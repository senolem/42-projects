import { Injectable, Res } from '@nestjs/common'
import { PassportStrategy } from '@nestjs/passport'
import { HttpService } from '@nestjs/axios'
import { Strategy } from 'passport-42'
import { User42 } from '@/src/interfaces/user42.interface'
import { config } from '@/config'

@Injectable()
export class StrategyAuth42 extends PassportStrategy(Strategy, 'transcendance') {
	constructor(private readonly httpService: HttpService) {
		super({
			clientID: config.auth.uid,
			clientSecret: config.auth.secret,
			callbackURL: config.auth.callback
		})
	}

	validate(accessToken: string, refreshToken: string, user: User42): User42 {
		return user
	}
}
