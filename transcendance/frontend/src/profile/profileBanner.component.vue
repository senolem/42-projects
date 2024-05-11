<template>
	<v-card
		v-if="user"
		class="banner mx-1"
		:style="{
			background: 'linear-gradient(to bottom, rgba(0, 0, 0, 0.45), rgba(128, 128, 128, 0.35)), url(' + userBackground + ') no-repeat center center',
			backgroundSize: 'cover'
		}"
	>
		<v-card-item>
			<template v-slot:prepend>
				<Avatar :filename="user.avatar" :size="96" :status="user.status"/>
			</template>
			<v-card-title class="d-flex" :style="{ color: user.usernameColor }">
				<div class="username">{{ user.username }}</div>
			</v-card-title>
			<v-card-subtitle class="d-flex">
				<v-icon class="mr-1" icon="mdi-star" size="16" color="cardStar"></v-icon>
				<div class="level">{{ 'Level ' }}<span class="levelValue">{{ calculateLevel(user.xp) }}</span></div>
			</v-card-subtitle>
			<v-card-subtitle class="d-flex">
				<v-icon class="mr-1" icon="mdi-trophy" size="16" color="cardTrophy"></v-icon>
				<div class="victories">{{ 'Victories ' }}<span class="victoriesValue">{{ user.totalVictories }}</span></div>
			</v-card-subtitle>
			<v-card-subtitle class="d-flex">
				<v-icon class="mr-1" icon="mdi-trophy-award" size="16" color="cardAward"></v-icon>
				<div class="victoriesInARow">{{ 'Max in a row ' }}<span class="victoriesInARowValue">{{ user.victoriesInARow }}</span></div>
			</v-card-subtitle>
			<template v-slot:append v-if="user.id === ownUser?.id">
				<SettingsPopup :user="user" />
			</template>
		</v-card-item>
		<div v-if="user.id !== ownUser?.id" class="actions">
			<template v-if="!isAdded && !requestSent && !requestReceived && !isBlocked" >
				<v-btn :min-width="175" @click="sendRequest" prepend-icon="mdi-account-plus">Add friend</v-btn>
			</template>
			<template v-if="isAdded && !isBlocked">
				<v-btn :min-width="175" v-show="!hoverIsAdded" @mouseenter="hoverIsAdded = true" @mouseleave="hoverIsAdded = false" prepend-icon="mdi-account-plus">Already added</v-btn>
				<v-btn :min-width="175" color="deny" v-show="hoverIsAdded" @click="removeUser" @mouseenter="hoverIsAdded = true" @mouseleave="hoverIsAdded = false" prepend-icon="mdi-account-remove">Remove friend</v-btn>
			</template>
			<template v-if="requestSent">
				<v-btn :min-width="175" v-show="!hoverRequestSent" @mouseenter="hoverRequestSent = true" @mouseleave="hoverRequestSent = false" prepend-icon="mdi-account-plus">Request sent</v-btn>
				<v-btn :min-width="175" @click="cancelPendingRequest" color="deny" v-show="hoverRequestSent" @mouseenter="hoverRequestSent = true" @mouseleave="hoverRequestSent = false" prepend-icon="mdi-account-remove">Cancel request</v-btn>
			</template>
			<template v-if="requestReceived">
				<v-btn :min-width="175" @click="acceptRequest" prepend-icon="mdi-account-heart">Accept request</v-btn>
			</template>
			<template v-if="!isBlocked">
				<v-btn :min-width="175" @click="blockUser" prepend-icon="mdi-account-cancel">Block user</v-btn>
			</template>
			<template v-if="isBlocked">
				<v-btn :min-width="175" color="deny" v-show="!hoverIsBlocked" @mouseenter="hoverIsBlocked = true" @mouseleave="hoverIsBlocked = false" prepend-icon="mdi-account">Blocked</v-btn>
				<v-btn :min-width="175" color="deny" v-show="hoverIsBlocked" @click="unblockUser" @mouseenter="hoverIsBlocked = true" @mouseleave="hoverIsBlocked = false" prepend-icon="mdi-account">Unblock user</v-btn>
			</template>
		</div>
	</v-card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import axios from 'axios'
import { notify } from '@kyvg/vue3-notification'
import { useSocialStore } from '@/stores/social.store'
import { User } from '@/interfaces/user.interface'
import SettingsPopup from '@/profile/settingsPopup.component.vue'
import Avatar from '@/components/avatar.component.vue'
import { getUserBackgroundUrl, calculateLevel } from '@/helpers'

const props = defineProps<{
	user: User | null,
	friends: User[] | null,
	pendingRequests: User[] | null,
	isAdded: boolean
	isBlocked: boolean
	requestSent: boolean
	requestReceived: boolean
}>()

const socialStore = useSocialStore()
const ownUser = socialStore.getOwnUser

const hoverIsAdded = ref(false)
const hoverIsBlocked = ref(false)
const hoverRequestSent = ref(false)
const userBackground = computed(() => getUserBackgroundUrl(props.user?.background ? props.user?.background : 'default.jpg'))

const emit = defineEmits(['update'])

const sendRequest = async() => {
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/friends/${props.user?.id}`, {
			withCredentials: true
		})

		emit('update')
		return res.data.data.user
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${props.user?.id} not found`)
			notify({
				title: `User #${props.user?.id} not found}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to fetch user: ${error}`)
			notify({
				title: `Failed to fetch user: ${error}`,
				type: 'error'
			})
		}
	}
}

const acceptRequest = async() => {
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/friends/accept/${props.user?.id}`, {
			withCredentials: true
		})

		emit('update')
		return res.data.data.friend
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${props.user?.id} not found`)
			notify({
				title: `User #${props.user?.id} not found}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to fetch user: ${error}`)
			notify({
				title: `Failed to fetch user: ${error}`,
				type: 'error'
			})
		}
	}
}

const removeUser = async() => {
	try {
		const res = await axios.delete(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/friends/${props.user?.id}`, {
			withCredentials: true
		})

		emit('update')
		return res.data.data.friend
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${props.user?.id} not found`)
			notify({
				title: `User #${props.user?.id} not found}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to fetch user: ${error}`)
			notify({
				title: `Failed to fetch user: ${error}`,
				type: 'error'
			})
		}
	}
	return null
}

const cancelPendingRequest = async() => {
	try {
		const res = await axios.delete(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/friends/pending/${props.user?.id}`, {
			withCredentials: true
		})

		emit('update')
		return res.data.data.friendReq
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${props.user?.id} not found`)
			notify({
				title: `User #${props.user?.id} not found}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to fetch user: ${error}`)
			notify({
				title: `Failed to fetch user: ${error}`,
				type: 'error'
			})
		}
	}
	return null
}

const blockUser = async() => {
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/blocked/${props.user?.id}`, {
			withCredentials: true
		})

		emit('update')
		return res.data.data.blocked
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${props.user?.id} not found`)
			notify({
				title: `User #${props.user?.id} not found}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to fetch user: ${error}`)
			notify({
				title: `Failed to fetch user: ${error}`,
				type: 'error'
			})
		}
	}
	return null
}

const unblockUser = async() => {
	try {
		const res = await axios.delete(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/blocked/${props.user?.id}`, {
			withCredentials: true
		})

		emit('update')
		return res.data.data.unblocked
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${props.user?.id} not found`)
			notify({
				title: `User #${props.user?.id} not found}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to fetch user: ${error}`)
			notify({
				title: `Failed to fetch user: ${error}`,
				type: 'error'
			})
		}
	}
	return null
}
</script>

<style lang="scss" scoped>
.banner {
	min-height: 150px;
	.username {
		font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
		font-size: 20px;
		font-weight: 700;
		overflow: hidden;
		text-overflow: ellipsis;
	}

	.v-card-subtitle {
		font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
		font-size: 14px;
		font-weight: 400;
		align-items: center;

		.level, .victories, .victoriesInARow {
			font-weight: 500;
			overflow: hidden;
			text-overflow: ellipsis;
			text-shadow: 1px 1px rgba(0, 0, 0, 0.75);
		}

		.levelValue, .victoriesValue, .victoriesInARowValue {
			font-weight: 700;
		}
	}
	.actions > *{
		margin: 0.25vw;
	}
}
</style>
