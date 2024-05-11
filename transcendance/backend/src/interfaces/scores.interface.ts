import { UserModel } from '@/src/user/user.model'

export interface Scores {
	id: string
	player1: UserModel
	player1Score: number
	player2: UserModel
	player2Score: number
	matchLength: number
	winByForfeit: boolean
}
