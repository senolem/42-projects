import { BODY_TYPES, Body, BodyType, Box, Material, Quaternion, Shape, Sphere, Vec3, World } from 'cannon-es'
import { GameRoomState } from '@/src/game/states/gameRoom.state'
import { EntityState, Quater, Vect3 } from '@/src/game/states/entity.state'
import { v4 as uuidv4 } from 'uuid'

export enum ShapeType {
	Sphere = 1,
	Box
}

export enum CocosBodyType {
	Static = 1,
	Dynamic,
	Kinematic
}

export enum EntityType {
	TopWall = 1,
	BottomWall,
	LeftWall,
	RightWall,
	LeftPaddle,
	RightPaddle,
	Ball,
	Default
}

export class WorldEntity {
	public id: string
	public body: Body
	public shape: Box | Sphere
	public state: EntityState
	public baseSpeed: number
	public basePosition: Vec3 = new Vec3(0, 0, 0)
	public baseQuaternion: Quaternion = new Quaternion(0, 0, 0, 0)
	private world: World
	private gameRoom: GameRoomState

	constructor(
		world: World,
		gameRoom: GameRoomState,
		position: Vec3,
		quaternion: Quaternion,
		size: Vec3,
		baseSpeed: number,
		mass: number,
		shapeType: ShapeType,
		bodyType: CocosBodyType,
		texture: string,
		entityType: EntityType,
		options: {
			linearFactor?: Vec3,
			linearDamping?: number,
			material?: Material
			fixedRotation?: boolean
		}
	) {
		// Generate uuid for the entity
		this.id = uuidv4()

		// Base position, quaternion and speed
		this.basePosition.copy(position)
		this.baseQuaternion.copy(quaternion)
		this.baseSpeed = baseSpeed

		// Create shape
		switch (shapeType) {
			case ShapeType.Sphere:
				this.shape = new Sphere(size.x / 2)
				break
			case ShapeType.Box:
				this.shape = new Box(new Vec3(size.x / 2, size.y / 2, size.z / 2))
				break
			default:
				throw new Error('Unsupported shape type')
		}

		// Create body
		let cannonBodyType: BodyType
		switch (bodyType) {
			case CocosBodyType.Dynamic:
				cannonBodyType = BODY_TYPES.DYNAMIC
				break

			case CocosBodyType.Static:
				cannonBodyType = BODY_TYPES.STATIC
				break

			case CocosBodyType.Kinematic:
				cannonBodyType = BODY_TYPES.KINEMATIC
				break
		}
		this.body = new Body({
			type: cannonBodyType,
			position: position,
			quaternion: quaternion,
			shape: this.shape,
			mass: mass
		})

		// Assign values to the entity state
		const entityState = new EntityState()
		const entityPosition = new Vect3()
		const entityQuaternion = new Quater()
		const entitySize = new Vect3()

		entityPosition.assign({ x: position.x, y: position.y, z: position.z })
		entityQuaternion.assign({ x: quaternion.x, y: quaternion.y, z: quaternion.z, w: quaternion.w })
		entitySize.assign({ x: size.x, y: size.y, z: size.z })
		entityState.assign({
			id: this.id,
			position: entityPosition,
			quaternion: entityQuaternion,
			size: entitySize,
			mass: mass,
			bodyType: bodyType,
			shapeType: shapeType,
			texture: texture,
			entityType: entityType,
			baseSpeed: baseSpeed
		})
		gameRoom.entities.set(this.id, entityState)

		// Options
		if (options.linearFactor) {
			const entityLinearFactor = new Vect3()
			entityLinearFactor.assign({ x: options.linearFactor.x, y: options.linearFactor.y, z: options.linearFactor.z })

			this.body.linearFactor = options.linearFactor
			entityState.assign({ linearFactor: entityLinearFactor })
		}
		if (options.linearDamping) {
			this.body.linearDamping = options.linearDamping
			entityState.assign({ linearDamping: options.linearDamping })
		}
		if (options.material) {
			this.body.material = options.material
		}
		if (options.fixedRotation) {
			this.body.fixedRotation = options.fixedRotation
			this.body.updateMassProperties() // Needed when changing a body's fixedRotation state
			entityState.assign({ fixedRotation: options.fixedRotation })
		}

		// Add body to world
		world.addBody(this.body)

		// Store references
		this.world = world
		this.state = entityState
		this.gameRoom = gameRoom
	}

	updateState() {
		this.state.position.assign({ x: this.body.position.x, y: this.body.position.y, z: this.body.position.z })
		this.state.quaternion.assign({ x: this.body.quaternion.x, y: this.body.quaternion.y, z: this.body.quaternion.z, w: this.body.quaternion.w })
		this.state.velocity.assign({ x: this.body.velocity.x, y: this.body.velocity.y, z: this.body.velocity.z })
		this.state.angularVelocity.assign({ x: this.body.angularVelocity.x, y: this.body.angularVelocity.y, z: this.body.angularVelocity.z })
	}

	reset() {
		this.body.position.copy(this.basePosition)
		this.body.quaternion.copy(this.baseQuaternion)
		this.body.velocity.setZero()
		this.body.angularVelocity.setZero()
		this.body.inertia.setZero()
		this.body.torque.setZero()
	}

	destroy() {
		this.world.removeBody(this.body)
		if (this.gameRoom.entities.get(this.id)) {
			this.gameRoom.entities.delete(this.id)
		}
	}
}
