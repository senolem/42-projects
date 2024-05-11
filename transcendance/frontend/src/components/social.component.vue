<template>
	<Suspense>
		<template #default>
			<div class="socialWrapper">
				<div class="socialPanel">
					<v-btn flat icon="mdi-chat" rounded="0" @click="socialStore.setActiveTab('chat')" :class="{ active: activeTab === 'chat', activeButton: activeTab === 'chat' }" title="Chat" />
					<v-btn flat icon="mdi-wifi" rounded="0" @click="socialStore.setActiveTab('users')" :class="{ active: activeTab === 'users', activeButton: activeTab === 'users' }" title="Online users" />
					<v-btn flat icon="mdi-forum" rounded="0" @click="socialStore.setActiveTab('conversations')" :class="{ active: activeTab === 'conversations', activeButton: activeTab === 'conversations' }" title="Conversations" />
				</div>
				<ChatComponent :active-tab="activeTab" :rooms="rooms" :currentRoom="currentRoom" @update:activeTab="activeTab = $event"/>
				<UsersComponent :active-tab="activeTab" :users="users" @update:activeTab="activeTab = $event"/>
				<ConversationsComponent :active-tab="activeTab" :users="users" :selected-conversation="selectedConversation" :conversations="conversations" />
			</div>
		</template>
		<template #fallback>
			<div>Loading...</div>
		</template>
	</Suspense>
</template>

<script setup lang="ts">
import { onMounted } from 'vue'
import { useSocialStore } from '@/stores/social.store'
import { storeToRefs } from 'pinia'
import axios from 'axios'
import { notify } from '@kyvg/vue3-notification'
import ChatComponent from '@/social/chat.component.vue'
import UsersComponent from '@/social/users.component.vue'
import ConversationsComponent from '@/social/conversations.component.vue'
import { Room } from '@/interfaces/room.interface'
import { socket, state } from '@/socket/socket'

const socialStore = useSocialStore()
socialStore.setActiveTab('chat')

const {
	users,
	conversations,
	activeTab,
	selectedConversation,
	rooms,
	currentRoom
} = storeToRefs(socialStore)

const fetchData = async () => {
	try {
		const [roomsRes, usersRes, conversationsRes] = await Promise.all([
			axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/chat?limit=50`, {
				withCredentials: true
			}),
			axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/chat/users`, {
				withCredentials: true
			}),
			axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/chat/conversations`, {
				withCredentials: true
			})
		])

		if (roomsRes.status === 200) {
			if (roomsRes.data.data.rooms) {
				const roomsMap = new Map<string, Room>()
				for (const room of roomsRes.data.data.rooms) {
					roomsMap.set(room.id, room)
					if (room.name === 'main') {
						socialStore.setCurrentRoom(room)
					}
				}
				socialStore.setRooms(roomsMap)
			}
		}

		if (usersRes.status === 200) {
			if (usersRes.data.data.connectedUsers) {
				socialStore.setUsers(usersRes.data.data.connectedUsers)
			}
		}

		if (conversationsRes.status === 200) {
			if (conversationsRes.data.data.conversations) {
				socialStore.setConversations(conversationsRes.data.data.conversations)
			}
		}
	} catch (error) {
		console.error('Error while fetching data :', error)
		notify({
			title: `Error while fetching data : ${error}`,
			type: 'error'
		})
	}
}

const scrollChat = () => {
	const chat = document.getElementById('chat')
	if (chat) {
		const newLastMessage = chat.lastElementChild
		if (newLastMessage) {
			newLastMessage.scrollIntoView({ behavior: 'smooth', block: 'end' })
		}
	}
}

const waitForSocketConnection = () => {
	return new Promise<void>((resolve) => {
		if (state.connected) {
			resolve()
		} else {
			const connectHandler = () => {
				socket.off('connect', connectHandler)
				resolve()
			}
			socket.on('connect', connectHandler)
		}
	})
}

onMounted(async () => {
	await waitForSocketConnection()
	await fetchData()
	scrollChat()
})
</script>

<style lang="scss" scoped>
.socialWrapper {
	height: 100%;
	display: flex;
	flex-flow: column;
	background-color: rgb(33, 33, 33);
	box-shadow: 0 0 1em rgba(0, 0, 0, 0.3) inset;
	position: initial;
	width: 340px;
	overflow: hidden;

	.socialPanel {
		display: flex;
		height: 2.5rem;
		border-bottom: 1px solid rgba(255, 255, 255, 0.05);
		border-collapse: collapse;

		button {
			color: rgb(223, 220, 215);
			height: 100%;
			padding-left: 0.5rem;
			padding-right: 0.5rem;
			border: none;
			background-color: rgba(0, 0, 0, 0.2);
		}

		.activeButton {
			background-color: rgba(255, 255, 255, 0.010);
		}
	}
}
</style>
