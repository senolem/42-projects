import { Injectable } from '@nestjs/common'
import { InjectModel } from '@nestjs/sequelize'
import { FindOptions } from 'sequelize'
import { UserModel } from '@/src/user/user.model'

@Injectable()
export class LeaderboardService {
	constructor(
		@InjectModel(UserModel)
		private userModel: typeof UserModel
	) {}

	async findAll(isAdmin: boolean, offset: number, itemsPerPage: number, sortBy: string, sortType: string): Promise<UserModel[]> {
		const options: FindOptions<UserModel> = {
			where: {
				isAdmin: isAdmin
			},
			attributes: [
				'id',
				'username',
				'xp',
				'totalVictories',
				'victoriesInARow'
			],
			offset: offset,
			limit: itemsPerPage,
			order: [[sortBy, sortType === 'desc' ? 'DESC' : 'ASC']]
		}
		return await this.userModel.findAll(options)
	}

	async countAll(): Promise<Number> {
		const options: FindOptions<UserModel> = {
			where: {
				isAdmin: false
			},
			attributes: [
				'id',
				'username',
				'xp',
				'totalVictories',
				'victoriesInARow'
			]
		}
		const count = await this.userModel.findAndCountAll(options)
		return count.count
	}
}
