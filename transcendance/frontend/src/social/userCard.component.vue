<template>
	<v-card :loading="loading" max-height="175px" class="mx-1">
		<div v-if="user">
			<v-card-item class="header">
				<template v-slot:prepend>
					<Avatar :filename="user.avatar" :size="48" :status="user.status"/>
				</template>
				<v-card-title :style="{ color: user.usernameColor }">{{ user.username }}</v-card-title>
				<v-card-subtitle class="align-items-center d-flex">
					<v-icon class="d-inline-block mr-1" icon="mdi-star" size="16" color="cardStar"></v-icon>
					<div class="level">{{ 'Level ' }}<span class="levelValue">{{ calculateLevel(user.xp) }}</span></div>
				</v-card-subtitle>
				<template v-slot:append>
					<v-btn icon="mdi-close" size="small" variant="text" @click="$emit('update:showUserCard', false)" />
				</template>
			</v-card-item>
			<div class="actions">
				<v-btn prepend-icon="mdi-email" @click="sendInvitation">Invite</v-btn>
				<v-btn prepend-icon="mdi-message" @click="sendMessage">Message</v-btn>
				<v-btn prepend-icon="mdi-card-account-details" @click="goToUserProfile(user.username)">Profile</v-btn>
			</div>
		</div>
	</v-card>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
import { notify } from '@kyvg/vue3-notification'
import axios from 'axios'
import { useSocialStore } from '@/stores/social.store'
import { User } from '@/interfaces/user.interface'
import { Invitation } from '@/interfaces/invitation.interface'
import Avatar from '@/components/avatar.component.vue'
import { calculateLevel, goToUserProfile } from '@/helpers'
import { socket } from '@/socket/socket'

const props = defineProps<{
	id: number
}>()

const socialStore = useSocialStore()
const user = ref<User | null>(null)
const loading = ref<boolean>(false)
const emit = defineEmits(['update:activeTab', 'update:showUserCard'])

const fetchUser = async() => {
	loading.value = true
	try {
		const res = await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/users?id=${props.id}`, {
			withCredentials: true
		})
		if (res.status === 200) {
			loading.value = false
			return res.data.data.user
		} else {
			console.error(`Failed to fetch user: ${res.data.message}`)
			notify({
				title: `Failed to fetch user: ${res.statusText}`,
				type: 'error'
			})
		}
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${props.id} not found`)
			notify({
				title: `User #${props.id} not found`,
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
	loading.value = false
	return null
}

const sendInvitation = async() => {
	const ownUserId = socialStore.getOwnUser?.id
	if (user.value && ownUserId) {
		const invitation: Invitation = {
			sender: ownUserId,
			recipient: user.value.id
		}
		socket.emit('sendInvitation', invitation)
	} else {
		console.error('Failed to send invitation')
		notify({
			title: 'Failed to send invitation',
			type: 'error'
		})
	}
	emit('update:showUserCard', false)
}

const sendMessage = async() => {
	if (user.value && user.value.username) {
		await socialStore.createConversation(user.value?.username)
	} else {
		console.error('Failed to open conversation')
		notify({
			title: 'Failed to open conversation',
			type: 'error'
		})
	}
	emit('update:showUserCard', false)
	emit('update:activeTab', 'conversations')
}

onMounted(async() => {
	user.value = await fetchUser()
})
</script>

<style lang="scss" scoped>
.v-card {
	.header {
		background-color: rgba(0, 0, 0, 0.25);

		.level {
			text-overflow: ellipsis;
			white-space: nowrap;
			overflow: hidden;
		}
	}

	.actions {
		flex-direction: row;
		flex-wrap: wrap;
		align-content: flex-end;

		.v-btn {
			background-color: rgb(102, 63, 153);
			margin: 4px;
		}
	}
}
</style>
