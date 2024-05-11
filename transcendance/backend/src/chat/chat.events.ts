import { Injectable, Inject, forwardRef, Logger } from '@nestjs/common'
import { Socket } from 'socket.io'
import { AuthService } from '@/src/auth/auth.service'
import { ChatService } from '@/src/chat/chat.service'
import { GameService } from '@/src/game/game.service'
import { Room } from '@/src/interfaces/room.interface'
import { SocketService } from '@/src/socket/socket.service'
import { UserModel } from '@/src/user/user.model'
import { UserService } from '@/src/user/user.service'
import { RelationshipService } from '@/src/relationship/relationship.service'
import { config } from '@/config'
import { helpPage, helpPageAdmin, helpPageOperator } from '@/src/chat/chat.help'
import { Invitation } from '@/src/interfaces/invitation.interface'
import { RoomMessage } from '@/src/interfaces/roomMessage.interface'
import { ConversationMessage } from '@/src/interfaces/conversationMessage.interface'
import { SocketIOGateway } from '@/src/socket/socket.gateway'
import { SchedulerRegistry } from '@nestjs/schedule'
import { getGameAssetUrl, isAlphabetic, secondsToDhms } from '@/src/helpers'
import { GameState } from '@/src/enums/gameState.enum'
const Cryptr = require('cryptr')
const cryptr = new Cryptr(config.roomPasswordSecretKey, { encoding: 'base64', pbkdf2Iterations: 10000, saltLength: 10 })

@Injectable()
export class ChatEvents {
	constructor (
		@Inject(forwardRef(() => AuthService))
		private readonly authService: AuthService,
		private readonly chatService: ChatService,
		private readonly gameService: GameService,
		@Inject(forwardRef(() => SocketService))
		private readonly socketService: SocketService,
		@Inject(forwardRef(() => UserService))
		private readonly userService: UserService,
		@Inject(forwardRef(() => RelationshipService))
		private readonly relationshipService: RelationshipService,
		@Inject(forwardRef(() => SocketIOGateway))
		private readonly socketGateway: SocketIOGateway,
		private schedulerRegistry: SchedulerRegistry
	) {}

	async handleSendMessage(client: Socket, payload: RoomMessage) {
		if (!payload || !payload.text || !payload.currentRoom) {
			client.emit('errorMessage', 'Invalid message')
			return
		}
		const currentRoom = payload.currentRoom
		const text = payload.text?.trim()
		const args = text?.split(' ')
		try {
			const sessionId = this.socketService.getSessionId(client.handshake.headers.cookie)
			if (!sessionId) {
				throw new Error('Invalid session cookie')
			}
			const user = await this.authService.authSessionId(sessionId)
			if (!user) {
				throw new Error('Invalid user')
			}
			if (args[0] === '/help') {
				this.handleHelpCommand(client, user, currentRoom)
			} else if (args[0] === '/op') {
				await this.handleOpCommand(client, user, currentRoom, args[1])
			} else if (args[0] === '/deop') {
				await this.handleDeopCommand(client, user, currentRoom, args[1])
			} else if (args[0] === '/join') {
				await this.handleJoinCommand(client, user, args[1], args[2])
			} else if (args[0] === '/leave') {
				await this.handleLeaveCommand(client, user, currentRoom)
			} else if (args[0] === '/kick') {
				await this.handleKickCommand(client, user, currentRoom, args[1])
			} else if (args[0] === '/ban') {
				await this.handleBanCommand(client, user, currentRoom, args[1])
			} else if (args[0] === '/unban') {
				await this.handleUnbanCommand(client, user, currentRoom, args[1])
			} else if (args[0] === '/mute') {
				await this.handleMuteCommand(client, user, currentRoom, args[1], args[2])
			} else if (args[0] === '/createroom') {
				await this.handleCreateRoomCommand(client, user, args[1], args[2])
			} else if (payload.text.startsWith('/rooms')) {
				await this.handleRoomsCommand(client, currentRoom)
			} else if (payload.text.startsWith('/users')) {
				await this.handleUsersCommand(client, currentRoom)
			} else if (payload.text.startsWith('/here')) {
				await this.handleHereCommand(client, currentRoom)
			} else if (payload.text.startsWith('/broadcast')) {
				const message = payload.text.substring('/broadcast'.length).trim()
				await this.handleBroadcastCommand(client, user, message)
			} else if (payload.text.startsWith('/clear')) {
				await this.handleClearCommand(client)
			} else if (payload.text.startsWith('/privacy')) {
				await this.handleChangeRoomPrivacy(client, user, currentRoom, args[1])
			} else if (payload.text.startsWith('/password')) {
				await this.handleShowRoomPasswordCommand(client, currentRoom)
			} else if (payload.text.startsWith('/newpassword')) {
				await this.handleChangeRoomPasswordCommand(client, user, currentRoom)
			} else if (payload.text.startsWith('/')) {
				this.sendServerMessage(client, 'Server', `Invalid command '${payload.text}', use /help to get the available commands`, 'error')
			} else {
				await this.sendCurrentRoomMessage(client, user, currentRoom, payload.text)
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	async handleSendConversationMessage(client: Socket, payload: ConversationMessage) {
		try {
			if (!payload || !payload.recipient || !payload.text) {
				throw new Error('Invalid message')
			}
			const sessionId = this.socketService.getSessionId(client.handshake.headers.cookie)
			if (!sessionId) {
				throw new Error('Invalid session cookie')
			}			
			const user = await this.authService.authSessionId(sessionId)
			this.sendConversationMessage(client, user, payload.recipient, payload.text)
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleHelpCommand(client: Socket, user: UserModel, currentRoom: string) {
		let help = helpPage
		const isOp = await this.chatService.isOp(user.id, currentRoom)
		if (isOp) {
			help += helpPageOperator
		}
		if (user.isAdmin) {
			help += helpPageAdmin
		}
		this.sendServerMessage(client, 'Server', help, 'info')
	}

	private async handleOpCommand(client: Socket, user: UserModel, currentRoom: string, targetUsername: string) {
		try {
			const isOp = await this.chatService.isOp(user.id, currentRoom)
			if (!isOp) {
				this.sendServerMessage(client, 'Server', 'You do not have permission to run this command', 'error')
				return
			}
			const targetUser = await this.userService.findByUsername(targetUsername)
			if (!targetUser) {
				client.emit('errorMessage', `Unknown user: '${targetUsername}'`)
			} else {
				const isInRoom = await this.chatService.isInRoom(targetUser.id, currentRoom)
				if (!isInRoom) {
					this.sendServerMessage(client, 'Server', 'User did not joined room', 'error')
					return
				}
				if (targetUser.id === user.id) {
					this.sendServerMessage(client, 'Server', 'You cannot set yourself as an op', 'error')
					return
				}
				const isOp = await this.chatService.isOp(targetUser.id, currentRoom)
				if (isOp) {
					this.sendServerMessage(client, 'Server', 'This user has already been set as an op', 'error')
					return
				}
				const targetSocket = await this.socketService.findSocketById(targetUser.id, 'chat')
				if (targetSocket) {
					await this.chatService.addOp(targetUser.id, currentRoom)
					const roomName = await this.chatService.getRoomName(currentRoom)
					this.sendServerRoomMessage(currentRoom, 'Server', `${client.data.user.username} set ${targetSocket.data.user.username} as an operator`, 'info')
				}
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleDeopCommand(client: Socket, user: UserModel, currentRoom: string, targetUsername: string) {
		try {
			const isOp = await this.chatService.isOp(user.id, currentRoom)
			if (!isOp) {
				this.sendServerMessage(client, 'Server', 'You do not have permission to run this command', 'error')
				return
			}
			const targetUser = await this.userService.findByUsername(targetUsername)
			if (!targetUser) {
				client.emit('errorMessage', `Unknown user: '${targetUsername}'`)
			} else {
				const isInRoom = await this.chatService.isInRoom(targetUser.id, currentRoom)
				if (!isInRoom) {
					this.sendServerMessage(client, 'Server', `${targetUser.username} did not joined room`, 'error')
					return
				}
				if (targetUser.id === user.id) {
					this.sendServerMessage(client, 'Server', 'You cannot deop yourself', 'error')
					return
				}
				const roomOwnerId = await this.chatService.getRoomOwner(currentRoom)
				if (targetUser.id === roomOwnerId) {
					this.sendServerMessage(client, 'Server', 'You cannot deop the room owner', 'error')
					return
				}
				const isOp = await this.chatService.isOp(targetUser.id, currentRoom)
				if (!isOp) {
					this.sendServerMessage(client, 'Server', `${targetUser.username} is not an operator`, 'error')
					return
				}
				const targetSocket = await this.socketService.findSocketById(targetUser.id, 'chat')
				if (targetSocket) {
					await this.chatService.removeOp(targetUser.id, currentRoom)
					const roomName = await this.chatService.getRoomName(currentRoom)
					this.sendServerRoomMessage(currentRoom, 'Server', `${client.data.user.username} removed ${targetSocket.data.user.username} from the operators`, 'info')
				}
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleJoinCommand(client: Socket, user: UserModel, room: string, password?: string) {
		if (room && room.length >= 3 && room.length <= 10 && isAlphabetic(room)) {
			try {
				const joinedRoom = await this.chatService.findByName(room)
				if (joinedRoom) {
					if (joinedRoom.id === this.socketGateway.mainRoom.id) {
						this.sendServerMessage(client, 'Server', 'You cannot join the main room', 'error')
						return
					}
					if (joinedRoom.usersJoined.length >= config.maxClientsPerRoom) {
						this.sendServerMessage(client, 'Server', `Room is currently full`, 'error')
					}
					const isInRoom = await this.chatService.isInRoom(client.data.user.id, joinedRoom.id)
					if (!isInRoom) {
						if (joinedRoom.privacy === 'public') {
							await this.chatService.addUserToRoom(joinedRoom.id, user.id, joinedRoom.name)
							await client.join(joinedRoom.id)
							client.emit('joinedRoom', { id: joinedRoom.id, name: room, privacy: 'public' })
							await this.sendUsersJoinedCountUpdate(joinedRoom.id)
							this.sendServerRoomMessage(joinedRoom.id, 'Server', `${client.data.user.username} has joined`, 'info')
						} else if (joinedRoom.privacy === 'private') {
							try {
								const encryptedPassword = joinedRoom.password
								const decryptedPassword = cryptr.decrypt(encryptedPassword)
								if (password && password === decryptedPassword) {
									await this.chatService.addUserToRoom(joinedRoom.id, user.id, joinedRoom.name)
									await client.join(joinedRoom.id)
									client.emit('joinedRoom', { id: joinedRoom.id, name: room, privacy: 'private' })
									await this.sendUsersJoinedCountUpdate(joinedRoom.id)
									this.sendServerRoomMessage(joinedRoom.id, 'Server', `${client.data.user.username} has joined`, 'info')
								} else {
									this.sendServerMessage(client, 'Server', `Room '${room}' is private, invalid password`, 'error')
								}
							} catch (error) {
								this.sendServerMessage(client, 'Server', `An error occured during password decryption: ${error.message}`, 'error')
							}
						}
					} else {
						this.sendServerMessage(client, 'Server', `You already joined this room`, 'error')
					}
				} else {
					this.sendServerMessage(client, 'Server', `Room '${room}' does not exist`, 'error')
				}
			} catch (error) {
				this.sendServerMessage(client, 'Server', error.message, 'error')
			}
		} else {
			this.sendServerMessage(client, 'Server', 'Invalid room name (between 3 and 10 characters included, alphabetic only)', 'error')
		}
	}

	private async handleLeaveCommand(client: Socket, user: UserModel, currentRoom: string) {
		try {
			if (currentRoom === this.socketGateway.mainRoom.id) {
				this.sendServerMessage(client, 'Server', 'You cannot leave the main room', 'error')
				return
			}
			await this.chatService.removeUserFromRoom(currentRoom, user.id)
			await client.leave(currentRoom)
			client.emit('leftRoom', { id: currentRoom })
			await this.sendUsersJoinedCountUpdate(currentRoom)
			this.sendServerRoomMessage(currentRoom, 'Server', `${client.data.user.username} has left the room`, 'info')
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleKickCommand(client: Socket, user: UserModel, currentRoom: string, targetUsername: string) {
		try {
			const isOp = await this.chatService.isOp(user.id, currentRoom)
			if (!isOp) {
				this.sendServerMessage(client, 'Server', 'You do not have permission to run this command', 'error')
				return
			}
			const targetUser = await this.userService.findByUsername(targetUsername)
			if (!targetUser) {
				client.emit('errorMessage', `Unknown user: '${targetUsername}'`)
			} else {
				const isInRoom = await this.chatService.isInRoom(targetUser.id, currentRoom)
				if (!isInRoom) {
					this.sendServerMessage(client, 'Server', `${targetUser.username} did not joined room`, 'error')
					return
				}
				if (targetUser.id === user.id) {
					this.sendServerMessage(client, 'Server', 'You cannot kick yourself from a room. Please consider the command /leave', 'error')
					return
				}
				const roomOwnerId = await this.chatService.getRoomOwner(currentRoom)
				if (targetUser.id === roomOwnerId) {
					this.sendServerMessage(client, 'Server', 'You cannot kick the room owner', 'error')
					return
				}
				const targetSocket = await this.socketService.findSocketById(targetUser.id, 'chat')
				if (targetSocket) {
					await this.chatService.removeUserFromRoom(currentRoom, targetUser.id)
					await targetSocket.leave(currentRoom)
					targetSocket.emit('leftRoom', { id: currentRoom })
					const roomName = await this.chatService.getRoomName(currentRoom)
					await this.sendUsersJoinedCountUpdate(currentRoom)
					this.sendServerRoomMessage(currentRoom, 'Server', `${client.data.user.username} kicked ${targetSocket.data.user.username}`, 'info')
					this.sendServerMessage(targetSocket, 'Server', `You have been kicked from room ${roomName} by ${client.data.user.username}`, 'info')
				}
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleBanCommand(client: Socket, user: UserModel, currentRoom: string, targetUsername: string) {
		try {
			const isOp = await this.chatService.isOp(user.id, currentRoom)
			if (!isOp) {
				this.sendServerMessage(client, 'Server', 'You do not have permission to run this command', 'error')
				return
			}
			const targetUser = await this.userService.findByUsername(targetUsername)
			if (!targetUser) {
				client.emit('errorMessage', `Unknown user: '${targetUsername}'`)
			} else {
				const isInRoom = await this.chatService.isInRoom(targetUser.id, currentRoom)
				if (!isInRoom) {
					this.sendServerMessage(client, 'Server', `${targetUser.username} did not joined room`, 'error')
					return
				}
				if (targetUser.id === user.id) {
					this.sendServerMessage(client, 'Server', 'You cannot ban yourself from a room. Please consider the command /leave', 'error')
					return
				}
				const roomOwnerId = await this.chatService.getRoomOwner(currentRoom)
				if (targetUser.id === roomOwnerId) {
					this.sendServerMessage(client, 'Server', 'You cannot ban the room owner', 'error')
					return
				}
				const blacklist = await this.chatService.getBlacklistedUsers(currentRoom)
				if (blacklist.includes(targetUser.id)) {
					this.sendServerMessage(client, 'Server', `${targetUser.username} is already banned`, 'error')
					return
				}
				const targetSocket = await this.socketService.findSocketById(targetUser.id, 'chat')
				if (targetSocket) {
					await this.chatService.addUserToBlacklist(currentRoom, targetUser.id)
					await this.chatService.removeUserFromRoom(currentRoom, targetUser.id)
					await targetSocket.leave(currentRoom)
					targetSocket.emit('leftRoom', { id: currentRoom })
					targetSocket.emit('banned', { id: currentRoom })
					const roomName = await this.chatService.getRoomName(currentRoom)
					await this.sendUsersJoinedCountUpdate(currentRoom)
					this.sendServerRoomMessage(currentRoom, 'Server', `${client.data.user.username} banned ${targetSocket.data.user.username} `, 'info')
					this.sendServerMessage(targetSocket, 'Server', `You have been banned from room ${roomName} by ${client.data.user.username}`, 'info')
				}
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleUnbanCommand(client: Socket, user: UserModel, currentRoom: string, targetUsername: string) {
		try {
			const isOp = await this.chatService.isOp(user.id, currentRoom)
			if (!isOp) {
				this.sendServerMessage(client, 'Server', 'You do not have permission to run this command', 'error')
				return
			}
			const targetUser = await this.userService.findByUsername(targetUsername)
			if (!targetUser) {
				client.emit('errorMessage', `Unknown user: '${targetUsername}'`)
			} else {
				if (targetUser.id === user.id) {
					this.sendServerMessage(client, 'Server', 'You cannot unban yourself', 'error')
					return
				}
				const roomOwnerId = await this.chatService.getRoomOwner(currentRoom)
				if (targetUser.id === roomOwnerId) {
					this.sendServerMessage(client, 'Server', 'The room owner cannot be banned', 'error')
					return
				}
				const blacklist = await this.chatService.getBlacklistedUsers(currentRoom)
				if (!blacklist.includes(targetUser.id)) {
					this.sendServerMessage(client, 'Server', `${targetUser.username} is not banned`, 'error')
					return
				}
				const targetSocket = await this.socketService.findSocketById(targetUser.id, 'chat')
				if (targetSocket) {
					await this.chatService.removeUserFromBlacklist(currentRoom, targetUser.id)
					targetSocket.emit('unbanned', { id: currentRoom })
					const roomName = await this.chatService.getRoomName(currentRoom)
					this.sendServerRoomMessage(currentRoom, 'Server', `${client.data.user.username} unbanned ${targetSocket.data.user.username} `, 'info')
					this.sendServerMessage(targetSocket, 'Server', `You have been unbanned from room ${roomName}`, 'info')
					Logger.log(`${targetUser} has been unbanned from room ${roomName}`)
				}
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleUnmuteCommand(client: Socket, user: UserModel, currentRoom: string, targetUsername: string) {
		try {
			const isOp = await this.chatService.isOp(user.id, currentRoom)
			if (!isOp) {
				this.sendServerMessage(client, 'Server', 'You do not have permission to run this command', 'error')
				return
			}
			const targetUser = await this.userService.findByUsername(targetUsername)
			if (!targetUser) {
				client.emit('errorMessage', `Unknown user: '${targetUsername}'`)
			} else {
				if (targetUser.id === user.id) {
					this.sendServerMessage(client, 'Server', 'You cannot unmute yourself', 'error')
					return
				}
				const roomOwnerId = await this.chatService.getRoomOwner(currentRoom)
				if (targetUser.id === roomOwnerId) {
					this.sendServerMessage(client, 'Server', 'The room owner cannot be muted', 'error')
					return
				}
				const targetSocket = await this.socketService.findSocketById(targetUser.id, 'chat')
				if (targetSocket) {
					await this.chatService.unmuteUser(currentRoom, targetUser.id)
					targetSocket.emit('unmuted', { id: currentRoom })
					const roomName = await this.chatService.getRoomName(currentRoom)
					this.sendServerRoomMessage(currentRoom, 'Server', `${targetSocket.data.user.username} has been unmuted`, 'info')
					this.sendServerMessage(targetSocket, 'Server', `You have been unmuted from room ${roomName}`, 'info')
					Logger.log(`${targetUser} has been unmuted in room ${roomName}`)
				}
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleMuteCommand(client: Socket, user: UserModel, currentRoom: string, targetUsername: string, timeoutInSeconds: string) {
		try {
			if (Number(timeoutInSeconds) < 1 || Number(timeoutInSeconds) > 432000) {
				const Dhms = secondsToDhms(Number(timeoutInSeconds))
				this.sendServerMessage(client, 'Server', `Invalid time value`, 'error')
				return
			}
			const isOp = await this.chatService.isOp(user.id, currentRoom)
			if (!isOp) {
				this.sendServerMessage(client, 'Server', 'You do not have permission to run this command', 'error')
				return
			}
			const targetUser = await this.userService.findByUsername(targetUsername)
			if (!targetUser) {
				client.emit('errorMessage', `Unknown user: '${targetUsername}'`)
			} else {
				const isInRoom = await this.chatService.isInRoom(targetUser.id, currentRoom)
				if (!isInRoom) {
					this.sendServerMessage(client, 'Server', `${targetUser.username} did not joined room`, 'error')
					return
				}
				if (targetUser.id === user.id) {
					this.sendServerMessage(client, 'Server', 'You cannot mute yourself', 'error')
					return
				}
				const roomOwnerId = await this.chatService.getRoomOwner(currentRoom)
				if (targetUser.id === roomOwnerId) {
					this.sendServerMessage(client, 'Server', 'The room owner cannot be muted', 'error')
					return
				}
				const targetSocket = await this.socketService.findSocketById(targetUser.id, 'chat')
				if (targetSocket) {
					const muteEnd = new Date(Date.now())
					muteEnd.setSeconds(muteEnd.getSeconds() + Number(timeoutInSeconds))
					await this.chatService.muteUser(currentRoom, targetUser.id, muteEnd)
					const roomName = await this.chatService.getRoomName(currentRoom)
					this.sendServerRoomMessage(currentRoom, 'Server', `${client.data.user.username} muted ${targetSocket.data.user.username} for ${timeoutInSeconds} seconds`, 'info')
					this.sendServerMessage(targetSocket, 'Server', `You have been muted in room ${roomName} by ${client.data.user.username} for ${timeoutInSeconds} seconds`, 'info')
					const timeout = setTimeout(
						() => this.handleUnmuteCommand(client, user, currentRoom, targetUsername),
						Number(timeoutInSeconds) * 1000
					)
					const timeouts = this.schedulerRegistry.getTimeouts()
					if (timeouts.includes(`unmute ${user} in room ${currentRoom}`)) {
						this.schedulerRegistry.deleteTimeout(`unmute ${user} in room ${currentRoom}`)
					}
					this.schedulerRegistry.addTimeout(
						`unmute ${user} in room ${currentRoom}`,
						timeout
					)
				}
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleCreateRoomCommand(client: Socket, user: UserModel, roomName: string, privacy: string) {
		try {
			if (roomName && roomName.length >= 3 && roomName.length <= 10 && isAlphabetic(roomName)) {
				const roomExists = await this.chatService.roomExists(roomName)
				if (privacy && (privacy === 'public' || privacy === 'private')) {
					if (roomExists) {
						this.sendServerMessage(client, 'Server', 'Room already exist', 'error')
					} else {
						let password: string
						let newRoom: Room
						if (privacy === 'private') {
							password = Math.floor(Math.random() * 1000000).toString()
							const encryptedPassword = cryptr.encrypt(password)
							newRoom = await this.chatService.createRoom(user.id, roomName, privacy, encryptedPassword)
						} else {
							newRoom = await this.chatService.createRoom(user.id, roomName, privacy)
						}
						await this.chatService.addUserToRoom(newRoom.id, user.id, newRoom.name)
						await client.join(newRoom.id)
						client.emit('joinedRoom', { id: newRoom.id, name: roomName, privacy: privacy })
						await this.sendUsersJoinedCountUpdate(newRoom.id)
						this.sendServerMessage(client, 'Server', `Room '${roomName}' successfully created`, 'info')
						if (privacy === 'private') {
							this.sendServerMessage(client, 'Server', `Room password : ${password}`, 'info')
						}
					}
				} else if (!privacy) {
					if (roomExists) {
						this.sendServerMessage(client, 'Server', 'Room already exist', 'error')
					} else {
						const newRoom = await this.chatService.createRoom(user.id, roomName, privacy)
						await this.chatService.addUserToRoom(newRoom.id, user.id, newRoom.name)
						await client.join(newRoom.id)
						client.emit('joinedRoom', { id: newRoom.id, name: roomName, privacy: 'public' })
						await this.sendUsersJoinedCountUpdate(newRoom.id)
						this.sendServerMessage(client, 'Server', `Room '${roomName}' successfully created`, 'info')
					}
				} else {
					this.sendServerMessage(client, 'Server', 'Invalid room privacy', 'error')
				}
			} else {
				this.sendServerMessage(client, 'Server', 'Invalid room name (between 3 and 10 characters included, alphabetic only)', 'error')
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleRoomsCommand(client: Socket, currentRoom: string) {
		try {
			const rooms = await this.chatService.getPublicRooms()
			if (rooms.length === 0) {
				this.sendServerMessage(client, 'Server', 'No currently public available room', 'info')
			} else {
				const formattedRooms = await Promise.all(rooms.map(async (room) => {
					const clientCount = await this.chatService.getJoinedUsersCount(room.id)
					const roomName = room.name === currentRoom ? `${room.name} (Current)` : room.name
					return `- ${roomName} ${clientCount}/${config.maxClientsPerRoom}`
				}))
				const formattedList = `Available public rooms:\n${formattedRooms.join('\n')}`
				this.sendServerMessage(client, 'Server', formattedList, 'info')
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleUsersCommand(client: Socket, currentRoom: string) {
		try {
			const room = await this.chatService.findByPk(currentRoom)
			const users = await this.socketGateway.server.sockets.in(currentRoom).fetchSockets()
			const owner = await this.userService.findByPk(room.owner)
			const formattedUsers = await Promise.all(users.map(async (user) => {
				const id = user.data.user.id
				const ogUsername = user.data.user.username
				let username = user.data.user.username
				if (owner && owner.id && id === owner.id) {
					username += ' (Owner)'
				}
				const isOp = room.op.includes(id)
				if (isOp) {
					username += ' (Mod)'
				}
				if (ogUsername === client.data.user.username) {
					username += ' (You)'
				}
				return '- ' + username
			}))
			const formattedList = `Current room '${room.name}' connected users:\n${formattedUsers.join('\n')}`
			this.sendServerMessage(client, 'Server', formattedList, 'info')
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleHereCommand(client: Socket, currentRoom: string) {
		try {
			const room = await this.chatService.findByPk(currentRoom)
			const users = await this.chatService.findAllRoomUsers(currentRoom)
			const owner = await this.userService.findByPk(room.owner)
			const formattedUsers = await Promise.all(users.map(async (user) => {
				const id = user.id
				const ogUsername = user.username
				let username = user.username
				if (owner && owner.id && id === owner.id) {
					username += ' (Owner)'
				}
				const isOp = room.op.includes(id)
				if (isOp) {
					username += ' (Mod)'
				}
				if (ogUsername === client.data.user.username) {
					username += ' (You)'
				}
				return '- ' + username
			}))
			const formattedList = `Current room '${room.name}' joined users:\n${formattedUsers.join('\n')}`
			this.sendServerMessage(client, 'Server', formattedList, 'info')
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleChangeRoomPrivacy(client: Socket, user: UserModel, currentRoom: string, privacy: string) {
		try {
			const isOp = await this.chatService.isOp(user.id, currentRoom)
			if (!isOp) {
				this.sendServerMessage(client, 'Server', 'You do not have permission to run this command', 'error')
				return
			}
			if (privacy && (privacy === 'public' || privacy === 'private')) {
				const room = await this.chatService.findByPk(currentRoom)
				if (privacy === 'public' && room.privacy === 'public') {
					this.sendServerMessage(client, 'Server', 'Room is already public', 'error')
					return
				} else if (privacy === 'private' && room.privacy === 'private') {
					this.sendServerMessage(client, 'Server', 'Room is already private', 'error')
					return
				}
				if (privacy === 'public')
				{
					room.password = ''
					room.privacy = 'public'
					await room.save()
					this.socketGateway.server.to(room.id).emit('updateRoomPrivacy', { id: room.id, privacy: 'public' })
				} else if (privacy === 'private') {
					let roomPassword = ''
					roomPassword = Math.floor(Math.random() * 1000000).toString()
					const encryptedPassword = cryptr.encrypt(roomPassword)
					room.password = encryptedPassword
					room.privacy = 'private'
					await room.save()
					this.sendServerMessage(client, 'Server', `Current room '${room.name}' new password: ${roomPassword}`, 'info')
					this.socketGateway.server.to(room.id).emit('updateRoomPrivacy', { id: room.id, privacy: 'private' })
				}
			} else {
				this.sendServerMessage(client, 'Server', 'Invalid room privacy', 'error')
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async handleChangeRoomPasswordCommand(client: Socket, user: UserModel, currentRoom: string) {
		try {
			const isOp = await this.chatService.isOp(user.id, currentRoom)
			if (!isOp) {
				this.sendServerMessage(client, 'Server', 'You do not have permission to run this command', 'error')
				return
			}
			const room = await this.chatService.findByPk(currentRoom)
			let roomPassword = ''
			if (room.privacy === 'private') {
				roomPassword = Math.floor(Math.random() * 1000000).toString()
				const encryptedPassword = cryptr.encrypt(roomPassword)
				await this.chatService.updateRoomPassword(room.id, encryptedPassword)
			} else {
				this.sendServerMessage(client, 'Server', 'The room is not private', 'error')
				return
			}
			this.sendServerMessage(client, 'Server', `Current room '${room.name}' new password: ${roomPassword}`, 'info')
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}
		

	private async handleShowRoomPasswordCommand(client: Socket, currentRoom: string) {
		try {
			const room = await this.chatService.findByPk(currentRoom)
			if (room.privacy === 'private') {
				let roomPassword = ''
				if (room.password) {
					try {
						const decryptedPassword = cryptr.decrypt(room.password)
						roomPassword = decryptedPassword
					} catch (error) {
						this.sendServerMessage(client, 'Server', `An error occured during password decryption: ${error.message}`, 'error')
					}
				}
				this.sendServerMessage(client, 'Server', `Current room '${room.name}' password: ${roomPassword}`, 'info')
			} else {
				this.sendServerMessage(client, 'Server', 'The room is not private', 'error')
				return
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}
	
	private async handleBroadcastCommand(client: Socket, user: UserModel, message: string) {
		try {
			if (client.data.user.isAdmin) {
				this.socketGateway.server.emit('receivedRoomMessage', {
					type: 'broadcast',
					id: 0,
					senderId: user.id,
					sender: user,
					room: this.socketGateway.mainRoom.id,
					text: message
				})
			} else {
				this.sendServerMessage(client, 'Server', `You are not allowed to use this command`, 'error')
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async sendCurrentRoomMessage(client: Socket, user: UserModel, currentRoom: string, message: string) {
		if (!currentRoom) {
			this.sendServerMessage(client, 'Server', 'You must join a room to be able to send messages', 'error')
			return
		}
		try {
			const mutedUser = await this.chatService.findMutedUser(currentRoom, user.id)
			if (mutedUser) {
				const currentTime = new Date(Date.now())
				if (currentTime >= mutedUser.muteEnd) {
					mutedUser.destroy()
				} else {
					this.sendServerMessage(client, 'Server', `You have been muted until ${mutedUser.muteEnd}`, 'info')
					return
				}
			}
			message = message.trim()
			const newMessage = await this.chatService.createRoomMessage(user.id, currentRoom, message)
			if (!newMessage || !newMessage.sender) {
				this.sendServerMessage(client, 'Server', 'Failed to send message', 'error')
			} else {
				this.socketGateway.server.to(currentRoom).emit('receivedRoomMessage', {
					type: 'default',
					id: newMessage.id,
					senderId: newMessage.senderId,
					sender: newMessage.sender,
					room: currentRoom,
					text: message
				})
			}
		} catch (error) {
			this.sendServerMessage(client, 'Server', error.message, 'error')
		}
	}

	private async sendConversationMessage(client: Socket, user: UserModel, recipient: number, message: string) {
		if (!recipient || !message) {
			client.emit('errorMessage', 'You must specify a recipient and a message')
		} else {
			if (message.length < 1 || message.length > 250) {
				client.emit('errorMessage', 'Invalid message length: Message length must be between 1 and 250 characters')
			} else {
				try {
					const userRecipient = await this.userService.findByPk(recipient)
					if (!userRecipient) {
						client.emit('errorMessage', `Unknown user: '${recipient}'`)
					} else {
						const blockedUsers = await this.relationshipService.getBlockedUsers(user.id)
						const recipientBlockedUsers = await this.relationshipService.getBlockedUsers(recipient)
						if (blockedUsers.includes(recipient)) {
							client.emit('errorMessage', "You cannot send a message to a user you blocked")
						} else if (recipientBlockedUsers.includes(user.id)) {
							client.emit('errorMessage', "You cannot send a message to a user who blocked you")
						} else {
							const socketId = await this.socketService.findSocketIdById(userRecipient.id, 'chat')
							if (socketId) {
								const newMessage = await this.chatService.createConversationMessage(client.data.user.id, userRecipient.id, message)
								if (!newMessage || !newMessage.sender) {
									client.emit('errorMessage', 'Failed to send message')
									this.sendServerMessage(client, 'Server', 'Failed to send message', 'error')
								} else {
									this.socketGateway.server.to(socketId).emit('receivedConversationMessage', {
										senderId: user.id,
										sender: user,
										recipientId: userRecipient.id,
										text: message,
									})
								}
							} else {
								await this.chatService.createConversationMessage(client.data.user.id, userRecipient.id, message)
							}
							client.emit('receivedConversationMessage', {
								id: userRecipient.id,
								senderId: user.id,
								sender: user,
								recipientId: userRecipient.id,
								text: message,
							})
						}
					}
				} catch (error) {
					this.sendServerMessage(client, 'Server', error.message, 'error')
				}
			}
		}
	}

	private async handleClearCommand(client: Socket) {
		client.emit('clearChat')
	}

	private sendServerMessage(client: Socket, username: string, message: string, type: string) {
		this.socketGateway.server.to(client.id).emit('receivedRoomMessage', {
			type: type,
			id: 0,
			senderId: 0,
			sender: {
				id: 0,
				username: username,
				avatar: 'default.png'
			},
			room: client.id,
			text: message
		})
	}

	private sendServerRoomMessage(room: string, username: string, message: string, type: string) {
		this.socketGateway.server.to(room).emit('receivedRoomMessage', {
			type: type,
			id: 0,
			senderId: 0,
			sender: {
				id: 0,
				username: username,
				avatar: 'default.png'
			},
			room: room,
			text: message
		})
	}

	private async sendUsersJoinedCountUpdate(room: string) {
		const usersJoined = await this.chatService.getJoinedUsersCount(room)
		this.socketGateway.server.to(room).emit('usersJoined', {
			id: room,
			usersJoined
		})
	}

	async handleSendInvitation(client: Socket, invitation: Invitation) {
		if (invitation.recipient === invitation.sender) {
			client.emit('errorMessage', 'You cannot send an invitation to yourself')
			return
		}
		if (client.data.user.id !== invitation.sender) {
			client.emit('errorMessage', 'Invitation sender is not matching your user id')
			return
		}
		try {
			const user = await this.userService.findByPk(invitation.sender)
			const senderClient = this.gameService.findClientById(invitation.sender)
			const recipientClient = this.gameService.findClientById(invitation.recipient)
			const blockedUsers = await this.relationshipService.getBlockedUsers(user.id)
			const recipientBlockedUsers = await this.relationshipService.getBlockedUsers(invitation.recipient)
			if (blockedUsers.includes(invitation.recipient)) {
				client.emit('errorMessage', "You cannot send an invitation to a user you blocked")
				return
			} else if (recipientBlockedUsers.includes(user.id)) {
				client.emit('errorMessage', "You cannot send an invitation to a user who blocked you")
				return
			}
			if (user) {
				if (!senderClient) {
					client.emit('errorMessage', "Player is not online")
					return
				}
				if (recipientClient) {
					const room = this.gameService.gameRooms.get(senderClient.playerState.currentRoom)
					if (!room) {
						client.emit('errorMessage', "You must be in a room before sending an invitation")
						return
					}
					if (room.state.gameState > GameState.Lobby) {
						client.emit('errorMessage', 'A game has already started in this room')
						return
					}
					if (room.clients.length > room.maxClients && room.locked) {
						client.emit('errorMessage', 'Room is full')
						return
					}
					const newInvitation = await this.gameService.createInvitation(room.roomId, invitation.sender, invitation.recipient)
					invitation.id = newInvitation.id
					invitation.roomId = newInvitation.roomId
					invitation.username = user.username
					invitation.avatarUrl = getGameAssetUrl('avatar', user.avatar)
					recipientClient.client.send('receivedInvitation', invitation)
				} else {
					client.emit('errorMessage', 'Player is not online')
				}
			} else {
				client.emit('errorMessage', `Couldn't retrieve user`)
			}
		} catch (error) {
			client.emit('errorMessage', `Error while sending invitation : ${error}`)
		}
	}
}
