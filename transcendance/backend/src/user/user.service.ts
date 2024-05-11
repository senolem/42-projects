import { Injectable, UnauthorizedException } from '@nestjs/common'
import { InjectModel } from '@nestjs/sequelize'
import { FindOptions, Op } from 'sequelize'
import { UserModel } from '@/src/user/user.model'
import { RelationshipService } from '@/src/relationship/relationship.service'
const bcrypt = require('bcrypt')

@Injectable()
export class UserService {
	constructor(
		@InjectModel(UserModel)
		private userModel: typeof UserModel,
		private relationshipService: RelationshipService
	) {}

	async findAll(): Promise<UserModel[]> {
		const options: FindOptions<UserModel> = {}
		options.attributes = ['id', 'username', 'avatar', 'background', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'status']
		return await this.userModel.findAll(options)
	}

	async findByPk(id: number, userId?: number): Promise<UserModel> {
		const user = await this.userModel.findByPk(id, { attributes: ['id', 'username', 'avatar', 'background', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'status'] })

		if (userId) {
			if (user) {
				let areFriends = false
				if (user.id !== userId) {
					areFriends = await this.relationshipService.areFriends(userId, user.id)
				} else {
					areFriends = true
				}
				if (areFriends) {
					return user
				}
				else {
					user.status = 0
					return user
				}
			}
		} else {
			if (user) {
				user.status = 0
				return user
			} else {
				return undefined
			}
		}
	}

	async findByPkArray(ids: number[]): Promise<UserModel[]> {
		return await this.userModel.findAll({
			where: { id: ids },
			attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'status']
		})
	}

	async findBy42Id(id: number): Promise<UserModel> {
		return await this.userModel.findOne({
			where: {
				id42: {
					[Op.eq]: id
				}
			}
		})
	}

	async findByUsername(username: string, userId?: number): Promise<UserModel> {
		const user = await this.userModel.findOne({
			where: {
				username: {
					[Op.eq]: username
				}
			},
			attributes: ['id', 'username', 'avatar', 'background', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'status', 'enable2FA', 'secret', 'totalVictories', 'victoriesInARow', 'createdAt']
		})
		if (!user) {
			return undefined
		}
		if (userId) {
			if (user) {
				let areFriends = false
				if (user.id !== userId) {
					areFriends = await this.relationshipService.areFriends(userId, user.id)
				} else {
					areFriends = true
				}
				if (areFriends) {
					return user
				}
				else {
					user.status = 0
					return user
				}
			}
		} else {
			if (user) {
				user.status = 0
				return user
			} else {
				return undefined
			}
		}
	}

	async findBySessionId(sessionId: string): Promise<UserModel> {
		return await this.userModel.findOne({
			where: {
				session: {
					[Op.eq]: sessionId
				}
			},
			attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'status']
		})
	}

	async create(user: UserModel): Promise<UserModel> {
		const hashedPassword = await bcrypt.hash(user.password, 10)
		user.password = hashedPassword
		return await this.userModel.create(user)
	}

	async update(id: string, user: UserModel): Promise<UserModel> {
		return await this.userModel.update(user, { where: {id} })
			.then(() => {
				return this.userModel.findByPk(id)
			})
	}

	async delete(id: string): Promise<void> {
		return await this.userModel.destroy({ where: { id } })
			.then(() => {})
	}

	async updateAvatar(id: number, newAvatar: string): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.update({ avatar: newAvatar })
	}

	async updateBackground(id: number, newBackground: string): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.update({ background: newBackground })
	}

	async updateUsername(id: number, newUsername: string): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		const existingUser = await this.findByUsername(newUsername)
		if (existingUser) {
			throw new UnauthorizedException('Username is already taken')
		}
		return await user.update({ username: newUsername })
	}

	async updatePassword(id: number, newPassword: string): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		const hashedPassword = await bcrypt.hash(newPassword, 10)
		return await user.update({ password: hashedPassword })
	}

	async updateUsernameColor(id: number, newUsernameColor: string): Promise<UserModel> {
		const colors = [
			'#D4ADCF',
			'#FAEDCA',
			'#20BF55',
			'#FF674D',
			'#7CC6FE',
			'#FFF'
		]
		if (!colors.includes(newUsernameColor)) {
			throw new UnauthorizedException('Invalid color')
		}
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.update({ usernameColor: newUsernameColor })
	}

	async removeAvatar(id: number): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.update({ avatar: 'default.png' })
	}

	async removeBackground(id: number): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.update({ background: 'default.png' })
	}

	async updateVictoryStreak(id: string): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.increment('victoriesInARow', { by: 1 })
	}

	async updateVictories(id: string): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.increment('totalVictories', { by: 1 })
	}

	async enableTwoFactorAuthentication(id: number): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.update({ enable2FA: true })
	}

	async disableTwoFactorAuthentication(id: number): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.update({ enable2FA: false })
	}

	async setTwoFactorAuthenticationSecret(secret: string, id: number): Promise<UserModel> {
		if (!secret) 
			throw new UnauthorizedException('Missing secret')
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.update({ secret: secret })
	}

	async removeTwoFactorAuthenticationSecret(id: number): Promise<UserModel> {
		const user = await this.userModel.findByPk(id)
		if (!user) {
			throw new UnauthorizedException('Incorrect user ID')
		}
		return await user.update({ secret: null })
	}
}
