import axios from 'axios'
import { notify } from '@kyvg/vue3-notification'
import { router } from '@/router'
import { useSocialStore } from '@/stores/social.store'

const CONSTANT = 0.07
const POWER = 2

export const getUserAvatarUrl = (filename: string): string => {
	if (filename) {
		return `${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/users/avatar/${filename}`
	}
	return ''
}

export const getUserBackgroundUrl = (filename: string): string => {
	if (filename) {
		return `${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/users/background/${filename}`
	}
	return ''
}

export async function upload(dest: string, formData: FormData) {
	const headers = {
		'Content-Type': 'multipart/form-data',
		withCredentials: true
	}
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/uploads/${dest}`, formData, { headers })

		return res.data.data.response
	} catch (error: any) {
		console.error(`Failed to update ${dest}`)
		notify({
			title: `Failed to update ${dest}: ${error}`,
			type: 'error'
		})
	}
}

export const getBlockedUsers = async() => {
	try {
		const res = await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/blocked`, {
			withCredentials: true
		})

		return res.data.data.blockedUsers
	} catch (error: any) {
		console.error(`Failed to fetch blocked users: ${error}`)
		notify({
			title: `Failed to fetch blocked users: ${error}`,
			type: 'error'
		})
	}
	return null
}

export const goToUserProfile = (username: string) => {
	router.push(`/profile/${username}`)
}

export const setDoUpdateProfile = () => {
	const socialStore = useSocialStore()
	socialStore.setDoUpdateProfile(true)
}

export const calculateLevel = (xp: number) => {
	const level = Math.round(Math.pow(xp, 1 / POWER) * CONSTANT)
	return (level)
}
