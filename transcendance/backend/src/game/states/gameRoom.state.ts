import { MapSchema, Schema, type } from '@colyseus/schema'
import { PlayerState } from '@/src/game/states/player.state'
import { GameState } from '@/src/enums/gameState.enum'
import { EntityState } from '@/src/game/states/entity.state'

export class GameRoomState extends Schema {
	@type({ map: PlayerState })
	players = new MapSchema<PlayerState>()
	@type({ map: EntityState })
	entities = new MapSchema<EntityState>()
	@type('string')
	leftPlayer: string
	@type('string')
	rightPlayer: string
	@type('boolean')
	countdownStarted: boolean = false
	@type('number')
	gameState: GameState = GameState.Lobby
	@type('number')
	countdown: number = 0
	@type('number')
	selectedMap: number = 1
	@type('number')
	owner: number = -1
	@type('number')
	created: number
	@type('number')
	tick: number
}
