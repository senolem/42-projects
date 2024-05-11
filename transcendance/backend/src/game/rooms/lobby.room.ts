import { Inject, forwardRef, Logger } from '@nestjs/common'
import { Room, Client, ServerError, matchMaker } from '@colyseus/core'
import { LobbyRoomState } from '@/src/game/states/lobbyRoom.state'
import { PlayerState } from '@/src/game/states/player.state'
import { GameService } from '@/src/game/game.service'
import { AuthService } from '@/src/auth/auth.service'
import { GameEvents } from '@/src/game/game.events'
import { IncomingMessage } from 'http'
import { SocketService } from '@/src/socket/socket.service'
import { UserModel } from '@/src/user/user.model'
import { GameClient } from '@/src/interfaces/gameClient.interface'
import { getUserAvatarUrl } from '@/src/helpers'

export class LobbyRoom extends Room<LobbyRoomState> {
	private authService: AuthService
	private gameService: GameService
	private gameEvents: GameEvents
	private socketService: SocketService
	private userModel: typeof UserModel

	autoDispose = false

	onCreate(options: any) {
		this.authService = options.authService
		this.gameService = options.gameService
		this.gameEvents = options.gameEvents
		this.socketService = options.socketService
		this.userModel = options.userModel

		this.clock.start()
		this.setSimulationInterval((deltaTime) => this.update(deltaTime), 1000) // Update matchmaking every 1s
		this.setState(new LobbyRoomState())
		this.gameService.lobbyRoom = this
		Logger.log(`New LobbyRoom created (${this.roomId})`, 'Colyseus')

		this.onMessage('createRoom', (client) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleCreateRoom(client, player)
		})

		this.onMessage('leaveRoom', (client) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleLeaveRoom(client, player)
		})

		this.onMessage('acceptInvitation', (client, invitation) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleAcceptInvitation(client, player, invitation)
		})

		this.onMessage('declineInvitation', (client, invitation) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleDeclineInvitation(client, player, invitation)
		})

		this.onMessage('joinMatchmaking', async (client) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleJoinMatchmaking(client, player)
		})

		this.onMessage('leaveMatchmaking', (client) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleLeaveMatchmaking(client)
		})
	}

	async onAuth(client: Client, options: any, request: IncomingMessage) {
		if (request.headers.cookies || options.accessToken) {
			let user: UserModel
			try {
				let sessionId = this.socketService.getSessionId(request.headers.cookie)
				if (options.accessToken && !sessionId) {
					sessionId = options.accessToken
				} else if (!sessionId) {
					throw new ServerError(401, 'You need to provide a "session" cookie with a valid Session ID')
				}
				user = await this.authService.authSessionId(sessionId)
				client.userData = { id: user.id }
			} catch (error) {
				throw new ServerError(401, error)
			}

			if (!user) {
				throw new ServerError(401, 'Invalid Session ID')
			}

			this.state.players.forEach((value, key) => {
				if (value.id === user.id) {
					throw new ServerError(401, 'You are already connected')
				}
			})
			return true
		} else {
			throw new ServerError(401, 'You need to provide a "session" cookie with a valid Session ID')
		}
	}

	async onJoin(client: Client, options: any) {
		// Send authorization token so the client can make requests to the API
		client.send('setAuthorization', this.authService.generateToken(client.userData.id))

		// Create a new player state, add the informations from the retrieved user and add it to the room's players map
		const user = await this.userModel.findByPk(client.userData.id)
		const playerState = new PlayerState()
		playerState.assign({
			id: user.id,
			username: user.username,
			avatarUrl: getUserAvatarUrl(user.avatar),
			xp: user.xp,
			usernameColor: user.usernameColor
		})
		this.state.players.set(client.sessionId, playerState)

		// Create a new GameClient entity and add it to the clients map
		const newClient: GameClient = {
			lobbySocketId: client.sessionId,
			gameSocketId: '',
			client: client,
			playerState: this.state.players.get(client.sessionId)
		}
		this.gameService.clients.set(client.userData.id, newClient)

		user.status = 3
		await user.save()
		Logger.log(`${client.sessionId} (${user.username}) joined ${this.roomId} (LobbyRoom)`, 'Colyseus')

		const reconnectionData = this.gameService.getReconnectionData(user.id)
		if (reconnectionData) {
			if (!this.gameService.gameRooms.get(reconnectionData.roomId)) {
				this.gameService.deleteReconnectionData(user.id)
			} else {
				client.send('reconnect', `${reconnectionData.roomId}:${reconnectionData.reconnectionToken}`)
			}
		}
	}

	async onLeave(client: Client, consented: boolean) {
		const user = await this.userModel.findByPk(client.userData.id)

		const matchmakingPlayer = this.gameService.matchmakingPlayers.get(client.userData.id)
		if (matchmakingPlayer) {
			if (matchmakingPlayer.roomId) {
				const matchmakingRoom = this.gameService.matchmakingRooms.get(matchmakingPlayer.roomId)
				const room = this.gameService.gameRooms.get(matchmakingPlayer.roomId)

				if (matchmakingRoom && room) {
					let opponent: number
					if (matchmakingRoom.player1 === client.userData.id) {
						opponent = matchmakingRoom.player2
					} else {
						opponent = matchmakingRoom.player1
					}

					const gameClient = this.gameService.findClientById(client.userData.id)
					if (gameClient) {
						const client = room.clients.getById(gameClient.gameSocketId)
						client.leave(1000)
					}

					const opponentGameClient = this.gameService.findClientById(opponent)
					const opponentMatchmakingPlayer = this.gameService.matchmakingPlayers.get(opponent)

					if (opponentGameClient && opponentMatchmakingPlayer) {
						const opponentClient = room.clients.getById(opponentGameClient.gameSocketId)

						opponentMatchmakingPlayer.roomId = null
						opponentClient.leave(1000)
						this.gameService.matchmakingPlayers.delete(client.userData.id)
						this.gameService.matchmakingRooms.delete(matchmakingPlayer.roomId)

						opponentGameClient.client.send('server_error', 'Your opponent did not join the room in time, switching you back to matchmaking')
						opponentGameClient.client.send('leaveRoom')
						opponentGameClient.client.send('joinedMatchmaking')
					}
				}
			} else {
				this.gameService.matchmakingPlayers.delete(client.userData.id)
			}
		}

		this.state.players.delete(client.sessionId)
		this.gameService.clients.delete(client.userData.id)

		const chatId = await this.socketService.findSocketIdById(client.userData.id, 'chat')
		if (chatId) {
			user.status = 2
		} else {
			user.status = 1
		}
		await user.save()
		Logger.log(`${client.sessionId} (${user.username}) left ${this.roomId} (LobbyRoom)`, 'Colyseus')
	}

	onDispose() {
		this.gameService.lobbyRoom = null
		Logger.log(`Disposing room: ${this.roomId} (LobbyRoom)`, 'Colyseus')
	}

	private async update(deltaTime: number) {
		const skipUsers: Array<number> = new Array<number>
		for await (let [id, player] of this.gameService.matchmakingPlayers) {
			if (skipUsers.includes(id)) {
				return
			}
			if (!player.roomId) {
				const waitedFor = this.clock.currentTime - player.joined
				const lowerExpectations = waitedFor > 15000 ? true : false
				const opponent = this.gameService.getCompatibleOpponent(id, player.user.xp, lowerExpectations)
				if (opponent) {
					const room = await matchMaker.createRoom('GameRoom', {})
					player.roomId = room.roomId
					opponent.roomId = room.roomId

					const reservation = await matchMaker.joinById(room.roomId, { accessToken: player.user.session })
					const opponentReservation = await matchMaker.joinById(room.roomId, { accessToken: opponent.user.session })

					const gameClient = this.gameService.findClientById(player.user.id)
					const opponentgameClient = this.gameService.findClientById(opponent.user.id)

					this.gameService.matchmakingRooms.set(room.roomId, { player1: player.user.id, player2: opponent.user.id })
					const unbalanced = Math.abs(player.user.xp - opponent.user.xp) > 5000
					gameClient.client.send('status', { title: 'Matchmaking', message: 'Opponent found, waiting for them to join...' })
					if (lowerExpectations && unbalanced) {
						gameClient.client.send('status', { title: 'Matchmaking', message: 'Matchmaking couldn\'t find a balanced opponent in a fairly time.' })
					}
					gameClient.client.send('joinRoom', reservation)

					opponentgameClient.client.send('status', { title: 'Matchmaking', message: 'Opponent found, waiting for them to join...' })
					if (lowerExpectations && unbalanced) {
						opponentgameClient.client.send('status', { title: 'Matchmaking', message: 'Matchmaking couldn\'t find a balanced opponent in a fairly time.' })
					}
					opponentgameClient.client.send('joinRoom', opponentReservation)
				}
			} else {
				const room = this.gameService.gameRooms.get(player.roomId)
				const matchmakingRoom = this.gameService.matchmakingRooms.get(player.roomId)
				if (room.state.players.size === 2) {
					let opponent: number
					if (matchmakingRoom.player1 === player.user.id) {
						opponent = matchmakingRoom.player2
					} else {
						opponent = matchmakingRoom.player1
					}
					
					this.gameService.matchmakingPlayers.delete(player.user.id)
					this.gameService.matchmakingPlayers.delete(opponent)
					skipUsers.push(opponent)
					this.gameService.matchmakingRooms.delete(player.roomId)

					const client = this.gameService.findClientById(player.user.id)
					const opponentClient = this.gameService.findClientById(opponent)

					client.playerState.currentRoom = room.roomId
					opponentClient.playerState.currentRoom = room.roomId
				} else {
					const waitedFor = this.clock.currentTime - room.state.created
					if (waitedFor > 15000) {
						let playerJoined: PlayerState
						if (room.state.players.size === 1) {
							room.state.players.forEach((roomPlayer, sessionId) => {
								playerJoined = roomPlayer
							})
						}
						if (playerJoined) {
							const gameClient = this.gameService.findClientById(playerJoined.id)
							const client = room.clients.getById(gameClient.gameSocketId)
							let opponent: number

							if (matchmakingRoom.player1 === playerJoined.id) {
								opponent = matchmakingRoom.player2
							} else {
								opponent = matchmakingRoom.player1
							}

							player.roomId = null
							this.gameService.matchmakingPlayers.delete(opponent)
							skipUsers.push(opponent)
							this.gameService.matchmakingRooms.delete(player.roomId)
							client.leave(1000)

							const opponentGameClient = this.gameService.findClientById(opponent)
							opponentGameClient.client.send('status', { title: 'Matchmaking', message: 'You did not joined the matchmaking room in time, sending you back to menu' })
							opponentGameClient.client.send('leftMatchmaking')

							gameClient.client.send('server_error', 'Your opponent did not join the room in time, switching you back to matchmaking')
							gameClient.client.send('leaveRoom')
							client.send('joinedMatchmaking')
						} else {
							const gameClient = this.gameService.findClientById(matchmakingRoom.player1)
							const gameClient2 = this.gameService.findClientById(matchmakingRoom.player2)
							const client = room.clients.getById(gameClient.gameSocketId)
							const client2 = room.clients.getById(gameClient2.gameSocketId)

							this.gameService.matchmakingPlayers.delete(matchmakingRoom.player1)
							skipUsers.push(matchmakingRoom.player1)
							this.gameService.matchmakingPlayers.delete(matchmakingRoom.player2)
							skipUsers.push(matchmakingRoom.player2)
							this.gameService.matchmakingRooms.delete(player.roomId)
							client.leave(1000)
							client2.leave(1000)

							gameClient.client.send('status', { title: 'Matchmaking', message: 'You did not joined the matchmaking room in time, sending you back to menu' })
							gameClient.client.send('leaveRoom')
							gameClient2.client.send('status', { title: 'Matchmaking', message: 'You did not joined the matchmaking room in time, sending you back to menu' })
							gameClient2.client.send('leaveRoom')
						}
					}
				}
			}
		}
	}
}