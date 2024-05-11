<template>
	<div class="socialChat" v-show="activeTab === 'chat'">
		<div class="socialChatPanel">
			<div class="currentRoom">
				<v-menu width="250">
					<template v-slot:activator="{ props: menu }">
						<v-tooltip color="#E5E5E5" location="bottom">
							<template v-slot:activator="{ props: tooltip }">
								<v-btn color="primary" v-bind="mergeProps(menu, tooltip)" variant="text">
									<div class="room">
										<span class="roomPrivacy" title="Public room" v-if="currentRoom?.privacy === 'public'">🌍</span>
										<span class="roomPrivacy" title="Private room" v-else-if="currentRoom?.privacy === 'private'">🔒</span>
										<span class="roomName" v-if="currentRoom?.name">{{ "#" + currentRoom?.name }}</span>
									</div>
								</v-btn>
							</template>
							<span>Switch room</span>
						</v-tooltip>
					</template>
					<v-card>
						<v-list density="compact">
							<v-list-subheader>Rooms</v-list-subheader>
							<v-list-item v-for="[roomId, room] in rooms" :key="roomId" color="primary" @click="switchRoom(roomId)">
								<template v-slot:prepend>
									<span class="roomPrivacy" title="Public room" v-if="room?.privacy === 'public'">🌍</span>
									<span class="roomPrivacy" title="Private room" v-else-if="room?.privacy === 'private'">🔒</span>
								</template>
								<span class="typeText">{{ '&nbsp;' + room.name }}</span>
								<template v-slot:append>
									{{ room?.usersJoined ? `${room.usersJoined}/${maxClientsPerRoom}` : `0/${maxClientsPerRoom}`}}
								</template>
							</v-list-item>
						</v-list>
					</v-card>
				</v-menu>
			</div>
		</div>
		<div class="socialChatContainer">
			<div id="chatWrapper" class="socialChatMessagesWrapper" @scroll="handleScroll">
				<div id="chat" class="socialChatMessages">
					<div id="chatMessages" class="messageWrapper">
						<div class="message" v-for="message in currentRoom?.messages" :key="message.id" :class="getMessageClass(message.type)">
							<div class="type">
								<v-icon v-if="message.type === 'error'" icon="mdi-alert-circle-outline" size="small" />
								<v-icon v-else-if="message.type === 'info'" icon="mdi-information" size="small" />
								<v-icon v-else-if="message.type === 'broadcast'" icon="mdi-bullhorn" size="small" />
								<span class="typeText">{{ '&nbsp;' + message.type }}</span>
							</div>
							<div class="username" :style="{ color: message.sender.usernameColor }" @click="showCard(message.senderId, $event)">{{ message.sender.username }}</div>
							<div class="separator">:</div>
							<div class="text" :style="{ color: message.sender.textColor }">{{ message.text }}</div>
						</div>
					</div>
				</div>
			</div>
			<div class="socialChatOverlay">
				<div v-if="showChatPaused" class="chatPaused" @click="scrollDown">
					<div class="chatPausedBtn"><v-icon icon="mdi-pause" size="24"></v-icon>Chat paused due to scroll</div>
				</div>
				<div v-if="showUserCard" class="userCard" :style="{ top: userCardPosition.top + 'px', left: userCardPosition.left + 'px' }">
					<userCard :id="currentUserId" @update:activeTab="$emit('update:activeTab', $event)" @update:show-user-card="showUserCard = $event" />
				</div>
			</div>
		</div>
		<div class="socialChatInput">
			<div class="inputWrapper">
				<textarea ref="chatTextarea" @input="handleTextareaInput" @keydown.enter.prevent="sendRoomMessage" v-model="inputChatMessage" placeholder="Write here to chat..." data-placeholder-text="typeHereToChat" maxlength="250"></textarea>
			</div>
			<div class="inputActions">
				<v-menu location="left">
					<template v-slot:activator="{ props }">
						<v-btn icon="mdi-cog" variant="text" v-bind="props" title="Settings"></v-btn>
					</template>
					<v-list class="cogMenu">
						<v-list-item active><v-btn color="button" @click="socket.emit('sendRoomMessage', { text: '/clear', currentRoom: props.currentRoom?.id })">Clear chat</v-btn></v-list-item>
						<v-list-item active><v-btn color="button" @click="socket.emit('sendRoomMessage', { text: '/leave', currentRoom: props.currentRoom?.id })">Leave</v-btn></v-list-item>
						<v-list-item active><v-btn color="button" @click="socket.emit('sendRoomMessage', { text: '/here', currentRoom: props.currentRoom?.id })">Info</v-btn></v-list-item>
						<v-list-item active><v-btn color="button" @click="socket.emit('sendRoomMessage', { text: '/users', currentRoom: props.currentRoom?.id })">Users</v-btn></v-list-item>
						<v-list-item active><v-btn color="button" @click="socket.emit('sendRoomMessage', { text: '/rooms', currentRoom: props.currentRoom?.id })">Rooms</v-btn></v-list-item>
						<v-list-item active><v-btn id="createRoomBtn" @click="roomOptions('/createroom')" color="button">Create Room</v-btn></v-list-item>
						<v-list-item active><v-btn id="joinRoomBtn" @click="roomOptions('/join')" color="button">Join Room</v-btn></v-list-item>
					</v-list>
				</v-menu>
				<v-btn id="sendRoomBtn" @click="sendRoomMessage" color="button" title="Send a message">Chat</v-btn>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref, onMounted, onUnmounted, defineAsyncComponent, nextTick, mergeProps } from 'vue'
import { notify } from '@kyvg/vue3-notification'
import throttle from 'lodash/throttle'
import { useSocialStore } from '@/stores/social.store'
import { socket } from '@/socket/socket'
import { Room } from '@/interfaces/room.interface'

const props = defineProps<{
	activeTab: string
	rooms: Map<string, Room>
	currentRoom: Room | null
}>()

const socialStore = useSocialStore()

const inputChatMessage = ref<string>('')
const showChatPaused = ref(false)
const showUserCard = ref(false)
const currentUserId = ref(0)
const userCardPosition = ref({ top: 0, left: 0 })
const chatTextarea = ref<HTMLElement | null>(null)
const maxClientsPerRoom = process.env.VUE_APP_MAX_CLIENTS_PER_ROOM
let prevScrollPosition = 0

const switchRoom = (newRoom: string) => {
	const room = props.rooms.get(newRoom)
	if (room) {
		socialStore.setCurrentRoom(room)
	}
}

const handleTextareaInput = () => {
	const textarea = chatTextarea.value
	if (textarea) {
		textarea.style.height = 'auto'
		textarea.style.height = `${textarea.scrollHeight}px`
	}
}

const sendRoomMessage = async() => {
	if (!props.currentRoom && inputChatMessage.value.trim() !== '') {
		console.error('Failed to send message: no room joined')
		notify({
			title: 'Failed to send message: no room joined',
			type: 'error'
		})
	}
	if (inputChatMessage.value.trim() !== '') {
		socket.emit('sendRoomMessage', { text: inputChatMessage.value, currentRoom: props.currentRoom?.id })
		inputChatMessage.value = ''
	}
	await nextTick()
	handleTextareaInput()
}

const roomOptions = async(options: string) => {
	if (!props.currentRoom) {
		console.error('Failed to send message: no room joined')
		notify({
			title: 'Failed to send message: no room joined',
			type: 'error'
		})
	}
	socket.emit('sendRoomMessage', { text: options + ' ' + inputChatMessage.value, currentRoom: props.currentRoom?.id })
	inputChatMessage.value = ''
	await nextTick()
	handleTextareaInput()
}

const getMessageClass = (messageType: string) => {
	if (messageType === 'info') {
		return 'infoMessage'
	} else if (messageType === 'error') {
		return 'errorMessage'
	} else if (messageType === 'broadcast') {
		return 'broadcastMessage'
	} else {
		return 'defaultMessage'
	}
}

const handleScroll = throttle((event: Event) => {
	const wrapper = event.target as HTMLElement
	if (wrapper) {
		const currentScrollPosition = wrapper.scrollTop
		const scrollDown = currentScrollPosition > prevScrollPosition
		prevScrollPosition = currentScrollPosition

		if (scrollDown) {
			if (showChatPaused.value && wrapper.scrollTop + wrapper.clientHeight >= wrapper.scrollHeight) {
				showChatPaused.value = false
			}
		} else {
			if (!showChatPaused.value) {
				const tolerance = wrapper.clientHeight * 0.15
				const isChatAtBottom = Math.abs(wrapper.scrollHeight - wrapper.scrollTop - wrapper.clientHeight) < tolerance
				if (!isChatAtBottom) {
					showChatPaused.value = true
				}
			}
		}
	}
}, 100)

const scrollDown = () => {
	const wrapper = document.getElementById('chatWrapper')
	if (wrapper) {
		wrapper.scrollTop = wrapper.scrollHeight
	}
	showChatPaused.value = false
}

const showCard = (userId: number, event: MouseEvent) => {
	if (showUserCard.value) {
		return
	}
	event.stopPropagation()
	currentUserId.value = userId
	showUserCard.value = true

	const target = event.target as HTMLElement
	const boundingRect = target.getBoundingClientRect()
	const socialChatRect = document.querySelector('.socialChat')?.getBoundingClientRect()
	const offsetTop = boundingRect.top - (socialChatRect ? socialChatRect.top : 0)
	const remainingSpaceBelow = socialChatRect ? socialChatRect.bottom - boundingRect.bottom : 0
	const remainingSpaceAbove = boundingRect.top - (socialChatRect ? socialChatRect.top : 0)
	const cardHeight = 175

	if (remainingSpaceAbove >= cardHeight) {
		userCardPosition.value = {
			top: offsetTop - cardHeight + window.scrollY,
			left: 0
		}
	} else if (remainingSpaceBelow >= cardHeight) {
		userCardPosition.value = {
			top: offsetTop + boundingRect.height + window.scrollY,
			left: 0
		}
	} else {
		userCardPosition.value = {
			top: offsetTop - cardHeight + window.scrollY,
			left: 0
		}
	}
}

const closeCard = (event: MouseEvent) => {
	const target = event.target as HTMLElement
	if (target && !target.closest('.userCard')) {
		showUserCard.value = false
	}
}

const userCard = defineAsyncComponent(() =>
	import('@/social/userCard.component.vue')
)

onMounted(async() => {
	document.body.addEventListener('click', closeCard)
})

onUnmounted(async() => {
	document.body.removeEventListener('click', closeCard)
})
</script>

<style lang="scss" scoped>

.socialChat {
	flex: 1;
	display: flex;
	flex-flow: column;
	align-items: stretch;
	overflow: hidden;
	position: relative;

	.socialChatPanel {
		display: flex;
		height: 2.5rem;
		border-bottom: 1px solid rgba(255, 255, 255, 0.025);
		border-collapse: collapse;

		.currentRoom {
			display: flex;
			position: relative;
			align-items: center;
			justify-content: center;
			width: 100%;

			.roomName {
				text-transform: none !important;
				font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
				font-weight: 700;
				font-size: 16px;
			}

			.roomPrivacy {
				font-weight: 700;
				font-size: 18px;
				line-height: 1.25;
			}

			.dropdown {
				width: 100%;
			}
		}
	}

	.socialChatMessagesWrapper {
		height: 100%;
		width: 100%;
		overflow-y: scroll;
		overflow-x: hidden;
		margin: 0;
		padding: 0;
		position: relative;

		.socialChatMessages {
			flex: 1;
			font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
			text-align: left;
			height: 100%;
			width: 100%;

			.messageWrapper {
				padding-left: 7.5px;
				padding-right: 7.5px;
				padding-top: 8px;
				padding-bottom: 8px;
				word-wrap: break-word;

				.message {
					line-height: 20px;
					padding-bottom: 5px;
					padding-left: 7.5px;
					padding-right: 7.5px;
					padding-top: 5px;
					border-collapse: collapse;
					border-radius: 4px;
					position: relative;

					.type {
						display: none;
					}

					.separator {
						display: inline;
						color: rgb(223, 220, 215);
						margin-right: 0.25rem;
						font-size: 14px;
						font-weight: 400;
					}

					.username {
						display: inline;
						font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
						color: rgb(223, 220, 215);
						font-weight: 700;
						font-size: 14px;
					}

					.username:hover {
						cursor: pointer;
					}

					.text {
						display: inline;
						color: rgb(223, 220, 215);
						font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
						font-size: 14px;
						font-weight: 400;
						white-space: pre-wrap;
					}

					&.defaultMessage {
						background-color: rgba(0, 0, 0, 0.0);
					}

					&.defaultMessage:hover {
						background-color: rgba(255, 255, 255, 0.16);
					}

					&.errorMessage {
						background-color: rgba(213, 87, 87, 0.2);

						.username, .separator {
							display: none;
						}
					}

					&.errorMessage:hover {
						background-color: rgba(213, 87, 87, 0.3);
					}

					&.infoMessage {
						background-color: rgba(35, 159, 219, 0.2);

						.username, .separator {
							display: none;
						}
					}

					&.infoMessage:hover {
						background-color: rgba(35, 159, 219, 0.3);
					}

					&.broadcastMessage {
						background-color: rgba(223, 22, 22, 0.2);
					}

					&.broadcastMessage:hover {
						background-color: rgba(223, 22, 22, 0.3);
					}

					&.errorMessage, &.infoMessage, &.broadcastMessage {
						border-top: 2px solid rgba(255, 255, 255, 0.025);
					}

					&.errorMessage .type, &.infoMessage .type, &.broadcastMessage .type {
						width: 100%;
						text-align: right;
						font-size: 12px;
						font-weight: 400;
						color: rgb(223, 220, 215);
						display: inline-block;
					}
				}
			}
		}
	}

	.socialChatInput {
		font-family: 'Open Sans', sans-serif;
		display: flex;
		flex-direction: column;
		padding-bottom: 0.5rem;
		padding-left: 1rem;
		padding-right: 1rem;
		font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
		font-size: 14px;
		font-weight: 400;

		.inputWrapper {
			border: 1px solid rgba(83, 83, 95, 0.48);
			border-radius: 4px;
			margin-bottom: 8px;

			textarea {
				min-height: 2.5rem;
				max-height: 7rem;
				width: 100%;
				appearance: none;
				display: block;
				background-color: rgba(0, 0, 0, 0.2);
				resize: none;
				border: none;
				outline: none;
				padding: 0.5rem;
				overflow-y: auto;
				line-height: 1.5;
				background-clip: padding-box;
				white-space: pre-wrap;
				overflow-wrap: break-word;
			}

			textarea:focus-within {
				box-shadow: 0 0 0 2px #a970ff,inset 0 0 0 2px #a970ff;
			}
		}

		.inputActions {
			display: flex;
			flex-direction: row;
			justify-content: space-between;

			.v-btn {
				height: 2rem;
				width: 2rem;
				color: rgb(223, 220, 215);
				font-size: 13px;
				font-weight: 600;
				transition: 0.2s all ease-in-out;
				border-radius: 4px;
				text-transform: none;
			}
		}
	}

	.socialChatContainer {
		position: relative;
		overflow: hidden;
		height: 100%;
	}

	.socialChatOverlay {
		position: absolute;
		top: 0;
		bottom: 0;
		right: 0;
		left: 0;
		pointer-events: none;
		z-index: 1;

		.userCard {
			position: absolute;
			width: 100%;
			z-index: 1;
			pointer-events: auto;

			.header {
				font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
			}
		}

		.chatPaused {
			width: 65%;
			height: 35px;
			position: absolute;
			pointer-events: auto;
			top: calc(100% - 45px);
			left: 17.5%;
			display: flex;
			align-items: center;
			flex-grow: 0;
			background-color: rgba(0, 0, 0, 0.6);
			font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
			border: 1px solid rgba(255, 255, 255, 0.22);
			border-radius: 0.5rem;

			.chatPausedBtn {
				display: inline-flex;
				align-items: center;
				justify-content: center;
				vertical-align: middle;
				white-space: nowrap;
				line-height: 20px;
				overflow: hidden;
				font-size: 13px;
				font-style: normal;
				font-weight: 600;
				position: absolute;
				left: 50%;
				top: 50%;
				transform: translate(-50%, -50%);
				color: rgb(223, 220, 215);

				.v-icon {
					margin-right: 6px;
				}
			}
		}

		.chatPaused:hover {
			cursor: pointer;
			background-color: rgba(255, 255, 255, 0.13);
		}
	}
}

.cogMenu {
	.v-list-item {
		height: 0.5rem;

		.v-btn {
			font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
			font-weight: 600;
			width: 100%;
			text-transform: unset !important;
		}
	}

	.v-list-item:hover {
		cursor: pointer;
	}
}
</style>
