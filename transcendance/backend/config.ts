require('dotenv').config()

const required = [
  'DB_HOST',
  'DB_HOST',
  'DB_PORT',
  'DB_USER',
  'DB_PASSWORD',
  'DB_DATABASE',
  'DB_DIALECT',
  'NEST_APP_FRONTEND_PROTOCOL',
  'NEST_APP_FRONTEND_URL',
  'NEST_APP_BACKEND_PROTOCOL',
  'NEST_APP_BACKEND_URL',
  'NEST_APP_BACKEND_PORT',
  'NEST_APP_SOCKETIO_PORT',
  'JWT_SECRET',
  'AUTH_UID',
  'AUTH_SECRET',
  'AUTH_CALLBACK',
  'MAX_CLIENTS_PER_ROOM',
  'TWO_FACTOR_AUTH_APP',
  'ROOM_PASSWORD_SECRET_KEY'
]

required.forEach((envVariable) => {
	if (!process.env[envVariable]) {
		throw new Error(`Environment variable ${envVariable} is missing`)
	}
})

const config = {
	network: {
		frontendProtocol: process.env.NEST_APP_FRONTEND_PROTOCOL,
		frontendUrl: process.env.NEST_APP_FRONTEND_URL,
		backendProtocol: process.env.NEST_APP_BACKEND_PROTOCOL,
		backendUrl: process.env.NEST_APP_BACKEND_URL,
		backendPort: parseInt(process.env.NEST_APP_BACKEND_PORT),
		socketIOPort: parseInt(process.env.NEST_APP_SOCKETIO_PORT)
	},
	db: {
		host: process.env.DB_HOST,
		port: parseInt(process.env.DB_PORT),
		user: process.env.DB_USER,
		password: process.env.DB_PASSWORD,
		database: process.env.DB_DATABASE,
		dialect: process.env.DB_DIALECT
	},
	auth: {
		uid: process.env.AUTH_UID,
		secret: process.env.AUTH_SECRET,
		callback: process.env.AUTH_CALLBACK,
		twoFactorAuthApp: process.env.TWO_FACTOR_AUTH_APP
	},
	jwtSecret: process.env.JWT_SECRET,
	maxClientsPerRoom: parseInt(process.env.MAX_CLIENTS_PER_ROOM),
	roomPasswordSecretKey: process.env.ROOM_PASSWORD_SECRET_KEY
}

export { config }