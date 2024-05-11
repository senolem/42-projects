import { Injectable, Inject, forwardRef } from '@nestjs/common'
import { Op } from 'sequelize'
import { RoomMessageModel } from '@/src/chat/roomMessage.model'
import { ConversationMessageModel } from '@/src/chat/conversationMessage.model'
import { UserModel } from '@/src/user/user.model'
import { UserService } from '@/src/user/user.service'
import { RelationshipService } from '@/src/relationship/relationship.service'
import { RoomModel } from '@/src/chat/room.model'
import { Room } from '@/src/interfaces/room.interface'
import { MutedUsersModel } from '@/src/chat/mutedUsers.model'
import { ClientRoom } from '@/src/interfaces/clientRoom.interface'

@Injectable()
export class ChatService {
	constructor (
		@Inject(forwardRef(() => UserService))
		private readonly userService: UserService,
		@Inject(forwardRef(() => RelationshipService))
		private readonly relationshipService: RelationshipService
	) {}

	async findAllRoomsMessages(userId: number, limit?: number): Promise<ClientRoom[]> {
		const blockedUsers = await this.relationshipService.getBlockedUsers(userId)
		const rooms = await RoomModel.findAll({
			where: {
				usersJoined: {
					[Op.contains]: [userId]
				}
			},
			attributes: ['id', 'name', 'privacy', 'owner', 'op'],
			include: [
				{
					model: RoomMessageModel,
					as: 'messages',
					order: [['createdAt', 'DESC']],
					limit: limit,
					include: [
						{
							model: UserModel,
							as: 'sender',
							where: {
								id: {
									[Op.notIn]: [...blockedUsers]
								}
							},
							attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor']
						}
					]
				}
			]
		})

		rooms.forEach(room => {
			room.messages.reverse()
		})

		const roomsWithUsersJoined: ClientRoom[] = await Promise.all(
			rooms.map(async (room) => {
				const usersJoined = await this.getJoinedUsersCount(room.id)
				return {
					id: room.id,
					name: room.name,
					privacy: room.privacy,
					usersJoined: usersJoined,
					messages: room.messages
				}
			})
		)

		return roomsWithUsersJoined
	}

	async findAllRooms(userId: number): Promise<Room[]> {
		const rooms = await RoomModel.findAll({
			where: {
				usersJoined: {
					[Op.contains]: [userId]
				}
			},
			attributes: ['id', 'name', 'privacy', 'owner', 'op']
		})

		return rooms
	}

	async findAllRoomUsers(room: string): Promise<UserModel[]> {
		try {
			const currentRoom = await RoomModel.findByPk(room)
			if (!currentRoom) {
				throw new Error(`Could not fetch room`)
			}
			if (currentRoom.usersJoined && currentRoom.usersJoined.length > 0) {
				const users = await UserModel.findAll({
					where: {
						id: currentRoom.usersJoined
					},
					attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor']
				})

				return users
			} else {
				return []
			}
		} catch (error) {
			throw new Error(`Failed to fetch room users: ${error.message}`)
		}
	}

	async findByName(roomName: string): Promise<RoomModel> {
		const room = await RoomModel.findOne({
			where: {
				name: roomName
			}
		})

		return room
	}

	async findByPk(roomId: string): Promise<RoomModel> {
		const room = await RoomModel.findByPk(roomId)

		return room
	}

	async getPublicRooms(): Promise<RoomModel[]> {
		const rooms = await RoomModel.findAll({
			where: {
				privacy: 'public'
			}
		})

		return rooms
	}

	async createRoom(senderId: number, name: string, privacy: string, password?: string) {
		const newRoom = await RoomModel.create({ name: name, privacy: privacy, owner: senderId, op: [senderId], password: password })
		return newRoom
	}

	async roomExists(roomName: string): Promise<boolean> {
		const room = await RoomModel.findOne({
			where: {
				name: roomName
			}
		})

		return !!room
	}

	async addUserToRoom(roomId: string, userId: number, roomName: string): Promise<number[]> {
		try {
			const room = await RoomModel.findByPk(roomId)
			if (!room) {
				throw new Error('Room not found')
			}

			const isUserBlacklisted = room.blacklistedUsers.includes(userId)
			if (isUserBlacklisted) {
				throw new Error(`You have been banned from ${roomName}`)
			}

			const isUserInRoom = room.usersJoined.includes(userId)
			if (!isUserInRoom) {
				room.usersJoined.push(userId)
				room.changed('usersJoined', true)
				await room.save()
			}
			return room.usersJoined
		} catch (error) {
			throw new Error(error.message)
		}
	}
	
	async removeUserFromRoom(roomId: string, userId: number): Promise<number[]> {
		try {
			const room = await RoomModel.findByPk(roomId)
			if (!room) {
				throw new Error('Room not found')
			}

			const isUserInRoom = room.usersJoined.includes(userId)
			if (isUserInRoom) {
				room.usersJoined = room.usersJoined.filter((id) => id !== userId)
				room.changed('usersJoined', true)
				await room.save()
			}
			return room.usersJoined
		} catch (error) {
			throw new Error(`Failed to remove user from room: ${error.message}`)
		}
	}

	async addUserToBlacklist(roomId: string, userId: number): Promise<number[]> {
		try {
			const room = await RoomModel.findByPk(roomId)
			if (!room) {
				throw new Error('Room not found')
			}

			const isUserBlacklisted = room.blacklistedUsers.includes(userId)
			if (!isUserBlacklisted) {
				room.blacklistedUsers.push(userId)
				room.changed('blacklistedUsers', true)
				await room.save()
			}
			return room.blacklistedUsers
		} catch (error) {
			throw new Error(`Failed to add user to blacklist: ${error.message}`)
		}
	}

	async removeUserFromBlacklist(roomId: string, userId: number): Promise<number[]> {
		try {
			const room = await RoomModel.findByPk(roomId)
			if (!room) {
				throw new Error('Room not found')
			}

			const isUserBlacklisted = room.blacklistedUsers.includes(userId)
			if (isUserBlacklisted) {
				room.blacklistedUsers = room.blacklistedUsers.filter((id) => id !== userId)
				room.changed('blacklistedUsers', true)
				await room.save()
			}
			return room.blacklistedUsers
		} catch (error) {
			throw new Error(`Failed to remove user from blacklist: ${error.message}`)
		}
	}

	async isInRoom(userId: number, roomId: string): Promise<boolean> {
		const room = await RoomModel.findByPk(roomId)
		
		if (!room) {
			return false
		}

		return room.usersJoined.includes(userId)
	}

	async getJoinedUsersCount(roomId: string): Promise<number> {
		const room = await RoomModel.findByPk(roomId)

		if (!room || !room.usersJoined) {
			return 0
		}

		return room.usersJoined.length
	}

	async getRoomName(roomId: string): Promise<string> {
		const room = await RoomModel.findByPk(roomId)

		if (!room) {
			return undefined
		}

		return room.name
	}

	async getRoomPrivacy(roomId: string): Promise<string> {
		const room = await RoomModel.findByPk(roomId)

		if (!room) {
			return undefined
		}

		return room.privacy
	}

	async getRoomOwner(roomId: string): Promise<number> {
		const room = await RoomModel.findByPk(roomId)

		if (!room) {
			return -1
		}

		return room.owner
	}

	async getBlacklistedUsers(roomId: string): Promise<number[]> {
		const room = await RoomModel.findByPk(roomId)

		if (!room) {
			return null
		}

		return room.blacklistedUsers
	}

	async isOp(userId: number, roomId: string): Promise<boolean> {
		const room = await RoomModel.findByPk(roomId)

		if (!room) {
			return false
		}

		return room.op.includes(userId)
	}

	async addOp(userId: number, roomId: string): Promise<boolean> {
		const room = await RoomModel.findByPk(roomId)

		if (!room) {
			return false
		}

		const newArr = room.op.push(userId)
		room.changed('op', true)
		await room.save()
		return (true)
	}

	async removeOp(userId: number, roomId: string): Promise<boolean> {
		const room = await RoomModel.findByPk(roomId)

		if (!room) {
			return false
		}

		room.op = room.op.filter((id) => id !== userId)
		room.changed('op', true)
		await room.save()
	
		return (true)
	}

	async createRoomMessage(senderId: number, room: string, text: string) {
		const newMessage = await RoomMessageModel.create({ senderId: senderId, room: room, text: text })
		const sender = await this.userService.findByPk(senderId)
		newMessage.sender = sender
		return newMessage
	}

	async createConversationMessage(senderId: number, recipientId: number, text: string) {
		const newMessage = await ConversationMessageModel.create({ senderId, recipientId, text })
		const sender = await this.userService.findByPk(senderId)
		newMessage.sender = sender
		return newMessage
	}

	async findMutedUser(roomId: string, userId: number): Promise<MutedUsersModel> {
		return await MutedUsersModel.findOne({
			where: {
				roomId: {
					[Op.eq]: roomId
				},
				userId: {
					[Op.eq]: userId
				}
			}
		})
	}

	async muteUser(roomId: string, userId: number, muteEnd: Date): Promise<MutedUsersModel> {
		try {
			const room = await RoomModel.findByPk(roomId)
			if (!room) {
				throw new Error('Room not found')
			}

			const user = await UserModel.findByPk(userId)
			if (!user) {
				throw new Error('Invalid user ID')
			}

			const mutedUser = await this.findMutedUser(roomId, userId)

			if (mutedUser) {
				return await mutedUser.update({ muteEnd })
			} else {
				const newMutedUser = await MutedUsersModel.create({
					roomId,
					userId,
					muteEnd
				})
				return newMutedUser
			}
		} catch (error) {
			throw new Error(`Failed to mute user: ${error.message}`)
		}
	}

	async unmuteUser(roomId: string, userId: number): Promise<void> {
		try {
			const room = await RoomModel.findByPk(roomId)
			if (!room) {
				throw new Error('Room not found')
			}

			const user = await UserModel.findByPk(userId)
			if (!user) {
				throw new Error('Invalid user ID')
			}

			const mutedUser = await this.findMutedUser(roomId, userId)
			if (!mutedUser) {
				throw new Error('The user has not been muted in this room')
			}
			return await mutedUser.destroy()
		} catch (error) {
			throw new Error(`Failed to unmute user: ${error.message}`)
		}
	}

	async updateRoomPassword(roomId: string, newPassword: string): Promise<void> {
		try {
			const room = await RoomModel.findByPk(roomId)
			if (!room) {
				throw new Error('Room not found')
			}
			room.password = newPassword
			await room.save()
		} catch (error) {
			throw new Error(`Failed to update room password: ${error.message}`)
		}
	}
}
