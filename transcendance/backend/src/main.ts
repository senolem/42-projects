import { NestFactory } from '@nestjs/core'
import { Logger } from '@nestjs/common'
import { LobbyRoom } from '@/src/game/rooms/lobby.room'
import { GameRoom } from '@/src/game/rooms/game.room'
import { AppModule } from '@/src/app.module'
import { config } from '@/config'
import { GameService } from '@/src/game/game.service'
const session = require('express-session')
const cookieParser = require('cookie-parser')

const rooms = [ LobbyRoom, GameRoom ]

async function bootstrap() {
	const app = await NestFactory.create(AppModule)

	app.enableShutdownHooks()
	app.enableCors({
		origin: [
			`${config.network.frontendProtocol}://${config.network.frontendUrl}`,
		],
		methods: ["GET", "POST", "PUT", "DELETE"],
		credentials: true,
	})
	app.use(cookieParser())
	app.use(
		session({
			secret: config.jwtSecret,
			resave: false,
			saveUninitialized: false
		})
	)

	const gameService = app.get(GameService)
	await gameService.createServer(app.getHttpServer())
	await gameService.defineRooms(rooms)

	await app.listen(config.network.backendPort)
	Logger.log(`HTTP Server running on : http://${config.network.backendUrl}`, 'Express')
}
bootstrap()
