import { UserModel } from '@/src/user/user.model'
import { matchMaker } from 'colyseus'

export interface MatchmakingRoom {
	player1: number
	player2: number
}
