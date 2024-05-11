import { Controller, Get, Post, Delete, Param, Res, Req } from '@nestjs/common'
import { RelationshipService } from '@/src/relationship/relationship.service'

@Controller('relationships')
export class RelationshipController {
	constructor(
		private readonly relationshipService: RelationshipService
	) {}

	@Get('friends')
	async getFriends(@Req() req, @Res() res): Promise<void> {
		try {
			const userId = req.session.userId
			const friends = await this.relationshipService.getFriends(userId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully fetched friends for user ${userId}`, data: { friends } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to fetch friends: ${error}` })
		}
	}

	@Get(':userId/friends')
	async getUserFriends(@Res() res, @Param('userId') userId: number): Promise<void> {
		try {
			const friends = await this.relationshipService.getFriends(userId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully fetched friends for user ${userId}`, data: { friends } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to fetch friends: ${error}` })
		}
	}

	@Post('friends/:friendId')
	async sendFriendRequest(@Req() req, @Res() res, @Param('friendId') friendId: number) {
		try {
			const userId = req.session.userId
			const friendRequest = await this.relationshipService.sendFriendRequest(userId, friendId)
			res.status(201).json({ statusCode: 201, success: true, message: `Successfully sent friend request from user ${userId} to user ${friendId}`, data: { friendRequest } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to send friend request: ${error}` })
		}
	}

	@Delete('friends/:friendId')
	async deleteFriend(@Req() req, @Res() res, @Param('friendId') friendId: number) {
		try {
			const userId = req.session.userId
			const friend = await this.relationshipService.deleteFriend(userId, friendId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully deleted user ${friendId} by user ${userId}`, data: { friend } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to send friend request: ${error}` })
		}
	}

	@Get('friends/pending')
	async getPendingRequests(@Req() req, @Res() res): Promise<void> {
		try {
			const userId = req.session.userId
			const pendingRequests = await this.relationshipService.getPendingRequests(userId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully fetched pending requests for user ${userId}`, data: { pendingRequests } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to fetch pending requests: ${error}` })
		}
	}

	@Post('friends/accept/:friendId')
	async acceptFriendRequest(@Req() req, @Res() res, @Param('friendId') friendId: number) {
		try {
			const userId = req.session.userId
			const friend = await this.relationshipService.acceptFriendRequest(userId, friendId)
			res.status(201).json({ statusCode: 201, success: true, message: `Successfully accepted friend request from user ${userId} to user ${friendId}`, data: { friend } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to accept friend request: ${error}` })
		}
	}

	@Delete('friends/pending/:friendId')
	async cancelPendingRequest(@Req() req, @Res() res, @Param('friendId') friendId: number) {
		try {
			const userId = req.session.userId
			const friend = await this.relationshipService.cancelPendingRequest(userId, friendId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully deleted friend request to user ${friendId} by user ${userId}`, data: { friend } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to delete the friend request: ${error}` })
		}
	}

	@Get('blocked')
	async getBlockedUsers(@Req() req, @Res() res): Promise<void> {
		try {
			const userId = req.session.userId
			const blockedUsers = await this.relationshipService.getBlockedUsers(userId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully fetched blocked users for user ${userId}`, data: { blockedUsers } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to fetch blocked users: ${error}` })
		}
	}

	@Get('blocked/:id')
	async getBlockedUser(@Req() req, @Res() res, @Param('id') blockedId: number): Promise<void> {
		try {
			const userId = req.session.userId
			const blockedUser = await this.relationshipService.getBlockedUser(userId, blockedId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully fetched blocked user for user ${userId}`, data: { blockedUser } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to fetch blocked user: ${error}` })
		}
	}

	@Post('blocked/:id')
	async blockUser(@Req() req, @Res() res, @Param('id') blockedId: number) {
		try {
			const userId = req.session.userId
			const blocked = await this.relationshipService.blockUser(userId, blockedId)
			res.status(201).json({ statusCode: 201, success: true, message: `Successfully blocked user ${blockedId} for user ${userId}`, data: { blocked } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to block user: ${error}` })
		}
	}

	@Delete('blocked/:id')
	async unblockUser(@Req() req, @Res() res, @Param('id') blockedId: number) {
		try {
			const userId = req.session.userId
			const unblocked = await this.relationshipService.unblockUser(userId, blockedId)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully unblocked user ${blockedId} for user ${userId}`, data: { unblocked } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to unblock user: ${error}` })
		}
	}

	@Get('friends/:id')
	async fetchRelationStatus(@Req() req, @Res() res, @Param('id') id: number) {
		try {
			const userId = await req.session.userId
			const relationship = await this.relationshipService.fetchRelationStatus(userId, id)
			res.status(200).json({ statusCode: 200, success: true, message: `Successfully fetched the status of the relationship between user ${userId} and user ${id}`, data: { relationship } })
		} catch (error) {
			res.status(400).json({ statusCode: 400, success: false, message: `Failed to fetch any info about the existing relationship : ${error}` })
		}
	}
}
