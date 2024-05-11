import { Logger } from '@nestjs/common'
import { Room, Client, ServerError, Delayed } from 'colyseus'
import { GameRoomState } from '@/src/game/states/gameRoom.state'
import { InputState, PlayerState } from '@/src/game/states/player.state'
import { GameService } from '@/src/game/game.service'
import { AuthService } from '@/src/auth/auth.service'
import { GameEvents } from '@/src/game/game.events'
import { IncomingMessage } from 'http'
import { SocketService } from '@/src/socket/socket.service'
import { UserModel } from '@/src/user/user.model'
import { getGameAssetUrl } from '@/src/helpers'
import { GameState } from '@/src/enums/gameState.enum'
import { Box, ContactMaterial, Material, Quaternion, Vec3, World } from 'cannon-es'
import { WorldEntity, ShapeType, EntityType, CocosBodyType } from '@/src/game/worldEntity'
import { EndGameScreenData } from '@/src/interfaces/endGameScreenData.interface'

export class GameRoom extends Room<GameRoomState> {
	private authService: AuthService
	private gameService: GameService
	private gameEvents: GameEvents
	private socketService: SocketService
	private userModel: typeof UserModel

	private leftPlayer: PlayerState
	private rightPlayer: PlayerState
	
	private world: World
	private entities: Map<string, WorldEntity> = new Map<string, WorldEntity>
	private topWall: string
	private bottomWall: string
	private leftWall: string
	private rightWall: string
	private leftPaddle: string
	private rightPaddle: string
	private ball: string
	
	private ballSpeed: number
	private ballPaddleContactMaterial: ContactMaterial

	private startCountdown: Delayed
	private disposeDelayed: Delayed
	private started: number
	private ended: number

	// Game logic stuff
	private leftWallCollision: boolean
	private rightWallCollision: boolean
	private leftPaddleCollision: boolean
	private rightPaddleCollision: boolean

	maxClients = 2
	autoDispose = false

	startGame() {
		Logger.log(`Starting game in room ${this.roomId}`, 'Colyseus')
		this.state.entities.clear()
		this.state.gameState = GameState.Starting
		this.leftWallCollision = false
		this.rightWallCollision = false
		this.leftPaddleCollision = false
		this.rightPaddleCollision = false

		// Reset and start countdown
		this.state.countdownStarted = true
		this.state.countdown = 5
		this.state.tick = 0

		// Set left & right players
		const players = this.state.players.keys()
		this.state.leftPlayer = players.next().value
		this.state.rightPlayer = players.next().value
		this.leftPlayer = this.state.players.get(this.state.leftPlayer)
		this.rightPlayer = this.state.players.get(this.state.rightPlayer)
		this.leftPlayer.score = 0
		this.rightPlayer.score = 0

		this.startCountdown = this.clock.setInterval(() => {
			this.state.countdown -= 1
		}, 1000)

		this.clock.setTimeout(() => {
			this.startCountdown.clear()
			this.state.countdown = 0
			this.state.countdownStarted = false
			this.state.players.forEach((value) => {
				value.ready = false
			})
			this.state.gameState = GameState.PlayersLoading
			this.broadcast('loadingScreen')

			// Create materials
			const ballMaterial = new Material('ball')
			const surfaceMaterial = new Material('paddle')
			this.ballPaddleContactMaterial = new ContactMaterial(ballMaterial, surfaceMaterial, {
				friction: 0.0,
				restitution: 1.0,
				contactEquationStiffness: 1e6,
				contactEquationRelaxation: 10
			})
			this.world.addContactMaterial(this.ballPaddleContactMaterial)

			// Create walls
			const topWall = new WorldEntity(
				this.world,
				this.state,
				new Vec3(0, 335, 0),
				new Quaternion(0, 0, 0, 1),
				new Vec3(1280, 50, 50),
				0,
				0,
				ShapeType.Box,
				CocosBodyType.Static,
				'topWall',
				EntityType.LeftWall,
				{
					linearFactor: new Vec3(0, 0, 0),
					linearDamping: 0,
					material: surfaceMaterial
				}
			)
			this.topWall = topWall.id
			this.entities.set(topWall.id, topWall)

			const bottomWall = new WorldEntity(
				this.world,
				this.state,
				new Vec3(0, -335, 0),
				new Quaternion(0, 0, 0, 1),
				new Vec3(1280, 50, 50),
				0,
				0,
				ShapeType.Box,
				CocosBodyType.Static,
				'bottomWall',
				EntityType.BottomWall,
				{
					linearFactor: new Vec3(0, 0, 0),
					linearDamping: 0,
					material: surfaceMaterial
				}
			)
			this.bottomWall = bottomWall.id
			this.entities.set(bottomWall.id, bottomWall)

			const leftWall = new WorldEntity(
				this.world,
				this.state,
				new Vec3(-615, 0, 0),
				new Quaternion(0, 0, 0, 1),
				new Vec3(50, 720, 50),
				0,
				0,
				ShapeType.Box,
				CocosBodyType.Static,
				'leftWall',
				EntityType.LeftWall,
				{
					linearFactor: new Vec3(0, 0, 0),
					linearDamping: 0,
					material: surfaceMaterial
				}
			)
			this.leftWall = leftWall.id
			this.entities.set(leftWall.id, leftWall)

			const rightWall = new WorldEntity(
				this.world,
				this.state,
				new Vec3(615, 0, 0),
				new Quaternion(0, 0, 0, 1),
				new Vec3(50, 720, 50),
				0,
				0,
				ShapeType.Box,
				CocosBodyType.Static,
				'rightWall',
				EntityType.RightWall,
				{
					linearFactor: new Vec3(0, 0, 0),
					linearDamping: 0,
					material: surfaceMaterial
				}
			)
			this.rightWall = rightWall.id
			this.entities.set(rightWall.id, rightWall)

			// Reset values and create paddles
			this.leftPlayer.clientReady = false
			this.leftPlayer.clientLoaded = false
			this.leftPlayer.inputs.assign({ upward: false, downward: false, powerup: false })
			const leftPaddle = new WorldEntity(
				this.world,
				this.state,
				new Vec3(-560, 0, 0),
				new Quaternion(0, 0, 0, 1),
				new Vec3(35, 150, 50),
				300,
				100.0,
				ShapeType.Box,
				CocosBodyType.Dynamic,
				'paddle',
				EntityType.LeftPaddle,
				{
					linearFactor: new Vec3(0, 1, 0),
					linearDamping: 0.5,
					material: surfaceMaterial,
					fixedRotation: true
				}
			)
			this.leftPaddle = leftPaddle.id
			this.entities.set(leftPaddle.id, leftPaddle)

			this.rightPlayer.clientReady = false
			this.rightPlayer.clientLoaded = false
			this.rightPlayer.inputs.assign({ upward: false, downward: false, powerup: false })
			const rightPaddle = new WorldEntity(
				this.world,
				this.state,
				new Vec3(560, 0, 0),
				new Quaternion(0, 0, 0, 1),
				new Vec3(35, 150, 50),
				300,
				100.0,
				ShapeType.Box,
				CocosBodyType.Dynamic,
				'paddle',
				EntityType.RightPaddle,
				{
					linearFactor: new Vec3(0, 1, 0),
					linearDamping: 0.5,
					material: surfaceMaterial,
					fixedRotation: true
				}
			)
			this.rightPaddle = rightPaddle.id
			this.entities.set(rightPaddle.id, rightPaddle)

			// Create ball
			const ball = new WorldEntity(
				this.world,
				this.state,
				new Vec3(0, 0, 0),
				new Quaternion(0, 0, 0, 1),
				new Vec3(35, 35, 35),
				500,
				1.0,
				ShapeType.Sphere,
				CocosBodyType.Dynamic,
				'ball',
				EntityType.Ball,
				{
					linearFactor: new Vec3(1, 1, 0),
					linearDamping: 0,
					material: ballMaterial,
					fixedRotation: true
				}
			)
			this.ball = ball.id
			this.entities.set(ball.id, ball)
			this.ballSpeed = 500

			this.broadcast('loadGame')

			this.clock.setTimeout(() => {
				if (!this.leftPlayer.clientReady || !this.rightPlayer.clientReady) {
					if (!this.leftPlayer.clientReady && !this.rightPlayer.clientReady) {
						this.broadcast('server_error', 'Both players did not loaded in time. Going back to menu')
					} else if (!this.leftPlayer.clientReady && this.rightPlayer.clientReady) {
						this.broadcast('server_error', `${this.leftPlayer.username} did not loaded in time. Going back to menu`)
					} else if (this.leftPlayer.clientReady && !this.rightPlayer.clientReady) {
						this.broadcast('server_error', `${this.rightPlayer.username} did not loaded in time. Going back to menu`)
					}
					this.state.gameState = GameState.Lobby
					this.broadcast('loadMenu')
				} else {
					this.broadcast('startGame')
					this.clock.setTimeout(() => {
						this.started = new Date().getTime()
						if (this.leftPlayer.connected && this.rightPlayer.connected) {
							this.state.gameState = GameState.Playing
						} else {
							this.state.gameState = GameState.Paused
						}
						this.checkCollisions()

						const ball = this.entities.get(this.ball)
						ball.body.velocity.set(ball.baseSpeed, 0, 0)
					}, 3000)
				}
			}, 5000)
		}, 5000)
	}

	async endGame(disconnected: number = 0) {
		if (this.state.gameState !== GameState.Ended && this.state.gameState !== GameState.Lobby) {
			this.state.gameState = GameState.Ended
			this.entities.forEach((entity) => {
				entity.destroy()
			})
			this.world.removeContactMaterial(this.ballPaddleContactMaterial)
			this.ended = new Date().getTime()
			const duration = this.ended - this.started
			let winByForfeit = false

			if (disconnected) {
				if (disconnected === this.leftPlayer.id) {
					if (this.rightPlayer.score <= this.leftPlayer.score) {
						this.rightPlayer.score = this.leftPlayer.score + 1
					}
				} else if (disconnected === this.rightPlayer.id) {
					if (this.leftPlayer.score <= this.rightPlayer.score) {
						this.leftPlayer.score = this.rightPlayer.score + 1
					}
				}
				winByForfeit = true
			}

			let endGameScreenData: EndGameScreenData
			const winner = await this.gameService.addScore(this.leftPlayer.id, this.rightPlayer.id, this.leftPlayer.score, this.rightPlayer.score, winByForfeit, duration, this.leftPlayer.xp, this.rightPlayer.xp)
			if (winner) {
				const socketId = this.gameService.findGameSocketIdById(winner.id)
				const player = this.state.players.get(socketId)
				if (player) {
					player.xp = winner.xp
				}
				let loser = winner.id === this.leftPlayer.id ? this.rightPlayer.id : this.leftPlayer.id
				endGameScreenData = {
					username: winner.username,
					avatarUrl: getGameAssetUrl('avatar', winner.avatar),
					leftPlayerScore: this.leftPlayer.score,
					rightPlayerScore: this.rightPlayer.score,
					leftPlayerXp: winner.id === this.leftPlayer.id ? winner.xp : this.leftPlayer.xp,
					rightPlayerXp: winner.id === this.rightPlayer.id ? winner.xp : this.rightPlayer.xp,
					winner: winner.id,
					loser
				}
			} else {
				endGameScreenData = {
					username: 'Nobody',
					avatarUrl: '',
					leftPlayerScore: this.leftPlayer.score,
					rightPlayerScore: this.rightPlayer.score,
					leftPlayerXp: this.leftPlayer.xp,
					rightPlayerXp: this.rightPlayer.xp,
					winner: 0,
					loser: 0
				}
			}
			this.broadcast('endGame', endGameScreenData)
			this.broadcast('status', { title: 'Game end', message: 'Game ended, switching you back to lobby in 5 seconds...' })
			this.clock.setTimeout(() => {
				this.state.gameState = GameState.Lobby
				this.broadcast('loadMenu')
				this.leftPlayer.score = 0
			}, 5000)
		}
	}

	private update(deltaTime: number) {
		if (this.state.gameState !== GameState.Playing) {
			return
		}
		
		++this.state.tick
		this.updateLogic()
		this.updatePhysics(deltaTime)
		this.updateStates()
	}

	updateLogic() {
		const ball = this.entities.get(this.ball)
		const leftPaddle = this.entities.get(this.leftPaddle)
		const rightPaddle = this.entities.get(this.rightPaddle)

		if (this.leftPlayer.score > 9 || this.rightPlayer.score > 9) {
			this.endGame()
			return
		}

		if (this.leftWallCollision) {
			this.rightPlayer.score += 1
			this.reset()
			ball.body.velocity.set(ball.baseSpeed, 0, 0)
			this.leftWallCollision = false
		}
		if (this.rightWallCollision) {
			this.leftPlayer.score += 1
			this.reset()
			ball.body.velocity.set(-ball.baseSpeed, 0, 0)
			this.rightWallCollision = false
		}

		if (this.leftPaddleCollision) {
			this.adjustBallVelocity(leftPaddle)
			this.leftPaddleCollision = false
		}
		if (this.rightPaddleCollision) {
			this.adjustBallVelocity(rightPaddle)
			this.rightPaddleCollision = false
		}
	}

	updatePhysics(deltaTime: number) {
		this.world.fixedStep()
		this.movePaddles()
		this.updateBallVelocity()
	}

	updateBallVelocity() {
		const ball = this.entities.get(this.ball)

		let velocity = ball.body.velocity

		let currentSpeed = velocity.length()

		let direction = new Vec3(velocity.x, velocity.y, velocity.z)
		direction.normalize()

		if (this.ballSpeed < 1000) {
			this.ballSpeed += 0.4
		}

		if (currentSpeed < this.ballSpeed) {
			currentSpeed = this.ballSpeed
		}

		velocity.x = direction.x * currentSpeed
		velocity.y = direction.y * currentSpeed
		velocity.z = direction.z * currentSpeed

		ball.body.velocity = velocity
	}

	adjustBallVelocity(entity: WorldEntity) {
		const ball = this.entities.get(this.ball)

		const impactPoint = entity.body.position.y - ball.body.position.y
		let paddleHeight = 0
		if (entity.shape instanceof Box) {
			paddleHeight = entity.shape.halfExtents.y
		} else {
			return
		}
		const normalizedImpactPoint = impactPoint / paddleHeight
		const verticalVelocityFactor = normalizedImpactPoint * Math.abs(ball.baseSpeed)
		let newVerticalVelocity = verticalVelocityFactor

		if (normalizedImpactPoint > 0) {
			newVerticalVelocity = -Math.abs(newVerticalVelocity)
		} else {
			newVerticalVelocity = Math.abs(newVerticalVelocity)
		}

		ball.body.velocity.set(ball.body.velocity.x, newVerticalVelocity, ball.body.velocity.z)
	}

	updateStates() {
		this.entities.forEach((entity) => {
			entity.updateState()
		})
	}
	
	movePaddles() {
		const leftPaddle = this.entities.get(this.leftPaddle)
		const rightPaddle = this.entities.get(this.rightPaddle)

		if (leftPaddle && this.leftPlayer) {
			if (this.leftPlayer.inputs.upward && !this.leftPlayer.inputs.downward) {
				leftPaddle.body.velocity.set(0, leftPaddle.baseSpeed, 0)
			} else if (!this.leftPlayer.inputs.upward && this.leftPlayer.inputs.downward) {
				leftPaddle.body.velocity.set(0, -leftPaddle.baseSpeed, 0)
			} else {
				leftPaddle.body.velocity.set(0, 0, 0)
			}
		}
		
		if (rightPaddle && this.rightPlayer) {
			if (this.rightPlayer.inputs.upward && !this.rightPlayer.inputs.downward) {
				rightPaddle.body.velocity.set(0, rightPaddle.baseSpeed, 0)
			} else if (!this.rightPlayer.inputs.upward && this.rightPlayer.inputs.downward) {
				rightPaddle.body.velocity.set(0, -rightPaddle.baseSpeed, 0)
			} else {
				rightPaddle.body.velocity.set(0, 0, 0)
			}
		}
	}

	checkCollisions() {
		const ball = this.entities.get(this.ball)
		const leftWall = this.entities.get(this.leftWall)
		const rightWall = this.entities.get(this.rightWall)
		const leftPaddle = this.entities.get(this.leftPaddle)
		const rightPaddle = this.entities.get(this.rightPaddle)

		// Collision with left wall
		leftWall.body.addEventListener('collide', (event) => {
			if (event.body.id === ball.body.id) {
				this.leftWallCollision = true
			}
		})

		// Collision with right wall
		rightWall.body.addEventListener('collide', (event) => {
			if (event.body.id === ball.body.id) {
				this.rightWallCollision = true
			}
		})

		leftPaddle.body.addEventListener('collide', (event) => {
			if (event.body.id === ball.body.id) {
				this.leftPaddleCollision = true
			}
		})
	
		// Collision with right paddle
		rightPaddle.body.addEventListener('collide', (event) => {
			if (event.body.id === ball.body.id) {
				this.rightPaddleCollision = true
			}
		})
	}

	reset() {
		this.entities.get(this.leftPaddle).reset()
		this.entities.get(this.rightPaddle).reset()
		this.ballSpeed = 500
		this.entities.get(this.ball).reset()
	}

	onCreate(options: any) {
		this.authService = options.authService
		this.gameService = options.gameService
		this.gameEvents = options.gameEvents
		this.socketService = options.socketService
		this.userModel = options.userModel

		this.world = new World({
			gravity: new Vec3(0, 0, 0)
		})

		this.clock.start()
		this.setSimulationInterval((deltaTime) => this.update(deltaTime))
		this.setState(new GameRoomState())
		this.state.created = this.clock.currentTime
		this.gameService.gameRooms.set(this.roomId, this)
		Logger.log(`New GameRoom created (${this.roomId})`, 'Colyseus')

		// Game events
		this.onMessage('setReady', (client) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleSetReady(client, player, this)
		})

		this.onMessage('setSelectedMap', (client, selectedMap: number) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleSetSelectedMap(client, player, this.state, selectedMap)
		})

		this.onMessage('clientReady', (client) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleClientReady(client, player, this.state)
		})

		this.onMessage('clientReconnectedReady', (client) => {
			const player = this.state.players.get(client.sessionId)
			this.gameEvents.handleClientReconnectedReady(client, player, this.state)
		})

		this.onMessage('updateInputs', (client, inputs: InputState) => {
			const player = this.state.players.get(client.sessionId)

			if (!inputs || !player || inputs.upward === undefined || inputs.downward === undefined || inputs.powerup === undefined) {
				return
			}

			if (client.sessionId === this.state.leftPlayer || client.sessionId === this.state.rightPlayer) {
				player.inputs.assign({ upward: inputs.upward, downward: inputs.downward, powerup: inputs.powerup })
			}
		})
	}

	async onAuth(client: Client, options: any, request: IncomingMessage) {
		if (request.headers.cookies || options.accessToken) {
			let user
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
			const gameClient = this.gameService.clients.get(client.userData.id)
			gameClient.gameSocketId = client.id

			if (this.state.owner === -1) {
				this.state.owner = user.id
			}
			return true
		} else {
			if (this.state.players.size <= 0) {
				this.autoDispose = true
			}
			throw new ServerError(401, 'Authentication failed: You need either a valid token in your "Authorization: Bearer" header or provide a "session" cookie with a valid Session ID')
		}
	}

	async onJoin(client: Client, options: any) {
		if (this.disposeDelayed) {
			this.disposeDelayed.clear()
			this.disposeDelayed = null
		}
		// Send available maps
		client.send('setMaps', await this.gameService.getMaps())

		// Create a new player state, add the informations from the retrieved user and add it to the room's players map
		const user = await this.userModel.findByPk(client.userData.id)
		const playerState = new PlayerState()
		playerState.assign({
			id: user.id,
			username: user.username,
			avatarUrl: getGameAssetUrl('avatar', user.avatar),
			xp: user.xp,
			usernameColor: user.usernameColor,
			connected: true
		})
		this.state.players.set(client.sessionId, playerState)

		user.status = 4
		await user.save()
		Logger.log(`${client.sessionId} (${user.username}) joined ${this.roomId} (GameRoom)`, 'Colyseus')
	}

	async onLeave(client: Client, consented: boolean) {
		let disconnected: number = -1
		try {
			let playerState = this.state.players.get(client.sessionId)
			playerState.connected = false

			if ((this.state.gameState > GameState.Lobby && this.state.gameState != GameState.Ended) && (playerState.id === this.leftPlayer.id || playerState.id === this.rightPlayer.id)) {
				this.state.gameState = GameState.Paused
				try {
					this.broadcast('status', { title: 'Game paused', message: `One of the players disconnected. They have 15 seconds to reconnect.` })
					this.broadcast('status', { title: 'Player disconnected', message: `${playerState.username} has been disconnected.` })
					this.gameService.setReconnectionData(playerState.id, { reconnectionToken: client._reconnectionToken, roomId: this.roomId })
					const newClient = await this.allowReconnection(client, 15)
					this.gameService.deleteReconnectionData(playerState.id)

					if (client.sessionId !== newClient.sessionId) {
						if (client.sessionId === this.state.leftPlayer) {
							this.state.leftPlayer = newClient.sessionId
						} else if (client.sessionId === this.state.rightPlayer) {
							this.state.rightPlayer = newClient.sessionId
						}

						this.state.players.set(newClient.sessionId, playerState)
						this.state.players.delete(client.sessionId)
					}

					playerState = this.state.players.get(newClient.sessionId)
					playerState.connected = true
					if (this.leftPlayer.connected === true && this.rightPlayer.connected === true) {
						newClient.send('setMaps', await this.gameService.getMaps())
						this.broadcast('status', { title: 'Player reconnected', message: `${playerState.username} reconnected.` })
						let timeout = 5000
						const assetsLoadingInterval = this.clock.setInterval(() => {
							if (playerState.clientLoaded) {
								assetsLoadingInterval.clear()
								newClient.userData = client.userData
								const gameClient = this.gameService.findClientById(newClient.userData.id)
								gameClient.gameSocketId = newClient.sessionId
								gameClient.playerState.currentRoom = this.roomId
								playerState.clientLoaded = false
								newClient.send('startGame')
								this.state.gameState = GameState.Playing
							} else {
								if (timeout > 0) {
									timeout -= 100
								} else {
									assetsLoadingInterval.clear()
									newClient.leave()
								}
							}
						}, 100)
					}
				} catch (error) {
					console.error(error)
					this.broadcast('status', { title: 'Game terminated', message: `One of the players timed out. The game has been terminated.` })

					this.gameService.deleteReconnectionData(playerState.id)
					disconnected = playerState.id
					const user = await this.userModel.findByPk(client.userData.id)

					user.status = 3
					await user.save()
					const gameClient = this.gameService.clients.get(client.userData.id)
					if (gameClient) {
						gameClient.gameSocketId = null
					}
					if (client.userData.id && this.state.owner === client.userData.id) {
						for (const value of this.state.players) {
							if (value[1].id !== client.userData.id) {
								this.state.owner = value[1].id
								break
							}
						}
					}
					throw new Error('Reconnection timeout')
				}
			} else {
				this.state.players.delete(client.sessionId)

				if (this.clients.length === 0) {
					if (this.state.gameState === GameState.Lobby) {
						this.autoDispose = true
					} else {
						this.disposeDelayed = this.clock.setTimeout(() => {
							this.autoDispose = true
						}, 15000)
					}
				}
				const user = await this.userModel.findByPk(client.userData.id)

				user.status = 3
				await user.save()
				const gameClient = this.gameService.clients.get(client.userData.id)
				if (gameClient) {
					gameClient.gameSocketId = null
				}
				if (client.userData.id && this.state.owner === client.userData.id) {
					for (const value of this.state.players) {
						if (value[1].id !== client.userData.id) {
							this.state.owner = value[1].id
							break
						}
					}
				}
			}
		} catch (error) {
			if (this.clients.length != 2 && this.state.gameState != GameState.Lobby) {
				this.endGame(disconnected)
			}
			this.state.players.delete(client.sessionId)
			if (this.clients.length === 0) {
				this.autoDispose = true
			}
		}
		
		Logger.log(`${client.sessionId} left ${this.roomId} (GameRoom) (${consented ? 'consented' : 'not consented'})`, 'Colyseus')
	}

	onDispose() {
		this.gameService.gameRooms.delete(this.roomId)
		Logger.log(`Disposing room: ${this.roomId} (GameRoom)`, 'Colyseus')
	}
}
