import { Controller, Body, Get, Post, Delete, Res, Req, UseGuards, NotFoundException, UnauthorizedException } from '@nestjs/common'
import { CookieOptions } from 'express'
import { AuthService } from '@/src/auth/auth.service'
import { AuthGuard42 } from '@/src/auth/auth.guard'
import { UserService } from '@/src/user/user.service'
import { User42 } from '@/src/interfaces/user42.interface'
import { config } from '@/config'
const qrCode = require('qrcode')

@Controller('auth')
export class AuthController {
	constructor(
		private readonly authService: AuthService,
		private readonly userService: UserService
	) {}

	@Get()
	async verifyAuth(@Req() req, @Res() res) {
		if (!req.cookies || !req.cookies.session) {
			return res.status(401).json({ statusCode: 401, success: false, message: 'Authentication failed: Missing "session" cookie.' })
		}
		try {
			const user = await this.authService.checkSessionId(req)
			if (user) {
				return res.status(200).json({ statusCode: 200, success: true, message: 'Authentication successful.' })
			} else {
				return res.status(401).json({ statusCode: 401, success: false, message: 'Authentication failed: Invalid "session" cookie.' })
			}
		} catch (error) {
			return res.status(401).json({ statusCode: 401, success: false, message: `Authentication failed: ${error}` })
		}
	}

	@Post('authorize')
	async verifyAuthAdmin(@Res() res, @Body() credentials: Record<string, any>): Promise<void> {
		try {
			const token = await this.authService.loginAdmin(credentials.username, credentials.password)
			res.status(200).json({ statusCode: 200, success: true, message: 'Authentication successful', data: { token } })
		}
		catch (error)
		{
			if (error instanceof NotFoundException) {
				res.status(404).json({ statusCode: 404, success: false, message: error.message })
			} else if (error instanceof UnauthorizedException) {
				res.status(401).json({ statusCode: 401, success: false, message: error.message })
			} else {
				res.status(500).json({ statusCode: 500, success: false, message: `Authentication failed : ${error}` })
			}
		}
	}

	@Get('42/callback')
	@UseGuards(AuthGuard42)
	async login42Callback(@Req() req, @Res() res): Promise<void> {
		try {
			const student: User42 = req.user as User42
			const sessionId = await this.authService.login42(req, student)
			const user = await this.userService.findBy42Id(student.id)
			let authentication = false
			if (user) {
				authentication = await this.authService.checkUserAuth(user.id)
				if (!authentication) {
					const cookieOptions: CookieOptions = {
						httpOnly: true,
						maxAge: 24 * 60 * 60 * 1000 * 365,
						sameSite: 'lax'
					}
					res.cookie('session', sessionId, cookieOptions)
				}
			}
			const url = new URL(`${config.network.frontendProtocol}:${config.network.frontendUrl}`)
			if (!authentication) {
				url.pathname = '/login'
				url.searchParams.set('success', '1')
			} else {
				url.pathname = '/2fa'
			}
			res.status(301).redirect(url.href)
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Error while logging in : ${error}` })
		}
	}

	@Post('login')
	async login(@Req() req, @Res() res, @Body() credentials: Record<string, any>) {
		try {
			const sessionId = await this.authService.login(req, credentials.username, credentials.password)
			const user = await this.userService.findByUsername(credentials.username)
			let authentication = false
			if (user) {
				authentication = await this.authService.checkUserAuth(user.id)
				if (!authentication) {
					const cookieOptions: CookieOptions = {
						httpOnly: true,
						maxAge: 24 * 60 * 60 * 1000 * 365,
						sameSite: 'lax'
					}
					res.cookie('session', sessionId, cookieOptions)
				}
			}
			res.status(200).json({ statusCode: 200, success: true, message: 'Authentication successful' })
		}
		catch (error)
		{
			if (error instanceof NotFoundException) {
				res.status(404).json({ statusCode: 404, success: false, message: error.message })
			} else if (error instanceof UnauthorizedException) {
				res.status(401).json({ statusCode: 401, success: false, message: error.message })
			} else {
				res.status(500).json({ statusCode: 500, success: false, message: `Error while logging in: ${error}` })
			}
		}
	}
	
	@Post('register')
	async register(@Req() req, @Res() res, @Body() credentials: Record<string, any>) {
		try {
			await this.authService.register(credentials.username, credentials.password)
			res.status(200).json({ statusCode: 200, success: true, message: 'Registration successful' })
		}
		catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: error.message })
		}
	}
	
	@Get('logout')
	async logout(@Req() req, @Res() res) {
		try {
			res.cookie('session', '', { expires: new Date(0) })
			req.session.destroy()
			return res.status(200).json({ statusCode: 200, success: true, message: 'Logging out successful.' })
		}
		catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Error while logging out : ${error}` })
		}
	}

	@Get('*')
	handleNotFound(@Res() res): void {
		res.status(404).json({ statusCode: 404, success: false, message: '404 Not Found' })
	}

	@Post('generate')
	async generateQRCode(@Res() res, @Req() req) {
		try {
			const userId = req.session.userId
			const { otpauthUrl, secret } = await this.authService.generateTwoFactorAuthenticationSecret(userId)
			qrCode.toDataURL(otpauthUrl, (error, dataUrl) => {
				if (error) {
					res.status(500).json({ statusCode: 500, success: false, message: `Failed to generate a QR code url: ${error}` })
				}
				res.status(201).json({ statusCode: 201, success: true, message: `Successfully generated a QR code url for user ${userId}`, data: { dataUrl, secret } })
			})
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to generate a QR code url: ${error}` })
		}
	}

	@Delete('2fa-secret')
	async deleteSecret(@Req() req, @Res() res) {
		try {
			const userId = req.session.userId
			const deleted = await this.userService.removeTwoFactorAuthenticationSecret(userId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully deleted user ${userId}'s secret`, data: { deleted } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to delete user's secret: ${error}` })
		}
	}

	@Post('2fa')
	async enable2FA(@Req() req, @Res() res) {
		try {
			const userId = req.session.userId
			const enabled = await this.userService.enableTwoFactorAuthentication(userId)
			res.status(201).json({ statusCode: 200, success: true, message: `Successfully enabled two-factor authentication for user ${userId}`, data: { enabled } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to enable two-factor authentication: ${error}` })
		}
	}

	@Delete('2fa')
	async disable2FA(@Req() req, @Res() res) {
		try {
			const userId = req.session.userId
			const disabled = await this.userService.disableTwoFactorAuthentication(userId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully disabled two-factor authentication for user ${userId}`, data: { disabled } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to disable two-factor authentication: ${error}` })
		}
	}

	@Post('confirm')
	async registerTo2FA(@Res() res, @Req() req,  @Body() credentials: Record<string, any>) {
		try {
			const userId = req.session.userId
			const isValid = await this.authService.confirmTwoFactorAuthentication(userId, credentials.token, credentials.secret)
			if (isValid) {
				res.status(200).json({ statusCode: 200, success: true, message: `Registration to two-factor authentication for user ${userId} has been successful` })
			} else {
				res.status(500).json({ statusCode: 500, success: false, message: `Registration to two-factor authentication for user ${userId} has failed` })
			}
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to register user to two-factor authentication: ${error}` })
		}
	}

	@Post('verify')
	async verifyToken(@Res() res, @Req() req, @Body() credentials: Record<string, any>) {
		try {
			const userId = req.session.userId
			const isValid = await this.authService.verify2FAToken(userId, credentials.token)
			if (isValid) {
				const sessionId = req.session.sessionId
				const cookieOptions: CookieOptions = {
					httpOnly: true,
					maxAge: 24 * 60 * 60 * 1000 * 365,
					sameSite: 'lax'
				}
				res.cookie('session', sessionId, cookieOptions)
				res.status(200).json({ statusCode: 200, success: true, message: `Two-factor authentication for user ${userId} has been successful` })
			} else {
				res.status(500).json({ statusCode: 500, success: false, message: `Two-factor authentication for user ${userId} has failed` })
			}
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to authentify user: ${error}` })
		}
	}
}
