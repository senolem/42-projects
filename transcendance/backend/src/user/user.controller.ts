import { Controller, Get, Post, Put, Delete, Body, Param, Res, Req, Query, UnauthorizedException } from '@nestjs/common'
import { UniqueConstraintError, ValidationError } from 'sequelize'
import { UserService } from '@/src/user/user.service'
import { UserModel } from '@/src/user/user.model'
import { getPath } from './user.utils'

@Controller('users')
export class UserController {
	constructor(
		private readonly userService: UserService
	) {}


	@Get()
	async findUser(@Req() req, @Res() res, @Query('id') id?: number, @Query('username') username?: string): Promise<void> {
		try {
			let user
			if (id !== undefined) {
				user = await this.userService.findByPk(id, req.session.userId)
			} else if (username !== undefined) {
				user = await this.userService.findByUsername(username, req.session.userId)
			} else {
				if (req.session.isAdmin) {
					try {
						const users = await this.userService.findAll()
						res.status(200).json({ statusCode: 200, success: true, message: 'Successfully fetched users', data: { users } })
						return
					} catch (error) {
						res.status(500).json({ statusCode: 500, success: false, message: `Failed to fetch users : ${error}` })
					}
				} else {
					res.status(401).json({ statusCode: 401, message: 'You are not allowed to access this resource' })
					return
				}
			}
			if (user) {
				res.status(200).json({ statusCode: 200, message: `Successfully fetched user`, data: { user } })
			} else {
				res.status(404).json({ statusCode: 404, success: false, message: 'User not found' })
			}
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to fetch user: ${error}` })
		}
	}

	@Get('me')
	async getSelfUser(@Req() req, @Res() res): Promise<void> {
		try {
			const user = await this.userService.findByPk(req.session.userId)
			if (user) {
				res.status(200).json({ statusCode: 200, message: `Successfully fetched user #${req.session.userId}`, data: { user } })
			} else {
				res.status(404).json({ statusCode: 404, success: false, message: `User #${req.session.userId} not found` })
			}
		} catch (error) {
			if (error instanceof UnauthorizedException) {
				res.status(401).json({ statusCode: 401, success: false, message: `Failed to fetch #${req.session.userId} : ${error}` })
			}
			else {
				res.status(500).json({ statusCode: 500, success: false, message: `Failed to fetch #${req.session.userId} : ${error}` })
			}
		}
	}

	@Post()
	async create(@Req() req, @Res() res, @Body() user: UserModel): Promise<void> {
		if (req.session.isAdmin) {
			try {
				const newUser = await this.userService.create(user)
				res.status(200).json({ statusCode: 200, success: true, message: `Successfully created user #${newUser.id}`, data: { newUser } })
			} catch (error) {
				if (error instanceof UniqueConstraintError || error instanceof ValidationError) {
					res.status(400).json({ statusCode: 400, success: false, message: `Invalid request : ${error}` })
				} else {
					res.status(500).json({ statusCode: 500, success: false, message: `User creation failed : ${error}` })
				}
			}
		} else {
			res.status(401).json({ statusCode: 401, message: 'You are not allowed to access this resource' })
		}
	}

	@Put(':id')
	async update(@Req() req, @Res() res, @Param('id') id: string, @Body() user: UserModel): Promise<void> {
		if (req.session.isAdmin) {
			try {
				const updatedUser = await this.userService.update(id, user)
				res.status(200).json({ statusCode: 200, success: true, message: `Successfully updated user #${id}`, data: { updatedUser } })
			} catch (error) {
				if (error instanceof UniqueConstraintError || error instanceof ValidationError) {
					res.status(400).json({ statusCode: 400, success: false, message: `Invalid request : ${error}` })
				} else {
					res.status(500).json({ statusCode: 500, success: false, message: `User modification failed : ${error}` })
				}
			}
		} else {
			res.status(401).json({ statusCode: 401, message: 'You are not allowed to access this resource' })
		}
	}

	@Delete(':id')
	async delete(@Req() req, @Res() res, @Param('id') id: string): Promise<void> {
		if (req.session.isAdmin) {
			try {
				const deletedUser = await this.userService.delete(id)
				res.status(200).json({ statusCode: 200, success: true, message: `Successfully deleted user #${id}`, data: { deletedUser } })
			} catch (error) {
				res.status(500).json({ statusCode: 500, success: false, message: `User deletion failed : ${error}` })
			}
		} else {
			res.status(401).json({ statusCode: 401, message: 'You are not allowed to access this resource' })
		}
	}

	@Get('avatar/:filename')
	async getAvatar(@Param('filename') filename: string, @Res() res) {
		try {
			const avatarPath = getPath('data/avatar', filename)
			res.sendFile(avatarPath)
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Avatar fetch failed : ${error}` })
		}
	}

	@Get('background/:filename')
	async getBackground(@Param('filename') filename: string, @Res() res) {
		try {
			const backgroundPath = getPath('data/background', filename)
			res.sendFile(backgroundPath)
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Background fetch failed : ${error}` })
		}
	}

	@Get('me/avatar')
	async getSelfAvatar(@Req() req, @Res() res) {
		try {
			const user = await this.userService.findByPk(req.session.userId)
			if (user) {
				const avatarPath = getPath('data/avatar', user.avatar)
				res.sendFile(avatarPath)
			} else {
				res.status(404).json({ statusCode: 404, success: false, message: `User #${req.session.userId} not found` })
			}
		} catch (error) {
			if (error instanceof UnauthorizedException) {
				res.status(401).json({ statusCode: 401, success: false, message: `Failed to fetch #${req.session.userId} : ${error}` })
			}
			else {
				res.status(500).json({ statusCode: 500, success: false, message: `Failed to fetch #${req.session.userId} : ${error}` })
			}
		}
	}

	@Get('me/background')
	async getSelfBackground(@Req() req, @Res() res) {
		try {
			const user = await this.userService.findByPk(req.session.userId)
			if (user) {
				const backgroundPath = getPath('data/background', user.background)
				res.sendFile(backgroundPath)
			} else {
				res.status(404).json({ statusCode: 404, success: false, message: `User #${req.session.userId} not found` })
			}
		} catch (error) {
			if (error instanceof UnauthorizedException) {
				res.status(401).json({ statusCode: 401, success: false, message: `Failed to fetch #${req.session.userId} : ${error}` })
			}
			else {
				res.status(500).json({ statusCode: 500, success: false, message: `Failed to fetch #${req.session.userId} : ${error}` })
			}
		}
	}

	@Put('me/avatar')
	async updateAvatar(@Req() req, @Res() res, @Body() credentials: Record<string, any>): Promise<void> {
		try {
			const user = await this.userService.findByPk(req.session.userId)
			if (user) {
				const updatedAvatar = await this.userService.updateAvatar(user.id, credentials.filename)
				res.status(200).json({ statusCode: 200, success: true, message: `Successfully updated avatar of user #${user.id}`, data: { updatedAvatar } })
			} else {
				res.status(404).json({ statusCode: 404, success: false, message: `User #${req.session.userId} not found` })
			}
		} catch (error) {
			if (error instanceof UniqueConstraintError || error instanceof ValidationError) {
				res.status(400).json({ statusCode: 400, success: false, message: `Invalid request : ${error}` })
			} else {
				res.status(500).json({ statusCode: 500, success: false, message: `User modification failed : ${error}` })
			}
		}
	}

	@Delete('me/avatar')
	async removeAvatar(@Req() req, @Res() res): Promise<void> {
		try {
			const user = await this.userService.findByPk(req.session.userId)
			if (user) {
				if (user.avatar !== 'default.png') {
					const updatedAvatar = await this.userService.removeAvatar(user.id)
					res.status(200).json({ statusCode: 200, success: true, message: `Successfully removed avatar of user #${user.id}`, data: { updatedAvatar } })
				} else {
					res.status(405).json({ statusCode: 405, success: false, message: `Deleting default avatar is not allowed` })
				}
			} else {
				res.status(404).json({ statusCode: 404, success: false, message: `User #${req.session.userId} not found` })
			}
		} catch (error) {
			if (error instanceof UniqueConstraintError || error instanceof ValidationError) {
				res.status(400).json({ statusCode: 400, success: false, message: `Invalid request : ${error}` })
			} else {
				res.status(500).json({ statusCode: 500, success: false, message: `User modification failed : ${error}` })
			}
		}
	}

	@Put('me/background')
	async updateBackground(@Req() req, @Res() res, @Body() credentials: Record<string, any>): Promise<void> {
		try {
			const user = await this.userService.findByPk(req.session.userId)
			if (user) {
				const updatedBackground = await this.userService.updateBackground(user.id, credentials.filename)
				res.status(200).json({ statusCode: 200, success: true, message: `Successfully updated background of user #${user.id}`, data: { updatedBackground } })
			} else {
				res.status(404).json({ statusCode: 404, success: false, message: `User #${req.session.userId} not found` })
			}
		} catch (error) {
			if (error instanceof UniqueConstraintError || error instanceof ValidationError) {
				res.status(400).json({ statusCode: 400, success: false, message: `Invalid request : ${error}` })
			} else {
				res.status(500).json({ statusCode: 500, success: false, message: `User modification failed : ${error}` })
			}
		}
	}

	@Delete('me/background')
	async removeBackground(@Req() req, @Res() res): Promise<void> {
		try {
			const user = await this.userService.findByPk(req.session.userId)
			if (user) {
				if (user.background !== 'default.jpg') {
					const updatedBackground = await this.userService.removeBackground(user.id)
					res.status(200).json({ statusCode: 200, success: true, message: `Successfully removed background of user #${user.id}`, data: { updatedBackground } })
				} else {
					res.status(405).json({ statusCode: 405, success: false, message: `Deleting default background image is not allowed` })
				}
			} else {
				res.status(404).json({ statusCode: 404, success: false, message: `User #${req.session.userId} not found` })
			}
		} catch (error) {
			if (error instanceof UniqueConstraintError || error instanceof ValidationError) {
				res.status(400).json({ statusCode: 400, success: false, message: `Invalid request : ${error}` })
			} else {
				res.status(500).json({ statusCode: 500, success: false, message: `User modification failed : ${error}` })
			}
		}
	}

	@Get('*')
	handleNotFound(@Res() res): void {
		res.status(404).json({ statusCode: 404, success: false, message: '404 Not Found' })
	}
}
