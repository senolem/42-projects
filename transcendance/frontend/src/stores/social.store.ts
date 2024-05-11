import { ref, computed } from 'vue'
import { defineStore } from 'pinia'
import { notify } from '@kyvg/vue3-notification'
import axios from 'axios'
import { User } from '@/interfaces/user.interface'
import { Conversation } from '@/interfaces/conversation.interface'
import { RoomMessage } from '@/interfaces/roomMessage.interface'
import { Room } from '@/interfaces/room.interface'

export const useSocialStore = defineStore('socialStore', () => {
	const ownUser = ref<User | null>(null)
	const isLoggedIn = ref<boolean>(false)
	const isAuthenticated = ref<boolean>(false)
	const conversations = ref<Conversation[]>([])
	const selectedConversation = ref<Conversation | null>(null)
	const users = ref<User[]>([])
	const activeTab = ref<string>('chat')
	const currentRoom = ref<Room | null>(null)
	const rooms = ref<Map<string, Room>>(new Map())
	const doUpdateProfile = ref<boolean>(false)

	const getOwnUser = computed(() => ownUser.value)
	const getAvatar = computed(() => ownUser.value && ownUser.value.avatarBlob ? ownUser.value.avatarBlob : '')
	const getIsLoggedIn = computed(() => isLoggedIn.value)
	const getIsAuthenticated = computed(() => isAuthenticated.value)
	const getMessages = (roomName: string) => {
		return computed(() => {
			if (rooms.value && rooms.value.has(roomName)) {
				const targetRoom = rooms.value.get(roomName)
				return targetRoom ? targetRoom.messages : []
			}
			return []
		})
	}
	const getConversations = computed(() => conversations.value)
	const getSelectedConversation = computed(() => selectedConversation.value)
	const getUsers = computed(() => users.value)
	const getActiveTab = computed(() => activeTab.value)
	const getCurrentRoom = computed(() => currentRoom.value)
	const getRooms = computed(() => rooms.value)
	const getDoUpdateProfile = computed(() => doUpdateProfile.value)

	async function createConversation(username: string) {
		if (username?.trim() !== '') {
			try {
				const res = await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/users?username=${username}`, {
					withCredentials: true
				})
				if (res.status === 200) {
					const user = res.data.data.user
					const selfUser = getOwnUser
					if (!selfUser.value) {
						throw new Error("Couldn't retrieve own user data")
					}
					const conversations: Conversation[] = getConversations.value
					const existingConversation = conversations.find((conversation) => conversation.id === user.id)
					if (existingConversation) {
						setSelectedConversation(existingConversation)
					} else {
						if (selfUser.value) {
							const newConversation: Conversation = {
								id: user.id,
								sender: user,
								recipientId: selfUser.value.id,
								messages: []
							}
							setConversations([...conversations, newConversation])
							setSelectedConversation(newConversation)
						}
					}
				} else {
					console.error(`Failed to fetch user: ${res.data.message}`)
					notify({
						title: `Failed to fetch user: ${res.statusText}`,
						type: 'error'
					})
				}
			} catch (error: any) {
				if (error.response && error.response.status === 404) {
					console.error(`User not found: ${username}`)
					notify({
						title: `User not found: ${username}`,
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
		} else {
			notify({
				title: 'You must specify a username',
				type: 'warn'
			})
		}
	}

	function selectConversation(newConversation: Conversation | null) {
		setSelectedConversation(newConversation)
	}

	function updateConversation(index: number, conversation: Conversation) {
		conversations.value[index] = conversation
	}

	function setOwnUser(user: User | null) {
		ownUser.value = user
	}

	function setAvatar(avatarBlob: string) {
		if (ownUser.value) {
			ownUser.value.avatarBlob = avatarBlob
		}
	}

	function setIsLoggedIn(isLogged: boolean) {
		isLoggedIn.value = isLogged
	}

	function setIsAuthenticated(isAuth: boolean) {
		isAuthenticated.value = isAuth
	}

	function setMessages(room: string, newMessages: RoomMessage[]) {
		if (rooms.value && rooms.value.has(room)) {
			const targetRoom = rooms.value.get(room)
			if (targetRoom) {
				targetRoom.messages = newMessages
			}
		}
	}

	function setConversations(newConversations: Conversation[]) {
		conversations.value = newConversations
	}

	function setSelectedConversation(conversation: Conversation | null) {
		selectedConversation.value = conversation
	}

	function setUsers(newUsers: User[]) {
		users.value = newUsers
	}

	function setActiveTab(tab: string) {
		activeTab.value = tab
	}

	function setCurrentRoom(newRoom: Room) {
		if (rooms.value) {
			addRoom(newRoom)
		}
		currentRoom.value = newRoom
	}

	function setRooms(newRooms: Map<string, Room>) {
		rooms.value = newRooms
	}

	function addRoom(newRoom: Room) {
		if (rooms.value) {
			if (!newRoom.messages) {
				newRoom.messages = []
			}
			rooms.value.set(newRoom.id, newRoom)
		}
	}

	function removeRoom(toRemove: Room) {
		if (rooms.value) {
			rooms.value.delete(toRemove.id)
			const firstElement = rooms.value.entries().next().value
			if (firstElement && firstElement[1]) {
				setCurrentRoom(firstElement[1])
			}
		}
	}

	function getRoom(id: string) {
		return rooms.value.get(id)
	}

	function updateRoomPrivacy(id: string, privacy: string) {
		const room = getRoom(id)
		if (room) {
			room.privacy = privacy
		}
	}

	function setDoUpdateProfile(value: boolean) {
		doUpdateProfile.value = value
	}

	return {
		ownUser,
		doUpdateProfile,
		isLoggedIn,
		isAuthenticated,
		conversations,
		selectedConversation,
		users,
		activeTab,
		currentRoom,
		rooms,
		getOwnUser,
		getDoUpdateProfile,
		getAvatar,
		getIsLoggedIn,
		getIsAuthenticated,
		getMessages,
		getConversations,
		getSelectedConversation,
		getUsers,
		getActiveTab,
		getCurrentRoom,
		getRooms,
		getRoom,
		updateRoomPrivacy,
		createConversation,
		selectConversation,
		updateConversation,
		setOwnUser,
		setDoUpdateProfile,
		setAvatar,
		setIsLoggedIn,
		setIsAuthenticated,
		setMessages,
		setConversations,
		setSelectedConversation,
		setUsers,
		setActiveTab,
		setCurrentRoom,
		setRooms,
		addRoom,
		removeRoom
	}
})
