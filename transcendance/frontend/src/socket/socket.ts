import { nextTick, reactive } from 'vue'
import { io } from 'socket.io-client'
import { router } from '@/router'
import { notify } from '@kyvg/vue3-notification'
import { useSocialStore } from '@/stores/social.store'
import { User } from '@/interfaces/user.interface'
import { Room } from '@/interfaces/room.interface'
import { RoomMessage } from '@/interfaces/roomMessage.interface'
import { ConversationMessage } from '@/interfaces/conversationMessage.interface'
import { getBlockedUsers } from '@/helpers'
import { UsersJoinedUpdate } from '@/interfaces/usersJoinedUpdate.interface'
import { Conversation } from '@/interfaces/conversation.interface'

const socketOptions = {
	withCredentials: true,
	auth: {
		clientType: 'chat'
	},
	autoConnect: false
}

export const state = reactive({
	connected: false
})

export const socket = io(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_SOCKETIO_URL}`, socketOptions)

socket.on('connect', () => {
	state.connected = true
})

socket.on('disconnect', () => {
	state.connected = false
})

socket.on('errorMessage', (error) => {
	console.error(`WebSocket error: ${error}`)
	notify({
		title: `${error}`,
		type: 'error'
	})
})

socket.on('receivedRoomMessage', async (message: RoomMessage) => {
	const socialStore = useSocialStore()
	if (socialStore.currentRoom && message.room === socket.id) {
		const chatWrapper = document.getElementById('chatWrapper')
		if (chatWrapper) {
			const tolerance = chatWrapper.clientHeight * 0.15
			const isChatAtBottom = Math.abs(chatWrapper.scrollHeight - chatWrapper.scrollTop - chatWrapper.clientHeight) < tolerance
			socialStore.currentRoom.messages.push(message)
			await nextTick()
			if (isChatAtBottom) {
				chatWrapper.scrollTop = chatWrapper.scrollHeight
			}
		}
	} else if (socialStore.getRooms && socialStore.getRooms.has(message.room)) {
		const room = socialStore.getRooms.get(message.room)
		if (room) {
			const chatWrapper = document.getElementById('chatWrapper')
			if (chatWrapper) {
				const tolerance = chatWrapper.clientHeight * 0.15
				const isChatAtBottom = Math.abs(chatWrapper.scrollHeight - chatWrapper.scrollTop - chatWrapper.clientHeight) < tolerance
				const blockedUsers = await getBlockedUsers()
				if (!blockedUsers.includes(message.senderId)) {
					room.messages.push(message)
					await nextTick()
					if (isChatAtBottom) {
						chatWrapper.scrollTop = chatWrapper.scrollHeight
					}
				}
			}
		}
	}
})

socket.on('receivedConversationMessage', async(message: ConversationMessage) => {
	const socialStore = useSocialStore()
	try {
		const user = socialStore.getOwnUser
		if (!user) {
			throw new Error('Couldn\'t retrieve own user data')
		}
		const isOwnUserSender = message.sender.id === user.id
		let index = socialStore.getConversations.findIndex((c: Conversation) => {
			const isOwnUserRecipient = c.recipientId === user.id
			return (isOwnUserSender && isOwnUserRecipient && c.id === message.recipientId) || (!isOwnUserSender && c.id === message.sender.id)
		})
		if (index === -1) {
			await socialStore.createConversation(message.sender.username)
			index = socialStore.getConversations.findIndex((c: Conversation) => {
				const isOwnUserRecipient = c.recipientId === user.id
				return (isOwnUserSender && isOwnUserRecipient && c.id === message.recipientId) || (!isOwnUserSender && c.id === message.sender.id)
			})
		}
		if (index !== -1) {
			const conversation = socialStore.getConversations[index]
			const conversationMessages = document.getElementById('conversationMessages')
			if (conversationMessages) {
				const tolerance = conversationMessages.clientHeight * 0.15
				const isChatAtBottom = Math.abs(conversationMessages.scrollHeight - conversationMessages.scrollTop - conversationMessages.clientHeight) < tolerance
				conversation.messages.push(message)
				socialStore.updateConversation(index, conversation)
				await nextTick()
				if (isChatAtBottom) {
					conversationMessages.scrollTop = conversationMessages.scrollHeight
				}
			}
		}
	} catch (error) {
		console.error(`Websocket Error : ${error}`)
		notify({
			title: `Websocket Error : ${error}`,
			type: 'error'
		})
	}
})

socket.on('hasConnectedToChat', async (user: User) => {
	const socialStore = useSocialStore()
	try {
		const users: User[] = socialStore.getUsers
		const exists = users.find(usr => usr.id === user.id)
		if (!exists) {
			socialStore.setUsers([...users, user])
		}
	} catch (error) {
		console.error(`Websocket Error : ${error}`)
		notify({
			title: `Websocket Error : ${error}`,
			type: 'error'
		})
	}
})

socket.on('hasDisconnectedFromChat', async (user: number) => {
	const socialStore = useSocialStore()
	try {
		const users: User[] = socialStore.getUsers
		socialStore.setUsers(users.filter((usr) => usr.id !== user))
	} catch (error) {
		console.error(`Websocket Error : ${error}`)
		notify({
			title: `Websocket Error : ${error}`,
			type: 'error'
		})
	}
})

socket.on('clearChat', async () => {
	const socialStore = useSocialStore()
	const currentRoom = socialStore.getCurrentRoom
	if (currentRoom) {
		socialStore.setMessages(currentRoom.id, [])
	}
})

socket.on('joinedRoom', async (room: Room) => {
	const socialStore = useSocialStore()
	socialStore.setCurrentRoom(room)
})

socket.on('leftRoom', async (room: Room) => {
	const socialStore = useSocialStore()
	socialStore.removeRoom(room)
})

socket.on('banned', async (room: Room) => {
	console.log(`You have been banned from ${room.name}`)
})

socket.on('unbanned', async (room: Room) => {
	console.log(`You have been unbanned from ${room.name}`)
})

socket.on('updateProfile', async (usernames: string[]) => {
	const socialStore = useSocialStore()
	if (router.currentRoute.value.name === 'profile') {
		for (const username of usernames) {
			if (router.currentRoute.value.params.username === username) {
				socialStore.setDoUpdateProfile(true)
				break
			}
		}
	}
})

socket.on('updateRoomPrivacy', async (message: { id: string, privacy: string }) => {
	const socialStore = useSocialStore()
	socialStore.updateRoomPrivacy(message.id, message.privacy)
})

socket.on('usersJoined', (usersJoinedUpdate: UsersJoinedUpdate) => {
	const socialStore = useSocialStore()
	const room = socialStore.getRoom(usersJoinedUpdate.id)
	if (room) {
		room.usersJoined = usersJoinedUpdate.usersJoined
	}
})
