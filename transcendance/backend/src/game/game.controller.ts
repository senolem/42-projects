import { Controller, Get, Param, Query, Req, Res } from '@nestjs/common'
import { config } from '@/config'
import { getPath } from '@/src/user/user.utils'
import { UserService } from '../user/user.service'
const jwt = require('jsonwebtoken')

@Controller('game')
export class GameController {
	constructor(
		private readonly userService: UserService,
	) {}

	@Get('avatar/:filename')
	async getAvatar(@Req() req, @Res() res, @Param('filename') filename: string, @Query('authorization') authorization: string) {
		if (authorization) {
			try {
				const decoded = jwt.verify(authorization, config.jwtSecret)
				const user = await this.userService.findByPk(decoded.userId)
				req.session.isAdmin = user.isAdmin
				req.session.userId = decoded.userId
			} catch (error) {
				return res.status(401).json({ statusCode: 401, success: false, message: 'Invalid authorization token' })
			}
		} else {
			return res.status(401).json({ statusCode: 401, success: false, message: 'You need to provide an authorization query containing your token in your request. Please try again' })
		}
		try {
			const avatarPath = getPath('data/avatar', filename)
			res.sendFile(avatarPath)
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Avatar fetch failed : ${error}` })
		}
	}

	@Get('thumbnail/:filename')
	async getThumbnail(@Req() req, @Res() res, @Param('filename') filename: string, @Query('authorization') authorization: string) {
		if (authorization) {
			try {
				const decoded = jwt.verify(authorization, config.jwtSecret)
				const user = await this.userService.findByPk(decoded.userId)
				req.session.isAdmin = user.isAdmin
				req.session.userId = decoded.userId
			} catch (error) {
				return res.status(401).json({ statusCode: 401, success: false, message: 'Invalid authorization token' })
			}
		} else {
			return res.status(401).json({ statusCode: 401, success: false, message: 'You need to provide an authorization query containing your token in your request. Please try again' })
		}
		try {
			const thumbnailPath = getPath('data/thumbnail', filename)
			res.sendFile(thumbnailPath)
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Thumbnail fetch failed : ${error}` })
		}
	}

	@Get('background/:filename')
	async getBackground(@Req() req, @Res() res, @Param('filename') filename: string, @Query('authorization') authorization: string) {
		if (authorization) {
			try {
				const decoded = jwt.verify(authorization, config.jwtSecret)
				const user = await this.userService.findByPk(decoded.userId)
				req.session.isAdmin = user.isAdmin
				req.session.userId = decoded.userId
			} catch (error) {
				return res.status(401).json({ statusCode: 401, success: false, message: 'Invalid authorization token' })
			}
		} else {
			return res.status(401).json({ statusCode: 401, success: false, message: 'You need to provide an authorization query containing your token in your request. Please try again' })
		}
		try {
			const backgroundPath = getPath('data/gameBackground', filename)
			res.sendFile(backgroundPath)
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Background fetch failed : ${error}` })
		}
	}

	@Get('music/:filename')
	async getMusic(@Req() req, @Res() res, @Param('filename') filename: string, @Query('authorization') authorization: string) {
		if (authorization) {
			try {
				const decoded = jwt.verify(authorization, config.jwtSecret)
				const user = await this.userService.findByPk(decoded.userId)
				req.session.isAdmin = user.isAdmin
				req.session.userId = decoded.userId
			} catch (error) {
				return res.status(401).json({ statusCode: 401, success: false, message: 'Invalid authorization token' })
			}
		} else {
			return res.status(401).json({ statusCode: 401, success: false, message: 'You need to provide an authorization query containing your token in your request. Please try again' })
		}
		try {
			const musicPath = getPath('data/music', filename)
			res.sendFile(musicPath)
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Music fetch failed : ${error}` })
		}
	}
	
	@Get('*')
	handleNotFound(@Res() res): void {
		res.status(404).json({ statusCode: 404, success: false, message: '404 Not Found' })
	}
}
