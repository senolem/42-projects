import { User } from '@/interfaces/user.interface'

export interface ConversationMessage {
	id: string
	sender: User
	senderId: number
	recipientId: number
	text: string
}
