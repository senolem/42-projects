import { Controller, Get, Query, Res } from '@nestjs/common'
import { LeaderboardService } from '@/src/leaderboard/leaderboard.service'

@Controller('leaderboard')
export class LeaderboardController {
	constructor(
		private readonly leaderboardService: LeaderboardService
	) {}

	@Get()
	async findAll(
		@Res() res,
		@Query('page') page: number = 1,
		@Query('itemsPerPage') itemsPerPage: number = 5,
		@Query('sortBy') sortBy: string = 'xp',
		@Query('sortType') sortType: string = 'asc'
	): Promise<void> {
		try {
			const offset = (page - 1) * itemsPerPage
			const users = await this.leaderboardService.findAll(false, offset, itemsPerPage, sortBy, sortType)
			const totalUsers = await this.leaderboardService.countAll()
			const leaderboard = users.map(user => ({ username: user.username, xp: user.xp, victoriesInARow: user.victoriesInARow, totalVictories: user.totalVictories }))
			res.status(200).json({ statusCode: 200, success: true, message: 'Successfully fetched leaderboard', data: { leaderboard, totalItems: totalUsers } })
		}
		catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to fetch leaderboard : ${error}` })
		}
	}
}
