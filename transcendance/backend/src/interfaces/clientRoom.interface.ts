import { RoomMessageModel } from "@/src/chat/roomMessage.model"

export interface ClientRoom {
	id: string
	name: string
	privacy: string
	usersJoined: number
	messages: RoomMessageModel[]
}