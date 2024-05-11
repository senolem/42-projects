import { config } from '@/config'

export const getUserAvatarUrl = (filename: string): string => {
	if (filename) {
		return `${config.network.backendProtocol}://${config.network.backendUrl}/user/avatar/${filename}`
	}
	return ''
}

export const getGameAssetUrl = (type: string, filename: string): string => {
	if (filename) {
		return `${config.network.backendProtocol}://${config.network.backendUrl}/game/${type}/${filename}`
	}
	return ''
}

export const secondsToDhms = (seconds: number) => {
	const days = Math.floor(seconds / (3600 * 24))
	const hours = Math.floor(seconds % (3600 * 24) / 3600)
	const minutes = Math.floor(seconds % 3600 / 60)
	const secs = Math.floor(seconds % 60)

	const daysDisplay = days > 0 ? days + (days == 1 ? " day, " : " days, ") : ""
	const hoursDisplay = hours > 0 ? hours + (hours == 1 ? " hour, " : " hours, ") : ""
	const minutesDisplay = minutes > 0 ? minutes + (minutes == 1 ? " minute, " : " minutes, ") : ""
	const secondsDisplay = secs > 0 ? secs + (secs == 1 ? " second" : " seconds") : ""
	return daysDisplay + hoursDisplay + minutesDisplay + secondsDisplay
}

export const isAlphabetic = (input: string): boolean => {
	return /^[a-zA-Z]+$/.test(input)
}

export const generateRandomNumber = (): number => {
	return Math.floor(Math.random() * 10)
}