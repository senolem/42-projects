import { Injectable, Inject, forwardRef, Logger } from '@nestjs/common'
import { InjectModel } from '@nestjs/sequelize'
import { Client, matchMaker } from '@colyseus/core'
import { GameRoom } from '@/src/game/rooms/game.room'
import { PlayerState } from '@/src/game/states/player.state'
import { GameRoomState } from '@/src/game/states/gameRoom.state'
import { GameService } from '@/src/game/game.service'
import { SocketService } from '@/src/socket/socket.service'
import { UserService } from '@/src/user/user.service'
import { UserModel } from '@/src/user/user.model'
import { GameState } from '@/src/enums/gameState.enum'

@Injectable()
export class GameEvents {
	constructor (
		@Inject(forwardRef(() => GameService))
		private readonly gameService: GameService,
		@Inject(forwardRef(() => SocketService))
		private readonly socketService: SocketService,
		@Inject(forwardRef(() => UserService))
		private readonly userService: UserService,
		@InjectModel(UserModel)
		private userModel: typeof UserModel
	) {}

	handleClientReady(client: Client, playerState: PlayerState, state: GameRoomState)
	{
		if (state.gameState < GameState.PlayersLoading) {
			client.send('server_error', 'Game has not started yet')
			return
		}
		if (state.leftPlayer === client.id) {
			state.players.get(state.leftPlayer).clientReady = true
		} else if (state.rightPlayer === client.id) {
			state.players.get(state.rightPlayer).clientReady = true
		}
	}

	handleClientReconnectedReady(client: Client, playerState: PlayerState, state: GameRoomState) {
		if (state.gameState === GameState.Paused) {
			playerState.clientLoaded = true
		}
	}

	async handleSetReady(client: Client, playerState: PlayerState, room: GameRoom) {
		try {
			let isEveryoneReady = true
			room.state.players.forEach(player => {
				if (player.ready != true) {
					isEveryoneReady = false
				}
			})
			if (room.state.gameState > GameState.Lobby || room.state.countdownStarted || (isEveryoneReady && room.state.players.size > 1)) {
				client.send('server_error', 'You cannot change your ready set once everyone in the room is ready')
				return
			}
			playerState.ready = !playerState.ready
			room.state.players.set(client.id, playerState)

			isEveryoneReady = true
			room.state.players.forEach(player => {
				if (player.ready != true) {
					isEveryoneReady = false
				}
			})

			if (isEveryoneReady && !room.state.countdownStarted && room.state.gameState === GameState.Lobby && room.state.players.size > 1) {
				room.startGame()
			}
		} catch (error) {
			Logger.error(`Failed to handle set ready ${error}`, 'Colyseus')
			client.send('server_error', 'Failed to set ready')
		}
	}

	async handleSetSelectedMap(client: Client, playerState: PlayerState, state: GameRoomState, selectedMap: number) {
		if (!state.countdownStarted && state.gameState === GameState.Lobby && state.owner === playerState.id) {
			const map = await this.gameService.findMapByPk(selectedMap)
			if (!map) {
				client.send('server_error', 'Invalid map selected')
				return
			}
			state.selectedMap = selectedMap
		}
	}

	async handleCreateRoom(client: Client, player: PlayerState): Promise<matchMaker.SeatReservation> {
		try {
			const matchMakingPlayer = this.gameService.matchmakingPlayers.get(player.id)
			if (matchMakingPlayer) {
				client.send('server_error', 'You cannot create a room if you joined matchmaking')
			}
			if (!player.currentRoom) {
				const user = await this.userModel.findByPk(client.userData.id)
				if (!user || !user.session) {
					client.send('server_error', 'Failed to fetch user data. Try disconnecting and reconnecting.')
					player.currentRoom = null
					return
				}
				const reservation = await matchMaker.create('GameRoom', { accessToken: user.session })
				player.currentRoom = reservation.room.roomId
				client.send('joinRoom', reservation)
				return reservation
			} else {
				client.send('server_error', 'You cannot create a room if you already joined one')
			}
		} catch (error) {
			player.currentRoom = null
			Logger.error(`Failed to handle create room ${error}`, 'Colyseus')
			client.send('server_error', 'Failed to create room')
		}
	}

	async handleLeaveRoom(client: Client, player: PlayerState) {
		try {
			if (player.currentRoom) {
				const room = this.gameService.gameRooms.get(player.currentRoom)
				if (room.state.countdownStarted || room.state.gameState !== GameState.Lobby) {
					client.send('server_error', 'You cannot leave the room now')
					return
				}
				const gameClient = this.gameService.clients.get(client.userData.id)
				const roomClient = room.clients.getById(gameClient.gameSocketId)
				roomClient.leave(1000)
				player.currentRoom = null
				client.send('leaveRoom')
			} else {
				client.send('server_error', 'You did not joined any room')
			}
		} catch (error) {
			player.currentRoom = null
			Logger.error(`Failed to handle leave room ${error}`, 'Colyseus')
			client.send('server_error', 'Failed to leave room')
		}
	}

	async handleAcceptInvitation(client: Client, player: PlayerState, invitationId: string) {
		try {
			const cachedInvitation = await this.gameService.findInvitationById(invitationId)
			if (!cachedInvitation) {
				client.send('server_error', 'Invalid invitation id')
				return
			}
			const room = this.gameService.gameRooms.get(cachedInvitation.roomId)
			if (!room) {
				client.send('server_error', 'Invalid invitation roomId')
				return
			}
			if (room.clients.length > room.maxClients && room.locked) {
				client.send('server_error', 'Room is full')
				return
			}
			if (player.currentRoom) {
				const room = this.gameService.gameRooms.get(player.currentRoom)
				const gameClient = this.gameService.clients.get(client.userData.id)
				const roomClient = room.clients.getById(gameClient.gameSocketId)
				roomClient.leave(1000)
				player.currentRoom = null
				client.send('leaveRoom')
			}
			const user = await this.userModel.findByPk(player.id)
			const reservation = await matchMaker.joinById(cachedInvitation.roomId, { accessToken: user.session })
			player.currentRoom = reservation.room.roomId
			await this.gameService.deleteInvitation(player.id, invitationId)
			client.send('joinRoom', reservation)
		} catch (error) {
			player.currentRoom = null
			Logger.error(`Failed to handle accept invitation ${error}`, 'Colyseus')
			client.send('server_error', 'Failed to accept invitation')
		}
	}

	async handleDeclineInvitation(client: Client, player: PlayerState, invitationId: string) {
		try {
			const cachedInvitation = await this.gameService.findInvitationById(invitationId)
			if (!cachedInvitation) {
				client.send('server_error', 'Invalid invitation roomId')
				return
			}
			await this.gameService.deleteInvitation(player.id, invitationId)
			const sender = this.socketService.findSocketById(cachedInvitation.sender, 'chat')
			const recipient = await this.userService.findByPk(cachedInvitation.recipient)
			if (sender && recipient) {
				sender.emit('errorMessage', `${recipient.username} declined your invitation`)
			}
		} catch (error) {
			Logger.error(`Failed to handle decline invitation ${error}`, 'Colyseus')
			client.send('server_error', 'Failed to decline invitation')
		}
	}

	async handleJoinMatchmaking(client: Client, player: PlayerState) {
		try {
			if (!player.currentRoom) {
				const matchmakingPlayer = this.gameService.matchmakingPlayers.get(client.userData.id)
				if (matchmakingPlayer) {
					client.send('server_error', 'You already joined matchmaking')
				} else {
					const user = await this.userModel.findByPk(client.userData.id)
					this.gameService.matchmakingPlayers.set(client.userData.id, { sessionId: client.sessionId, user: user, joined: this.gameService.lobbyRoom.clock.currentTime })
					client.send('joinedMatchmaking')
				}
			} else {
				client.send('server_error', 'You already joined a room')
			}
		} catch (error) {
			Logger.error(`Failed to join matchmaking ${error}`, 'Colyseus')
			client.send('server_error', 'Failed to join matchmaking')
		}
	}

	async handleLeaveMatchmaking(client: Client) {
		try {
			const matchmakingPlayer = this.gameService.matchmakingPlayers.get(client.userData.id)
			if (matchmakingPlayer) {
				if (matchmakingPlayer.roomId) {
					client.send('server_error', 'The server is currently waiting for your opponent to join. Wait until being switched back to matchmaking search to leave')
				} else {
					this.gameService.matchmakingPlayers.delete(client.userData.id)
					client.send('leftMatchmaking')
				}
			} else {
				client.send('server_error', 'You did not joined matchmaking')
			}
		} catch (error) {
			Logger.error(`Failed to leave matchmaking ${error}`, 'Colyseus')
			client.send('server_error', 'Failed to leave matchmaking')
		}
	}
}
