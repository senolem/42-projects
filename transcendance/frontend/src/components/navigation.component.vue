<template>
	<v-app-bar app color="background-nav">
		<v-app-bar-nav-icon icon="mdi-menu" @click.stop="drawer = !drawer" title="Navigation menu"></v-app-bar-nav-icon>
		<v-toolbar-title class="text-left">Transcendance</v-toolbar-title>
		<template v-if="loggedIn" v-slot:append>
			<router-link v-if="isLarge" class="px-4 profile-link" :to="{ name: 'profile', params: { username: username } }" title="Profile">
				<span class="px-2 username">{{ username }}</span>
				<v-avatar :image="avatar" size="42"></v-avatar>
			</router-link>
			<v-btn v-else class="px-4" icon="mdi-account-circle" @click="profile" title="Profile"></v-btn>
			<v-btn class="px-4" icon="mdi-logout" @click="logout" title="Logout"></v-btn>
		</template>
	</v-app-bar>

	<v-navigation-drawer color="background-nav" v-model="drawer" location="left" temporary>
		<v-list :items="links"></v-list>
	</v-navigation-drawer>
</template>

<script setup lang="ts">
import { computed, ref, onMounted, watchEffect } from 'vue'
import { notify } from '@kyvg/vue3-notification'
import axios from 'axios'
import { socket, state } from '@/socket/socket'
import { useSocialStore } from '@/stores/social.store'
import { router } from '@/router'

const socialStore = useSocialStore()
const loggedIn = computed(() => socialStore.getIsLoggedIn)
const avatar = computed(() => socialStore.getAvatar)
const username = computed(() => {
	const user = socialStore.getOwnUser
	if (user) {
		return user.username
	} else {
		socialStore.setIsLoggedIn(false)
		return null
	}
})
const isLarge = ref(window.innerWidth > 512)
const drawer = ref(false)
const links = ref([
	{
		title: 'Home',
		props: {
			to: '/',
			prependIcon: 'mdi-home'
		}
	},
	{
		title: 'Leaderboard',
		props: {
			to: '/leaderboard',
			prependIcon: 'mdi-trophy'
		}
	},
	{
		title: 'About',
		props: {
			to: '/about',
			prependIcon: 'mdi-information'
		}
	}
])

async function logout() {
	try {
		await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/logout`, {
			withCredentials: true
		})
		socialStore.setAvatar('')
		socialStore.setOwnUser(null)
		socialStore.setIsLoggedIn(false)
		socialStore.setIsAuthenticated(false)
		router.push({ name: 'login' })
		if (socket && state.connected) {
			socket.disconnect()
		}
		notify({
			title: 'You have successfully been logged out',
			type: 'success'
		})
	} catch (error) {
		console.error(`Logging out failed: ${error}`)
		notify({
			title: `Error while fetching data: ${error}`,
			type: 'error'
		})
	}
}

async function profile() {
	router.push({ name: 'profile', params: { username: username.value } })
}

onMounted(async() => {
	watchEffect(() => {
		window.addEventListener('resize', () => {
			isLarge.value = window.innerWidth > 512
		})
	})
})
</script>

<style lang="scss" scoped>

.v-toolbar-title, .v-list-item-title {
	font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
	font-weight: 500;
}

.profile-link {
	display: flex;
	text-decoration: none;
	color: inherit;
	align-items: center;

	.username {
		font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
		font-weight: 500;
	}
}

.profile-link:hover, .profile-link:active {
	.username {
		color: #ccc;
	}

	.v-avatar {
		opacity: 0.8;
	}
}
</style>
