import { Req, Res, Next, Injectable, NestMiddleware, Inject, forwardRef } from '@nestjs/common'
import { config } from '@/config'
import { UserService } from '@/src/user/user.service'
import { AuthService } from '@/src/auth/auth.service'
const jwt = require('jsonwebtoken')

@Injectable()
export class AuthenticationMiddleware implements NestMiddleware {
	constructor(
		private readonly userService: UserService,
		@Inject(forwardRef(() => AuthService))
		private readonly authService: AuthService
	) {}

	async use(@Req() req, @Res() res, @Next() next) {
		const authorizationHeader = req.headers.authorization
		const sessionId = req.cookies.session
		if (authorizationHeader) {
			if (authorizationHeader.split(' ').length !== 2) {
				return res.status(401).json({ statusCode: 401, success: false, message: 'You need to provide an "Authorization: Bearer" header containing your token in your request headers. Please try again' })
			}
			const token = req.headers.authorization.split(' ')[1]
			if (token) {
				try {
					const decoded = jwt.verify(token, config.jwtSecret)
					const user = await this.userService.findByPk(decoded.userId)
					req.session.isAdmin = user.isAdmin
					req.session.userId = decoded.userId
					return next()
				} catch (error) {
					return res.status(401).json({ statusCode: 401, success: false, message: `Invalid token : ${error}` })
				}
			} else {
				return res.status(401).json({ statusCode: 401, success: false, message: 'You need to provide an "Authorization: Bearer" header containing your token in your request headers. Please try again' })
			}
		} else if (sessionId) {
			try {
				if (sessionId === 'UNITY') { // DELETE THIS AFTER DEVELOPMENT
					return next()
				}
				const decodedUserID = this.authService.verifyToken(sessionId)
				const user = await this.userService.findByPk(decodedUserID)
				if (!user) {
					return res.status(401).json({ statusCode: 401, success: false, message: 'Invalid Session ID' })
				}
				req.session.isAdmin = user.isAdmin
				req.session.userId = decodedUserID
				return next()
			} catch (error) {
				return res.status(401).json({ statusCode: 401, success: false, message: `Invalid Session ID : ${error}` })
			}
		} else {
			return res.status(401).json({ statusCode: 401, success: false, message: `Authentication failed: You need either a valid token in your "Authorization: Bearer" header or provide a "session" cookie with a valid Session ID` })
		}
	}
}
