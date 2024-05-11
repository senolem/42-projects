import { Controller, Post, Req, Res, Body, UseInterceptors, UploadedFile, ParseFilePipeBuilder, HttpStatus } from '@nestjs/common'
import { FileInterceptor, AnyFilesInterceptor, NoFilesInterceptor } from '@nestjs/platform-express'
import { diskStorage } from 'multer'
import { UploadsService } from '@/src/uploads/uploads.service'
import { editFileName, imageFileFilter } from './file-upload.utils'
import { UserService } from '@/src/user/user.service'
const fs = require('fs')
const probe = require('probe-image-size')

@Controller('uploads')
export class UploadsController {
	constructor(
		private readonly uploadsService: UploadsService,
		private readonly userService: UserService
	) {}

	@Post('background')
	@UseInterceptors(
		FileInterceptor('background', {
			storage: diskStorage({
				destination: './data/background',
				filename: editFileName
			}),
			fileFilter: imageFileFilter
		})
	)
	async uploadBackground(
		@Req() req,
		@Res() res,
		@UploadedFile(
			new ParseFilePipeBuilder()
			.addMaxSizeValidator({ maxSize: 5242880 })
			.build({
				errorHttpStatusCode: HttpStatus.UNPROCESSABLE_ENTITY
			})
		)
		file: Express.Multer.File
	) {
		try {
			const readStream = fs.createReadStream(file.path)
			const result = await probe(readStream)
			if (result.width < 900 || result.width > 3000 || result.height < 900 || result.height > 3000) {
				throw new Error('Background width and height should be between 900 x 900 and 3000 x 3000 pixels.')
			}
		} catch (error) {
			fs.unlink(file.path, (err) => {
				if (err) {
					console.error('Error in deleting the file', err)
				} else {
					console.log('File deleted successfully')
				}
			})
			res.status(422).json({ statusCode: 422, success: false, message: error })
			return
		}
		try {
			const userId = req.session.userId
			const response = this.uploadsService.handleFile(file)
			if (response['background']) {
				this.userService.updateBackground(userId, response['background'])
			}
			res.status(201).json({ statusCode: 201, success: true, message: `Successfully received data from user ${userId}`, data: { response } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to receive data: ${error}` })
		}
	}

	@Post('avatar')
	@UseInterceptors(
		FileInterceptor('avatar', {
			storage: diskStorage({
				destination: './data/avatar',
				filename: editFileName
			}),
			fileFilter: imageFileFilter
		})
	)
	async uploadAvatar(
		@Req() req,
		@Res() res,
		@UploadedFile(
			new ParseFilePipeBuilder()
			.addMaxSizeValidator({ maxSize: 2097152 })
			.build({
				errorHttpStatusCode: HttpStatus.UNPROCESSABLE_ENTITY
			})
		)
		file: Express.Multer.File,
		@Body() body
	) {
		try {
			const readStream = fs.createReadStream(file.path)
			const result = await probe(readStream)
			if (result.width > 3000 && result.height > 3000) {
				throw new Error('Avatar width and height should not exceed 3000 x 3000 pixels.')
			}
		} catch (error) {
			fs.unlink(file.path, (err) => {
				if (err) {
					console.error('Error in deleting the file', err)
				} else {
					console.log('File deleted successfully')
				}
			})
			res.status(422).json({ statusCode: 422, success: false, message: error })
			return
		}
		try {
			const userId = req.session.userId
			const response = this.uploadsService.handleFile(file)
			if (response.avatar) {
				this.userService.updateAvatar(userId, response.avatar)
			}
			res.status(201).json({ statusCode: 201, success: true, message: `Successfully received data from user ${userId}`, data: { response } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to receive data: ${error}` })
		}
	}

	@Post('profile')
	@UseInterceptors(NoFilesInterceptor())
	async handleMultiPartData(@Req() req, @Res() res, @Body() body) {
		try {
			const userId = req.session.userId
			const response = this.uploadsService.handleText(body)
			if (response.username) {
				await this.userService.updateUsername(userId, response.username)
			}
			if (response.newPassword && response.repeatPassword && response.newPassword === response.repeatPassword) {
				await this.userService.updatePassword(userId, response.newPassword)
			}
			if (response.color) {
				await this.userService.updateUsernameColor(userId, response.color)
			}
			res.status(201).json({ statusCode: 201, success: true, message: `Successfully received data from user ${userId}`, data: { response } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to receive data: ${error}` })
		}
	}
}
