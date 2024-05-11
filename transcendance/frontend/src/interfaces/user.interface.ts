export interface User {
	id: number
	id42: number
	username: string
	xp: number
	isAdmin: boolean
	avatar: string
	avatarBlob: string
	background: string
	backgroundBlob: string
	usernameColor: string
	textColor: string
	status: number
	secret: string
	enable2FA: boolean
	totalVictories: number
	victoriesInARow: number
	createdAt: Date
}
