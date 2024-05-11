import { Client } from 'colyseus'
import { PlayerState } from '@/src/game/states/player.state'

export interface GameClient {
	lobbySocketId: string
	gameSocketId: string
	client: Client
	playerState: PlayerState
}
