import { Controller, Get, Req, Res, Query } from '@nestjs/common'
import { ScoresService } from '@/src/scores/scores.service'

@Controller('scores')
export class ScoresController {
	constructor(
		private readonly scoresService: ScoresService
	) {}

	@Get()
	async getScores(@Res() res, @Query('id') id: number, @Query('limit') limit: number = 10, @Query('index') index: number = 0) {
		if (limit < 1 || limit > 500) {
			res.status(500).json({ statusCode: 500, success: false, message: 'Failed to fetch scores : Invalid limit. Limit should be between 1 and 500.' })
		}
		try {
			const scores = await this.scoresService.getScores(id, limit, index)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully fetched ${limit} starting from ${index} latest scores for player id ${id}`, data: { scores } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `${error}` })
		}
	}
}
