import { AxiosError } from 'axios'
import { checkAuth, router } from '@/router/index'
import { useSocialStore } from '@/stores/social.store'

export const interceptError = async(error: AxiosError<unknown, any>): Promise<any> => {
	const socialStore = useSocialStore()
	if (router.currentRoute.value.name && router.currentRoute.value.name !== 'login' && (typeof error.response === 'undefined' || error?.response?.status === 401)) {
		socialStore.setIsAuthenticated(await checkAuth())
		if (!socialStore.getIsAuthenticated) {
			router.push({ name: 'login' })
		}
	}
	return Promise.reject(error)
}
