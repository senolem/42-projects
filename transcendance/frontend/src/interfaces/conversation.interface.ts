import { User } from '@/interfaces/user.interface'
import { ConversationMessage } from '@/interfaces/conversationMessage.interface'

export interface Conversation {
	id: number
	sender: User
	recipientId: number
	messages: ConversationMessage[]
}
