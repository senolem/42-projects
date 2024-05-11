import { Schema, type, ArraySchema } from '@colyseus/schema'

export class InputState extends Schema {
	@type('boolean')
	upward: boolean = false
	@type('boolean')
	downward: boolean = false
	@type('boolean')
	powerup: boolean = false
}

export class PlayerState extends Schema {
	@type('number')
	id: number = 0
	@type('string')
	username: string = ''
	@type('string')
	avatarUrl: string = ''
	@type('number')
	xp: number = 0
	@type('string')
	usernameColor: string = ''
	@type('string')
	currentRoom: string = ''
	@type('boolean')
	ready: boolean = false
	@type('boolean')
	clientLoaded: boolean = false
	@type('boolean')
	clientReady: boolean = false
	@type('number')
	score: number = 0
	@type('boolean')
	connected: boolean = false
	@type(InputState)
	inputs: InputState = new InputState()
}