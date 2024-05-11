import { Controller, Get, Res } from '@nestjs/common'

@Controller()
export class IndexController {
	@Get()
	public getIndex(@Res() res): void {
		res.status(200).json({
			"message": "Welcome to the Transcendance API!",
			"endpoints": [
				{
					"url": "/users",
					"description": "Registered users"
				},
				{
					"url": "/matchs",
					"description": "Matchs between players history"
				},
				{
					"url": "/friends",
					"description": "Friendships, blocked users, pending requests..."
				}
			]
		})
	}
}
