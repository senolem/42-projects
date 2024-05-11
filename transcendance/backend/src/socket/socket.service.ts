import { Inject, Injectable, forwardRef } from '@nestjs/common'
import { Socket } from 'socket.io'
import { SocketIOGateway } from '@/src/socket/socket.gateway'

@Injectable()
export class SocketService {
	constructor(
		private readonly socketGateway: SocketIOGateway
	) {}

	getSessionId(cookie: string): string {
		if (!cookie)
			return null
		const cookies = cookie.split(';')
		let sessionId
		for (const cookie of cookies) {
			const [name, value] = cookie.trim()?.split('=')
			if (name === 'session') {
				sessionId = value
				break
			}
		}
		return sessionId
	}

	findSocketIdById(id: number, type: string): string | undefined {
		let targetMap: Map<string, Socket>

		if (type === 'chat') {
			targetMap = this.socketGateway.chatClients
		} else {
			return undefined
		}
		for (const [socketId, socket] of targetMap) {
			if (socket.data?.user && socket.data.user.id == id) {
				return socketId
			}
		}
		return undefined
	}

	findSocketById(id: number, type: string): Socket | undefined {
		let targetMap: Map<string, Socket>

		if (type === 'chat') {
			targetMap = this.socketGateway.chatClients
		} else {
			return undefined
		}
		for (const [socketId, socket] of targetMap) {
			if (socket.data?.user && socket.data.user.id == id) {
				return socket
			}
		}
		return undefined
	}

	sendUpdateProfile(clientId: string, usernames: string[]) {
		this.socketGateway.server.to(clientId).emit('updateProfile', usernames)
	}
}
