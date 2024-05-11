import { createRouter, createWebHistory, RouteRecordRaw } from 'vue-router'
import { notify } from '@kyvg/vue3-notification'
import axios from 'axios'
import { useSocialStore } from '@/stores/social.store'
import { socket } from '@/socket/socket'
import HomeView from '@/views/home.view.vue'

const axiosInstance = axios.create()

const routes: Array<RouteRecordRaw> = [
	{
		path: '/',
		name: 'home',
		component: HomeView,
		meta: { requiresAuth: true }
	},
	{
		path: '/about',
		name: 'about',
		component: () => import('@/views/about.view.vue'),
		meta: { requiresAuth: false }
	},
	{
		path: '/leaderboard',
		name: 'leaderboard',
		component: () => import('@/views/leaderboard.view.vue'),
		meta: { requiresAuth: true }
	},
	{
		path: '/profile/:username',
		name: 'profile',
		component: () => import('@/views/profile.view.vue'),
		beforeEnter: async (to, from, next) => {
			try {
				await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/users?username=${to.params.username}`, {
					withCredentials: true
				})
				next()
			} catch (error) {
				next('unknownUser')
			}
		},
		meta: { requiresAuth: true }
	},
	{
		path: '/2fa',
		name: '2fa',
		component: () => import('@/views/twoFAuth.view.vue'),
		meta: { requiresAuth: false }
	},
	{
		path: '/login',
		name: 'login',
		component: () => import('@/views/login.view.vue'),
		meta: { requiresAuth: false }
	},
	{
		path: '/signup',
		name: 'signup',
		component: () => import('@/views/signup.view.vue'),
		meta: { requiresAuth: false }
	},
	{
		path: '/:catchAll(.*)',
		name: 'notFound',
		component: () => import('@/views/notFound.view.vue'),
		meta: { requiresAuth: false }
	},
	{
		path: '/unknownUser',
		name: 'unknownUser',
		component: () => import('@/views/unknownUser.view.vue'),
		meta: { requiresAuth: false }
	}
]

export const router = createRouter({
	history: createWebHistory(),
	routes
})

router.beforeEach(async (to, from, next) => {
	const socialStore = useSocialStore()
	if (!socialStore.getIsAuthenticated) {
		socialStore.setIsAuthenticated(await checkAuth())
	}
	if (!socialStore.getIsAuthenticated && from.name !== 'signup') {
		socialStore.setOwnUser(null)
		notify({ clean: true })
		notify({
			title: 'You must log in before accessing the website',
			type: 'info'
		})
	}
	if (to.meta.requiresAuth) {
		if (socialStore.getIsAuthenticated) {
			try {
				const cachedUser = socialStore.getOwnUser
				if (!cachedUser) {
					await fetchUserData()
				}
				socket.connect()
				next()
			} catch (error) {
				next()
			}
		} else {
			next({ name: 'login' })
		}
	} else if (to.name === '2fa' && to.query.success === '1') {
		notify({
			title: 'You are now logged in',
			type: 'success'
		})
		next({ name: 'home' })
	} else if (to.name === '2fa') {
		if (!socialStore.getIsAuthenticated) {
			next()
		} else {
			notify({
				title: 'You are now logged in',
				type: 'success'
			})
			next({ name: 'home' })
		}
	} else if (to.name === 'login' && !to.query.success && socialStore.getIsAuthenticated) {
		next({ name: '2fa' })
	} else if (to.name === 'login' && to.query.success === '1' && socialStore.getIsAuthenticated) {
		next({ name: '2fa' })
	} else if (from.name === 'signup' && to.query.success === '1') {
		notify({
			title: 'Registration was successful, please login now',
			type: 'success'
		})
		next({ name: 'login' })
	} else {
		next()
	}
})

export const checkAuth = async (): Promise<boolean> => {
	try {
		const res = await axiosInstance.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth`, {
			withCredentials: true
		})

		return res.data.success
	} catch (error) {
		return false
	}
}

export const fetchUserData = async () => {
	const socialStore = useSocialStore()
	try {
		const resUser = await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/users/me`, {
			withCredentials: true
		})
		socialStore.setOwnUser(resUser.data.data.user)

		const resAvatar = await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/users/me/avatar`, {
			responseType: 'blob',
			withCredentials: true
		})
		const blobImage: string = await blobToDataURL(resAvatar.data) as string
		socialStore.setAvatar(blobImage)
		socialStore.setIsLoggedIn(true)
	} catch (error) {
		console.error(error)
		notify({
			title: `Fetching user failed : ${error}`,
			type: 'error'
		})
	}
}

const blobToDataURL = async (blob: Blob) => {
	return new Promise((resolve, reject) => {
		const reader = new FileReader()
		reader.onloadend = () => resolve(reader.result)
		reader.onerror = reject
		reader.readAsDataURL(blob)
	})
}
