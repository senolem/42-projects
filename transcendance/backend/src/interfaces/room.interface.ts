import { UserModel } from '@/src/user/user.model'
import { RoomMessageModel } from '@/src/chat/roomMessage.model'

export interface Room {
	id: string
	name: string
	privacy: string
	owner: number
	op: number[]
	password: string
	usersJoined: number[]
	joinedUsers: UserModel[]
	blacklistedUsers: number[]
	messages: RoomMessageModel[]
}
