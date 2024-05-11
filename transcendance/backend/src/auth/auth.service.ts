import { Req, Injectable, InternalServerErrorException, NotFoundException, UnauthorizedException, Inject, forwardRef } from '@nestjs/common'
import { randomBytes } from 'crypto'
import { extname } from 'path'
import { Op } from 'sequelize'
import axios from 'axios'
import * as fs from 'fs'
import { UserService } from '@/src/user/user.service'
import { config } from '@/config'
import { User42 } from '@/src/interfaces/user42.interface'
import { UserModel } from '@/src/user/user.model'
import { authenticator } from 'otplib'
import { generateRandomNumber } from '@/src/helpers'
const bcrypt = require('bcrypt')
const jwt = require('jsonwebtoken')
const path = require('path')

@Injectable()
export class AuthService {
	constructor(
		@Inject(forwardRef(() => UserService))
		private readonly userService: UserService
	) {}

	generateToken(id: number) : string {
		return jwt.sign(
			{ userId: id },
			config.jwtSecret,
			{ expiresIn: '365d' }
		)
	}

	verifyToken(token: string): number {
		if (!token)
			throw new UnauthorizedException('Missing token')
		try {
			const decoded = jwt.verify(token, config.jwtSecret) as { userId: number }
			return decoded.userId
		} catch (error) {
			throw new UnauthorizedException('Invalid token')
		}
	}

	generateSessionId() {
		const bytes = randomBytes(32)
		return bytes.toString('hex')
	}

	async checkSessionId(@Req() req) {
		try {
			const decodedUserID = this.verifyToken(req.cookies.session)
			const user = await this.userService.findByPk(decodedUserID)
			if (!user) {
				throw new UnauthorizedException('Invalid Session ID')
			}
			await UserModel.update(
				{ session: req.session.sessionId },
				{ where: { id: req.session.userId }}
			)
			return {
				id: user.id,
				username: user.username,
				avatar: user.avatar,
				xp: user.xp,
				isAdmin: user.isAdmin,
				usernameColor: user.usernameColor,
				textColor: user.textColor,
				secret: user.secret,
				enable2FA: user.enable2FA
			}
		} catch (error) {
			throw new UnauthorizedException('Invalid Session ID')
		}
	}

	async validatePassword(password: string, hashedPassword: string): Promise<boolean> {
		return await bcrypt.compare(password, hashedPassword)
	}

	async authBearer(token: string) {
		try {
			const userId = this.verifyToken(token)
			const user = await this.userService.findByPk(userId)
			return user
		}
		catch (error) {
			throw new UnauthorizedException(`Authentication failed: ${error}`)
		}
	}

	async authSessionId(sessionId: string) {
		try {
			if (sessionId === 'UNITY') { // DELETE THIS AFTER DEVELOPMENT
				const user = await this.userService.findByPk(1)
				return user
			}
			const user = await this.userService.findBySessionId(sessionId)
			return user
		}
		catch (error) {
			throw new UnauthorizedException(`Authentication failed: ${error}`)
		}
	}

	async loginAdmin(username: string, password: string): Promise<string> {
		const user = await this.userService.findByUsername(username)
		if (!user) {
			throw new NotFoundException('Invalid username')
		}
		const isPasswordValid = await this.validatePassword(password, user.password)
		if (!isPasswordValid) {
			throw new UnauthorizedException('Invalid password')
		}
		if (!user.isAdmin) {
			throw new UnauthorizedException('You are not allowed to access this resource.')
		}
		return this.generateToken(user.id)
	}

	async login(@Req() req, username: string, password: string): Promise<string> {
		const user = await UserModel.findOne({
			where: {
				username: {
					[Op.eq]: username
				}
			}
		})
		if (!user) {
			throw new NotFoundException('Invalid username')
		}
		if (user.password === 'defaultpassword') {
			throw new UnauthorizedException('You didn\'t set a password yet. Log in through your authentication app and change it')
		}
		const isPasswordValid = await this.validatePassword(password, user.password)
		if (!isPasswordValid) {
			throw new UnauthorizedException('Invalid password')
		}
		const sessionId = this.generateToken(user.id)
		req.session.sessionId = sessionId
		req.session.userId = user.id
		return sessionId
	}

	async login42(@Req() req, user: User42): Promise<string> {
		const exists = await this.userService.findBy42Id(user.id)
		let sessionId
		let newUser
		if (!exists) {
			try {
				let avatarFile = 'default.png'
				if (user._json.image && user._json.image.link) {
					const avatarUrl = user._json.image.link
					const avatarExtension = extname(avatarUrl)
					avatarFile = `${user.id}${avatarExtension}`
					const avatarPath = path.join(process.cwd(), 'data/avatar', avatarFile)
					const avatarStream = fs.createWriteStream(avatarPath)
					const res = await axios.get(avatarUrl, { responseType: 'stream' })
					res.data.pipe(avatarStream)
					await new Promise((resolve, reject) => {
						avatarStream.on('finish', resolve)
						avatarStream.on('error', reject)
					})
				}
				let usernameAlreadyTaken = await UserModel.findOne({
					where: {
						username: {
							[Op.eq]: user.username
						}
					}
				})
				while (usernameAlreadyTaken && user.username.length <= 20) {
					user.username += generateRandomNumber()
					usernameAlreadyTaken = await UserModel.findOne({
						where: {
							username: {
								[Op.eq]: user.username
							}
						}
					})
				}
				if (usernameAlreadyTaken) {
					throw new InternalServerErrorException(`Failed to generate a unique username. Please try again`)
				}
				newUser = await UserModel.create({
					id42: String(user.id),
					username: user.username,
					password: "defaultpassword",
					avatar: avatarFile
				})
				sessionId = this.generateToken(newUser.id)
				req.session.userId = newUser.id
			} catch (error) {
				throw new InternalServerErrorException(`Error while trying to create a new user: ${error}`)
			}
		}
		else {
			sessionId = this.generateToken(exists.id)
			req.session.userId = exists.id
		}
		req.session.sessionId = sessionId
		return sessionId
	}

	async register(username: string, password: string): Promise<void> {
		const user = await UserModel.findOne({
			where: {
				username: {
					[Op.eq]: username
				}
			}
		})
		if (!/^[a-zA-Z0-9]{1,20}$/.test(username)) {
			throw new UnauthorizedException('Invalid username.')
		} else if (!/^.{8,128}$/.test(password)) {
			throw new UnauthorizedException('Invalid password.')
		}
		if (!user) {
			try {
				const newUser: UserModel = {
					username,
					password,
					avatar: 'default.png'
				} as UserModel
				await this.userService.create(newUser)
			} catch (error) {
				throw new InternalServerErrorException(`Error while trying to create a new user: ${error}`)
			}
		} else {
			throw new UnauthorizedException('Username already exists.')
		}
	}

	async generateTwoFactorAuthenticationSecret(id: number) {
		const user = await UserModel.findOne({ where: { id } })
		if (!user) {
			throw new NotFoundException('Invalid user\'s ID')
		}
		const secret = authenticator.generateSecret()
		const otpauthUrl = authenticator.keyuri(user.username, config.auth.twoFactorAuthApp, secret)
		return {
			secret,
			otpauthUrl
		}
	}

	async verify2FAToken(id: number, token: string) {
		if (!token) {
			throw new UnauthorizedException('Missing token')
		}
		const user = await UserModel.findOne({ where: { id } })
		if (!user) {
			throw new NotFoundException('Invalid user\'s ID')
		}
		try {
			const secret = user.secret
			return authenticator.verify({ token, secret })
		} catch (error) {
			throw new InternalServerErrorException(`Error during verification of the user's token: ${error}`)
		}
	}

	async confirmTwoFactorAuthentication(id: number, token: string, secret: string) {
		const user = await UserModel.findOne({ where: { id } })
		if (!user) {
			throw new NotFoundException('Invalid user\'s ID')
		}
		try {
			const isValid = authenticator.verify({ token, secret })
			if (isValid) {
				await this.userService.setTwoFactorAuthenticationSecret(secret, user.id)
				await this.userService.enableTwoFactorAuthentication(user.id)
			}
			return isValid
		} catch (error) {
			throw new InternalServerErrorException(`Error during verification of the user's token: ${error}`)
		}
	}

	async checkUserAuth(id: number) {
		const user = await UserModel.findOne({ where: { id } })
		if (!user) {
			throw new NotFoundException('Invalid user\'s ID')
		}
		const secret = user.secret
		const enable2FA = user.enable2FA
		return (secret && enable2FA)
	}
}
