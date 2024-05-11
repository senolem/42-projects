import { User } from './user.interface';

export interface Scores {
	id: string
	player1: User
	player1Score: number
	player1Xp: number
	player2: User
	player2Score: number
	player2Xp: number
	matchLength: number
	winByForfeit: number
	updatedAt: Date
}
