import { RoomMessage } from '@/interfaces/roomMessage.interface'

export interface Room {
	id: string
	name: string
	privacy: string
	usersJoined: number
	messages: RoomMessage[]
}
