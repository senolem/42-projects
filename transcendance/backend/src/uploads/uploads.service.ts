import { Injectable, Body } from '@nestjs/common'

@Injectable()
export class UploadsService {
	constructor() {}

	handleMultipleFiles(files: Express.Multer.File[], @Body() body) {
		const dataset = new Map()
		files.forEach(file => {
			dataset.set(file.fieldname, file.filename)
		})
		for (const [key, value] of Object.entries(body)) {
			dataset.set(key, value)
		}
		const response = Object.fromEntries(dataset)
		return response
	}

	handleFile(file: Express.Multer.File) {
		const dataset = new Map()
		dataset.set(file.fieldname, file.filename)
		const response = Object.fromEntries(dataset)
		return response
	}

	handleText(@Body() body) {
		const dataset = new Map()
		for (const [key, value] of Object.entries(body)) {
			dataset.set(key, value)
		}
		const response = Object.fromEntries(dataset)
		return response
	}
}
