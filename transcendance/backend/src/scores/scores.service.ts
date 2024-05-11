import { Injectable, Logger } from '@nestjs/common'
import { InjectModel } from '@nestjs/sequelize'
import { Op } from 'sequelize'
import { ScoresModel } from '@/src/scores/scores.model'
import { Scores } from '@/src/interfaces/scores.interface'
import { UserModel } from '@/src/user/user.model'

@Injectable()
export class ScoresService {
	constructor(
		@InjectModel(ScoresModel)
		private readonly scoresModel: typeof ScoresModel,
		@InjectModel(UserModel)
		private readonly userModel: typeof UserModel,
	) {}

	async getScores(id: number, limit: number, offset: number): Promise<Scores[]> {
		if (limit < 1 || limit > 500) {
			throw new Error('Invalid limit. Limit should be between 1 and 500.')
		}
		if (offset < 0) {
			throw new Error('Invalid offset. offset cannot be inferior to 0')
		}

		try {
			const scores = await this.scoresModel.findAll({
			where: {
				[Op.or]: [{ player1: id }, { player2: id }],
			},
			order: [['updatedAt', 'DESC']],
			limit: limit,
			offset: offset,
			include: [
				{
					model: this.userModel,
					as: 'player1User',
					attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'background', 'totalVictories', 'victoriesInARow'],
				},
				{
					model: this.userModel,
					as: 'player2User',
					attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'background', 'totalVictories', 'victoriesInARow'],
				},
			],
			})

			let formattedScores: Scores[] = scores.map(score => {
				return {
					id: score.id,
					player1: score.player1User,
					player1Score: score.player1Score,
					player1Xp: score.player1Xp,
					player2: score.player2User,
					player2Score: score.player2Score,
					player2Xp: score.player2Xp,
					winByForfeit: score.winByForfeit,
					matchLength: score.duration,
					updatedAt: score.updatedAt
				}
			})

			return formattedScores
		} catch (error) {
			throw new Error(`Failed to fetch scores: ${error}`)
		}
	}

	async countConsecutiveVictories(playerId: number): Promise<number> {
		try {
			let victories = 0
			let offset = 0
			let continueCounting = true

			while (continueCounting) {
				const score = await this.scoresModel.findOne({
					where: {
						[Op.or]: [{ player1: playerId }, { player2: playerId }],
					},
					order: [['updatedAt', 'DESC']],
					offset: offset,
				})

				if (score && ((score.player1 === playerId && score.player1Score > score.player2Score) ||
					(score.player2 === playerId && score.player2Score > score.player1Score))) {
					victories++
					offset++
				} else {
					continueCounting = false
				}
			}

			return victories
		} catch (error) {
			throw new Error(`Failed to count consecutive victories: ${error}`)
		}
	}

	async create(player1: number, player2: number, player1Score: number, player2Score: number, winByForfeit: boolean, duration: number, player1Xp: number, player2Xp: number): Promise<ScoresModel> {
		try {
			return await this.scoresModel.create({ player1, player2, player1Score, player2Score, winByForfeit, duration, player1Xp, player2Xp })
		} catch (error) {
			Logger.error(`Failed to add score ${error}`)
		}
	}
}
