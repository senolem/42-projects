import { SubscribeMessage, WebSocketGateway, WebSocketServer, OnGatewayConnection, OnGatewayDisconnect, WsException } from '@nestjs/websockets'
import { Logger, Injectable, Inject, forwardRef } from '@nestjs/common'
import { Server, Socket } from 'socket.io'
import { ChatEvents } from '@/src/chat/chat.events'
import { AuthService } from '@/src/auth/auth.service'
import { ChatService } from '@/src/chat/chat.service'
import { SocketService } from '@/src/socket/socket.service'
import { Room } from '@/src/interfaces/room.interface'
import { RoomMessage } from '@/src/interfaces/roomMessage.interface'
import { ConversationMessage } from '@/src/interfaces/conversationMessage.interface'
import { UserService } from '@/src/user/user.service'
import { config } from '@/config'
import { Invitation } from '@/src/interfaces/invitation.interface'

@Injectable()
@WebSocketGateway(config.network.socketIOPort, {
	cors: {
		origin: `${config.network.frontendProtocol}://${config.network.frontendUrl}`,
		credentials: true
	}
})
export class SocketIOGateway implements OnGatewayConnection, OnGatewayDisconnect {
	constructor(
		private readonly chatEvents: ChatEvents,
		@Inject(forwardRef(() => AuthService))
		private readonly authService: AuthService,
		private readonly chatService: ChatService,
		@Inject(forwardRef(() => SocketService))
		private readonly socketService: SocketService,
		@Inject(forwardRef(() => UserService))
		private readonly userService: UserService
	) {}

	chatClients: Map<string, Socket> = new Map<string, Socket>()
	mainRoom: Room
	init: boolean = false

	@WebSocketServer()
	server: Server

	async initRooms() {
		this.init = true
		try {
			let mainRoom = await this.chatService.findByName('main')
			if (!mainRoom) {
				mainRoom = await this.chatService.createRoom(1, 'main', 'public')
				if (!mainRoom)
					throw new Error("Could not create main room")
			}
			this.mainRoom = mainRoom
			Logger.log('Server rooms initialized', 'WebSocket')
		} catch(error) {
			throw new Error(`Server rooms initialization failed : ${error}`)
		}
	}

	async handleConnection(client: Socket) {
		if (!this.init) {
			await this.initRooms()
		}
		try {
			if (client.handshake.headers.cookie || client.handshake.auth.session) {
				let user
				const clientType = client.handshake.auth.clientType
				if (client.handshake.headers.cookie) {
					const sessionId = this.socketService.getSessionId(client.handshake.headers.cookie)
					const decodedUserID = this.authService.verifyToken(sessionId)
					user = await this.userService.findByPk(decodedUserID)
				}
				else if (client.handshake.auth.session) {
					const sessionId = client.handshake.auth.session as string
					const decodedUserID = this.authService.verifyToken(sessionId)
					user = await this.userService.findByPk(decodedUserID)
				}
				if (!user) {
					throw new WsException('Invalid Session ID')
				}
				client.data.user = user
				if (clientType === 'chat') {
					for (const chatClient of this.chatClients.values()) {
						if (chatClient.data.user?.id === user.id) {
							throw new WsException('You are already connected')
						}
					}
					this.chatClients.set(client.id, client)
					this.server.emit('hasConnectedToChat', user)
					await this.chatService.addUserToRoom(this.mainRoom.id, user.id, this.mainRoom.name)
					await client.join(this.mainRoom.id)
					const joinedRooms = await this.chatService.findAllRooms(user.id)
					joinedRooms.forEach(async room => {
						await client.join(room.id)
					})
					if (user.status === 1) {
						user.status = 2
						await user.save()
					}
				} else {
					throw new WsException('Invalid client type')
				}
				Logger.log(`Client ${client.id} (#${user ? user.id : '?'}, ${user ? user.username : '?' }) connected (${clientType})`, 'WebSocket')
			} else {
				throw new WsException('You need either a valid "session" in your query or provide a "session" cookie with a valid Session ID')
			}
		}
		catch (error) {
			if (client.handshake.auth.clientType && client.handshake.auth.clientType === 'unity')
			{
				client.emit('authenticationFailed', error.message)
			} else {
				client.emit('errorMessage', error.message)
			}
			this.handleDisconnect(client, true)
		}
	}

	async handleDisconnect(client: Socket, disconnect: boolean = false) {
		if (!disconnect) {
			if (client.handshake.auth.clientType === 'chat' && client.data.user) {
				this.server.emit('hasDisconnectedFromChat', client.data.user.id)
				this.chatClients.delete(client.id)
				await client.leave(this.mainRoom.id)
				const joinedRooms = await this.chatService.findAllRooms(client.data.user.id)
				joinedRooms.forEach(async room => {
					await client.leave(room.id)
				})
				const user = await this.userService.findByPk(client.data.user.id)
				if (user.status === 2) {
					user.status = 1
					await user.save()
				}
			} else {
				this.chatClients.delete(client.id)
			}
			Logger.log(`Client ${client.id} (#${client.data.user ? client.data.user.id : '?'}, ${client.data.user ? client.data.user.username : '?' }) disconnected (${client.handshake.auth.clientType})`, 'WebSocket')
		}
		client.disconnect(true)
	}

	// Chat events
	@SubscribeMessage('sendRoomMessage')
	async handleSendMessage(client: Socket, payload: RoomMessage) {
		this.chatEvents.handleSendMessage(client, payload)
	}

	@SubscribeMessage('sendConversationMessage')
	async handleSendConversationMessage(client: Socket, payload: ConversationMessage) {
		this.chatEvents.handleSendConversationMessage(client, payload)
	}

	@SubscribeMessage('sendInvitation')
	async handleSendInvitation(client: Socket, payload: Invitation) {
		this.chatEvents.handleSendInvitation(client, payload)
	}
}
