import { Injectable, NotFoundException, ForbiddenException, Inject, forwardRef } from '@nestjs/common'
import { Op } from 'sequelize'
import { UserModel } from '@/src/user/user.model'
import { FriendModel } from '@/src/relationship/friend.model'
import { BlockedModel } from '@/src/relationship/blocked.model'
import { UserService } from '@/src/user/user.service'
import { SocketService } from '@/src/socket/socket.service'

@Injectable()
export class RelationshipService {
	constructor(
		@Inject(forwardRef(() => UserService))
		private readonly userService: UserService,
		private readonly socketService: SocketService
	) {}

	async getFriends(userId: number) {
		const user = await UserModel.findByPk(userId, {
			include: [
				{
					model: FriendModel,
					as: 'outgoingFriendRequests',
					include: [
						{
							model: UserModel,
							as: 'recipient',
							attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'background', 'totalVictories', 'victoriesInARow']
						}
					]
				},
				{
					model: FriendModel,
					as: 'incomingFriendRequests',
					include: [
						{
							model: UserModel,
							as: 'sender',
							attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'background', 'totalVictories', 'victoriesInARow']
						}
					]
				}
			]
		})

		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}
		const friends: UserModel[] = []
		for (const friendRequest of user.outgoingFriendRequests) {
			if (friendRequest.accepted) {
				friends.push(friendRequest.recipient)
			}
		}

		for (const friendRequest of user.incomingFriendRequests) {
			if (friendRequest.accepted) {
				friends.push(friendRequest.sender)
			}
		}
		return friends
	}

	async sendFriendRequest(userId: number, friendId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const friend = await this.userService.findByPk(friendId)
		if (!friend) {
			throw new NotFoundException(`User not found with ID ${friendId}`)
		}

		if (friend.id === user.id) {
			throw new ForbiddenException(`You cannot send a request to yourself`)
		}
	
		if (await this.isBlockedBy(friendId, userId)) {
			throw new Error(`Cannot send friend request. User with ID ${friendId} has blocked user with ID ${userId}`)
		}

		if (await this.isBlockedBy(userId, friendId)) {
			throw new Error(`Cannot send friend request. User with ID ${userId} has blocked user with ID ${friendId}`)
		}

		const existingRelationship = await FriendModel.findOne({
			where: {
				senderId: {
					[Op.or]: [userId, friendId]
				},
				recipientId: {
					[Op.or]: [userId, friendId]
				},
				accepted: {
					[Op.or]: [false, true]
				}
			}
		})

		if (existingRelationship) {
			if (existingRelationship.accepted === true) {
				throw new Error(`Users with ID ${userId} and ${friendId} are already friends`)
			}
			throw new Error(`Friend request already sent to user with ID ${friendId}`)
		} else {
			const friendRequest = await FriendModel.create({
				senderId: userId,
				recipientId: friendId,
				accepted: false
			})
			const id = this.socketService.findSocketIdById(friendId, 'chat')
			if (id) {
				this.socketService.sendUpdateProfile(id, [user?.username, friend?.username])
			}
			return friendRequest
		}
	}
	
	async deleteFriend(userId: number, friendId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const friend = await this.userService.findByPk(friendId)
		if (!friend) {
			throw new NotFoundException(`User not found with ID ${friendId}`)
		}

		const existingRelationship = await FriendModel.findOne({
			where: {
				senderId: {
					[Op.or]: [userId, friendId]
				},
				recipientId: {
					[Op.or]: [userId, friendId]
				},
				accepted: {
					[Op.or]: [false, true]
				}
			}
		})

		if (existingRelationship) {
			await existingRelationship.destroy()
			const id = this.socketService.findSocketIdById(friendId, 'chat')
			if (id) {
				this.socketService.sendUpdateProfile(id, [user?.username, friend?.username])
			}
			return existingRelationship
		} else {
			throw new NotFoundException(`No existing relationship found between ID ${userId} and ${friendId}`)
		}
	}

	async getPendingRequests(userId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const pendingRequests = await FriendModel.findAll({
			where: {
				recipientId: user.id,
				accepted: false
			},
			include: [
				{
					model: UserModel,
					as: 'sender',
					attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'background', 'totalVictories', 'victoriesInARow']
				},
				{
					model: UserModel,
					as: 'recipient',
					attributes: ['id', 'username', 'avatar', 'xp', 'isAdmin', 'usernameColor', 'textColor', 'background', 'totalVictories', 'victoriesInARow']
				}
			]
		})
		return pendingRequests
	}

	async acceptFriendRequest(userId: number, friendId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const friend = await this.userService.findByPk(friendId)
		if (!friend) {
			throw new NotFoundException(`User not found with ID ${friendId}`)
		}

		const pendingRequest = await FriendModel.findOne({
			where: {
				senderId: friendId,
				recipientId: userId,
				accepted: false
			}
		})

		if (!pendingRequest) {
			throw new NotFoundException(`No pending friend request from user with ID ${friendId}`)
		}

		pendingRequest.accepted = true
		await pendingRequest.save()
		const id = this.socketService.findSocketIdById(friendId, 'chat')
		if (id) {
			this.socketService.sendUpdateProfile(id, [user?.username, friend?.username])
		}
		return friend
	}

	async cancelPendingRequest(userId: number, friendId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const friend = await this.userService.findByPk(friendId)
		if (!friend) {
			throw new NotFoundException(`User not found with ID ${friendId}`)
		}

		const existingRelationship = await FriendModel.findOne({
			where: {
				senderId: {
					[Op.or]: [userId, friendId]
				},
				recipientId: {
					[Op.or]: [userId, friendId]
				},
				accepted: {
					[Op.or]: [false, true]
				}
			}
		})

		if (existingRelationship && !existingRelationship.accepted) {
			await existingRelationship.destroy()
			const id = this.socketService.findSocketIdById(friendId, 'chat')
			if (id) {
				this.socketService.sendUpdateProfile(id, [user?.username, friend?.username])
			}
			return friend
		} else {
			throw new NotFoundException(`No existing relationship found between ID ${userId} and ${friendId}`)
		}
	}

	async getBlockedUsers(userId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const blockedUsers = await BlockedModel.findAll({
			where: {
				userId: user.id
			}
		})

		return blockedUsers.map((blocked) => blocked.blockedUserId)
	}

	async getBlockedUser(userId: number, blockedId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const blockedUser = await BlockedModel.findOne({
			where: {
				userId: userId,
				blockedUserId: blockedId
			}
		})

		if (blockedUser) {
			return true
		}
		return false
	}

	async blockUser(userId: number, blockedId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`Blocking user not found with ID ${userId}`)
		}

		const blockedUser = await this.userService.findByPk(blockedId)
		if (!blockedUser) {
			throw new NotFoundException(`User to block not found with ID ${blockedId}`)
		}

		const alreadyBlocked = await BlockedModel.findOne({
			where: {
				userId: userId,
				blockedUserId: blockedId
			}
		})

		if (alreadyBlocked) {
			throw new Error(`User with ID ${userId} has already blocked user with ID ${blockedId}`)
		}

		const existingRelationship = await FriendModel.findOne({
			where: {
				[Op.or]: [
					{
						senderId: userId,
						recipientId: blockedId,
						accepted: {
							[Op.or]: [true, false]
						},
					},
					{
						senderId: blockedId,
						recipientId: userId,
						accepted: {
							[Op.or]: [true, false]
						},
					},
				],
			},
		})
		
		if (existingRelationship) {
			await existingRelationship.destroy()
		}

		const block = await BlockedModel.create({
			userId: userId,
			blockedUserId: blockedId
		})

		const id = this.socketService.findSocketIdById(blockedId, 'chat')
		if (id) {
			this.socketService.sendUpdateProfile(id, [user?.username, blockedUser?.username])
		}

		return block
	}

	async unblockUser(userId: number, blockedId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const blockedUser = await this.userService.findByPk(blockedId)
		if (!blockedUser) {
			throw new NotFoundException(`User not found with ID ${blockedId}`)
		}

		const alreadyBlocked = await BlockedModel.findOne({
			where: {
				userId: userId,
				blockedUserId: blockedId
			}
		})

		if (!alreadyBlocked) {
			throw new Error(`User with ID ${userId} has not blocked user with ID ${blockedId}`)
		}

		await alreadyBlocked.destroy()
		const id = this.socketService.findSocketIdById(blockedId, 'chat')
		if (id) {
			this.socketService.sendUpdateProfile(id, [user?.username, blockedUser?.username])
		}
		return alreadyBlocked
	}

	async isBlockedBy(userId: number, targetId: number) {
		const blocked = await BlockedModel.findOne({
			where: {
				userId: targetId,
				blockedUserId: userId,
			},
		})
		return blocked ? true : false
	}

	async fetchRelationStatus(userId: number, friendId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const friend = await this.userService.findByPk(friendId)
		if (!friend) {
			throw new NotFoundException(`User not found with ID ${friendId}`)
		}

		const existingRelationship = await FriendModel.findOne({
			where: {
				senderId: {
					[Op.or]: [userId, friendId]
				},
				recipientId: {
					[Op.or]: [userId, friendId]
				},
				accepted: {
					[Op.or]: [false, true]
				}
			}
		})
		return existingRelationship
	}

	async areFriends(userId: number, friendId: number) {
		const user = await this.userService.findByPk(userId)
		if (!user) {
			throw new NotFoundException(`User not found with ID ${userId}`)
		}

		const friend = await this.userService.findByPk(friendId)
		if (!friend) {
			throw new NotFoundException(`User not found with ID ${friendId}`)
		}

		const existingRelationship = await FriendModel.findOne({
			where: {
				senderId: {
					[Op.or]: [userId, friendId]
				},
				recipientId: {
					[Op.or]: [userId, friendId]
				},
				accepted: true
			}
		})
		return existingRelationship ? true : false
	}
}
