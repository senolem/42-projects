import { MapSchema, Schema, Context, type } from '@colyseus/schema'
import { BodyType, ShapeType } from 'cannon-es'
import { CocosBodyType, EntityType } from '@/src/game/worldEntity'

export class Vect3 extends Schema {
    @type("number")
	x: number = 0
    @type("number")
	y: number = 0
	@type("number")
	z: number = 0
}

export class Quater extends Schema {
    @type("number")
	x: number = 0
    @type("number")
	y: number = 0
	@type("number")
	z: number = 0
	@type("number")
	w: number = 0
}

export class EntityState extends Schema {
	@type('string')
	id: string = ''
	@type(Vect3)
	position: Vect3 = new Vect3()
	@type(Quater)
	quaternion: Quater = new Quater()
	@type(Vect3)
	size: Vect3 = new Vect3()
	@type('number')
	mass: number
	@type(Vect3)
	velocity: Vect3 = new Vect3()
	@type(Vect3)
	angularVelocity: Vect3 = new Vect3()
	@type('number')
	bodyType: CocosBodyType
	@type('number')
	shapeType: ShapeType
	@type('string')
	texture: string = ''
	@type('number')
	entityType: EntityType = EntityType.Default
	@type(Vect3)
	linearFactor: Vect3 = new Vect3()
	@type('number')
	linearDamping: number = 0.01
	@type('boolean')
	fixedRotation: boolean
	@type("number")
	baseSpeed: number = 0
}
