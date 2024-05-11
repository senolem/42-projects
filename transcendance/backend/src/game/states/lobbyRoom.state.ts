import { MapSchema, Schema, Context, type } from '@colyseus/schema'
import { PlayerState } from '@/src/game/states/player.state'

export class LobbyRoomState extends Schema {
	@type( { map: PlayerState })
	players = new MapSchema<PlayerState>()
}
