import { Injectable, OnModuleInit, Logger } from '@nestjs/common'
import { UserModel } from '@/src/user/user.model'
import { UserService } from '@/src/user/user.service'
import { config } from '@/config'

@Injectable()
export class UserInitService implements OnModuleInit {
	constructor(
		private readonly userService: UserService
	) {}

	async onModuleInit() {
		await this.initUsers()
	}

	async initUsers() {
		try {
			const admin = await this.userService.findByUsername('admin')
			if (!admin) {
				const adminUser = {
					username: 'admin',
					avatar: 'default.png',
					xp: 1000000,
					password: config.jwtSecret,
					isAdmin: true,
					usernameColor: '#47A992',
					textColor: '#7A3E3E'
				}
				await this.userService.create(adminUser as UserModel)
				Logger.log('Admin account added to the database', 'UserInit')
			}
		} catch (error) {
			throw new Error(`Admin account creation failed : ${error}`)
		}
	}
}
