import { UserModel } from '@/src/user/user.model'
import { matchMaker } from 'colyseus'

export interface MatchmakingPlayer {
	sessionId: string
	user: UserModel
	joined: number
	roomId?: string
}
