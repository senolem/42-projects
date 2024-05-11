import { User } from '@/interfaces/user.interface'

export interface RoomMessage {
	type: string
	id: string
	sender: User
	senderId: number
	room: string
	text: string
}
