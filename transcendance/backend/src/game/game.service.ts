import { Injectable, Inject, forwardRef, OnApplicationShutdown, Logger, OnModuleInit } from '@nestjs/common'
import * as http from 'http'
import { Server, Client, Room, matchMaker } from 'colyseus'
import { WebSocketTransport } from '@colyseus/ws-transport'
import { InjectModel } from '@nestjs/sequelize'
import { Op } from 'sequelize'
import { AuthService } from '@/src/auth/auth.service'
import { GameEvents } from '@/src/game/game.events'
import { SocketService } from '@/src/socket/socket.service'
import { UserModel } from '@/src/user/user.model'
import { LobbyRoom } from '@/src/game/rooms/lobby.room'
import { GameRoom } from '@/src/game/rooms/game.room'
import { GameClient } from '@/src/interfaces/gameClient.interface'
import { InvitationModel } from '@/src/game/invitation.model'
import { MapModel } from '@/src/game/map.model'
import { MapData } from '@/src/interfaces/mapData.interface'
import { getGameAssetUrl } from '@/src/helpers'
import { ScoresService } from '@/src/scores/scores.service'
import { MatchmakingPlayer } from '@/src/interfaces/matchmakingPlayer.interface'
import { MatchmakingRoom } from '@/src/interfaces/matchmakingRoom.interface'
import { ReconnectionData } from '@/src/interfaces/reconnectionData'

type Type<T> = new (...args: any[]) => T

@Injectable()
export class GameService implements OnApplicationShutdown, OnModuleInit {
	constructor (
		private readonly authService: AuthService,
		@Inject(forwardRef(() => GameEvents))
		private readonly gameEvents: GameEvents,
		@Inject(forwardRef(() => SocketService))
		private readonly socketService: SocketService,
		@InjectModel(UserModel)
		private userModel: typeof UserModel,
		@InjectModel(InvitationModel)
		private invitationModel: typeof InvitationModel,
		@InjectModel(MapModel)
		private mapModel: typeof MapModel,
		@Inject(ScoresService)
		private readonly scoresService: ScoresService
	) {}

	server: Server = null
	lobbyRoom: LobbyRoom = null
	gameRooms: Map<string, GameRoom> = new Map<string, GameRoom>()
	clients: Map<number, GameClient> = new Map<number, GameClient>()
	matchmakingPlayers: Map<number, MatchmakingPlayer> = new Map<number, MatchmakingPlayer>()
	matchmakingRooms: Map<string, MatchmakingRoom> = new Map<string, MatchmakingRoom>()
	maxWaitingTime = 15 * 1000 // After 15 seconds, matchmaking expectations are lowered
	maxTimeout = 15 * 1000 // After 15 seconds, if not both players joined the created room, the room is deleted and players sent back to menu
	reconnectionData: Map<number, ReconnectionData> = new Map<number, ReconnectionData>()

	async onModuleInit() {
		await this.initMaps()
	}

	async createServer(httpServer: http.Server) {
		if (this.server)
			return

		this.server = await new Server({
			transport: new WebSocketTransport({
				server: httpServer
			})
		})
		matchMaker.controller.exposedMethods = ['join', 'joinById', 'reconnect']
	}

	async defineRooms(rooms: Type<Room<any, any>>[]) {
		for (let room of rooms) {
			this.server.define(room.name, room, { authService: this.authService, gameService: this, gameEvents: this.gameEvents, socketService: this.socketService, userModel: this.userModel })
			Logger.log(`${room.name} defined`, 'Colyseus')
			switch (room.name) {
				case 'LobbyRoom':
					await matchMaker.createRoom('LobbyRoom', {})
					break
			}
		}
	}

	findLobbySocketIdById(id: number): string | undefined {
		const client = this.clients.get(id)
		if (client) {
			return client.lobbySocketId
		}
		return undefined
	}

	findGameSocketIdById(id: number): string | undefined {
		const client = this.clients.get(id)
		if (client) {
			return client.gameSocketId
		}
		return undefined
	}

	findClientById(id: number): GameClient | undefined {
		const client = this.clients.get(id)
		return client
	}

	onApplicationShutdown(sig) {
		if (!this.server)
			return
		console.info(`Caught signal ${sig}. Game server shutting down on ${new Date()}.`)
		this.server.gracefullyShutdown()
	}

	async findInvitationById(invitationId: string) {
		try {
			return await this.invitationModel.findOne({
				where: {
					id: invitationId
				}
			})
		} catch (error) {
			console.error(`Error while finding invitation : ${error.message}`)
		}
	}

	async createInvitation(roomId: string, sender: number, recipient: number): Promise<InvitationModel> {
		try {
			return await this.invitationModel.create({ roomId, sender, recipient })
		} catch (error) {
			console.error(`Error while creating invitation : ${error.message}`)
		}
	}

	async deleteInvitation(userId: number, invitationId: string): Promise<void> {
		try {
			const invitation = await this.invitationModel.findOne({
				where: {
					id: invitationId,
					[Op.or]: [{ sender: userId }, { recipient: userId }],
				}
			})

			await invitation.destroy()
		} catch (error) {
			console.error(`Error while deleting invitation : ${error.message}`)
		}
	}

	async initMaps() {
		let maps: MapData[] = []
		maps.push({ displayName: 'Classic', thumbnailUrl: 'classic.png', backgroundUrl: 'classic.png', musicUrl: 'classic.wav'})
		maps.push({ displayName: 'France', thumbnailUrl: 'france.png', backgroundUrl: 'france.png', musicUrl: 'france.wav'})
		maps.forEach(async (value) => {
			const existingMap = await this.mapModel.findOne({
				where: {
					displayName: {
						[Op.eq]: value.displayName
					}
				}
			})
			if (!existingMap) {
				const newMap = {
					displayName: value.displayName,
					thumbnail: value.thumbnailUrl,
					background: value.backgroundUrl,
					music: value.musicUrl,
				}
				this.mapModel.create(newMap as MapModel)
				Logger.log(`Created map ${value.displayName}`, 'Maps')
			}
		})
	}

	async getMaps(): Promise<MapData[]> {
		const mapsData: MapData[] = []
		const maps = await this.mapModel.findAll()
		maps.forEach((map, index) => {
			mapsData.push({
				id: map.id,
				displayName: map.displayName,
				thumbnailUrl: getGameAssetUrl('thumbnail', map.thumbnail),
				backgroundUrl: getGameAssetUrl('background', map.background),
				musicUrl: getGameAssetUrl('music', map.music)
			})
		})
		return mapsData
	}

	async findMapByPk(id: number): Promise<MapModel> {
		return await this.mapModel.findByPk(id)
	}

	async addScore(player1: number, player2: number, player1Score: number, player2Score: number, winByForfeit: boolean, duration: number, player1Xp: number, player2Xp: number): Promise<UserModel> {
		let winner: number
		if (player1Score > player2Score) {
			winner = player1
			await this.scoresService.create(player1, player2, player1Score, player2Score, winByForfeit, duration, player1Xp + 500, player2Xp)
		} else if (player2Score > player1Score) {
			winner = player2
			await this.scoresService.create(player1, player2, player1Score, player2Score, winByForfeit, duration, player1Xp, player2Xp + 500)
		}
		let user: UserModel
		if (winner) {
			const currentConsecutiveVictories = await this.scoresService.countConsecutiveVictories(winner)
			user = await this.userModel.findByPk(winner)
			user.xp += 500
			user.totalVictories += 1
			if (currentConsecutiveVictories > user.victoriesInARow) {
				user.victoriesInARow = currentConsecutiveVictories
			}
			await user.save()
		}

		return user
	}

	getCompatibleOpponent(id: number, xp: number, lowerExpectations: boolean): MatchmakingPlayer {
		for (let [key, value] of this.matchmakingPlayers) {
			if (id !== key && (Math.abs(value.user.xp - xp) <= 1000 || lowerExpectations)) {
				return value
			}
		}
		return null
	}

	getReconnectionData(id: number): ReconnectionData {
		return this.reconnectionData.get(id)
	}

	setReconnectionData(id: number, data: ReconnectionData): void {
		this.reconnectionData.set(id, data)
	}

	deleteReconnectionData(id: number): void {
		this.reconnectionData.delete(id)
	}
}
