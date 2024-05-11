import { Controller, Get, Req, Res, Query } from '@nestjs/common'
import { InjectModel } from '@nestjs/sequelize'
import { Op } from 'sequelize'
import { ChatService } from '@/src/chat/chat.service'
import { ConversationMessageModel } from '@/src/chat/conversationMessage.model'
import { SocketIOGateway } from '@/src/socket/socket.gateway'
import { UserService } from '@/src/user/user.service'
import { UserModel } from '@/src/user/user.model'

interface Conversation {
	id: number,
	sender: UserModel,
	recipientId: number,
	messages: ConversationMessageModel[]
}

@Controller('chat')
export class ChatController {
	constructor(
		private readonly chatService: ChatService,
		private readonly SocketIOGateway: SocketIOGateway,
		private readonly userService: UserService,
		@InjectModel(ConversationMessageModel)
		private conversationMessageModel: typeof ConversationMessageModel
	) {}

	@Get()
	async findAllRoomsMessages(@Req() req, @Res() res, @Query('limit') limit?: number) {
		if (limit < 1 || limit > 500) {
			res.status(500).json({ statusCode: 500, success: false, message: 'Failed to fetch rooms messages : Invalid limit' })
		}
		try {
			const rooms = await this.chatService.findAllRoomsMessages(req.session.userId, limit)
			res.status(200).json({ statusCode: 200, success: true, message: 'Rooms messages fetched successfully', data: { rooms } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to fetch rooms messages : ${error}` })
		}
	}

	@Get('users')
	async findAllConnectedChatUsers(@Res() res) {
		try {
			const connectedUsers = Array.from(this.SocketIOGateway.chatClients.values()).map((client) => {
				return {
					id: client.data.user.id,
					username: client.data.user.username,
					avatar: client.data.user.avatar
				}
			})
			res.status(200).json({ statusCode: 200, success: true, message: 'Chat users fetched successfully', data: { connectedUsers } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to fetch chat users : ${error}` })
		}
	}

	@Get('conversations')
	async findConversations(@Req() req, @Res() res): Promise<void> {
		try {
			const userId = req.session.userId
			const messages = await this.conversationMessageModel.findAll({
				where: {
					[Op.or]: [
						{ senderId: userId },
						{ recipientId: userId },
					],
				},
				order: [['createdAt', 'ASC']],
				include: [
					{
						model: UserModel,
						as: 'sender',
						attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor']
					}
				]
			})
			const senderIds = messages.map(message => message.senderId)
			const recipientIds = messages.map(message => message.recipientId)
			const usersIds = Array.from(new Set([...senderIds, ...recipientIds]))
			const users = await this.userService.findByPkArray(usersIds)
			const usersMap = new Map<number, UserModel>()
			users.forEach(user => {
				usersMap.set(user.id, user)
			})
			const conversations: Conversation[] = []
			messages.forEach(message => {
				const otherUserId = message.senderId === userId ? message.recipientId : message.senderId
				const otherUser = usersMap.get(otherUserId)
				if (otherUser) {
					let conversation = conversations.find(c => c.id === otherUserId)
					if (!conversation) {
						conversation = {
							id: otherUserId,
							sender: otherUser,
							recipientId: userId,
							messages: []
						}
						conversations.push(conversation)
					}
					conversation.messages.push(message)
				} else {
					throw new Error('Failed to fetch user data when packing conversation')
				}
			})
			res.status(200).json({ statusCode: 200, message: `Successfully fetched conversations`, data: { conversations } })
		} catch (error) {
			res.status(500).json({ statusCode: 500, success: false, message: `Failed to fetch conversations : ${error}` })
		}
	}

	@Get('*')
	handleNotFound(@Res() res): void {
		res.status(404).json({ statusCode: 404, success: false, message: '404 Not Found' })
	}
}
