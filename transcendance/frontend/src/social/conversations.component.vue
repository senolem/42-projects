<template>
	<div class="socialConversationsWrapper" v-show="activeTab === 'conversations'">
		<div class="socialConversations" v-if="selectedConversation">
			<div class="socialConversationPanel">
				<v-btn flat icon="mdi-arrow-left" class="backButton" @click="selectConversation(null)"></v-btn>
				<img class="avatar" :src="getUserAvatarUrl(selectedConversation.sender.avatar)" :alt="selectedConversation.sender.username">
				<span class="username" :style="{ color: selectedConversation.sender.usernameColor }" @click="showCard(selectedConversation.id, $event)">{{ selectedConversation.sender.username }}</span>
			</div>
			<div class="socialConversationContainer">
				<div id="conversationMessages" class="socialConversationMessages" @scroll="handleScroll">
					<div id="conversationMessagesWrapper" class="messageWrapper">
						<div class="message" v-for="message in selectedConversation.messages" :key="message.id">
							<div class="username" :style="{ color: message.sender.usernameColor }" @click="showCard(message.senderId, $event)">{{ message.sender.username }}</div>
							<div class="separator">:</div>
							<div class="text" :style="{ color: message.sender.textColor }">{{ message.text }}</div>
						</div>
					</div>
				</div>
				<div class="socialConversationOverlay">
					<div v-show="showChatPaused" class="chatPaused" @click="scrollDown">
						<div class="chatPausedBtn"><v-icon icon="mdi-pause" size="24"></v-icon>Chat paused due to scroll</div>
					</div>
					<div v-if="showUserCard" class="userCard" :style="{ top: userCardPosition.top + 'px', left: userCardPosition.left + 'px' }">
						<userCard :id="currentUserId" @update:show-user-card="showUserCard = $event" />
					</div>
				</div>
			</div>
			<div class="socialConversationInput">
				<div class="inputWrapper">
					<textarea ref="chatTextarea" @input="handleTextareaInput" @keydown.enter.prevent="sendConversationMessage" v-model="inputConversationMessage" placeholder="Write here to chat..." data-placeholder-text="typeHereToChat" maxlength="250"></textarea>
				</div>
				<div class="inputActions">
					<v-btn icon="mdi-cog" variant="text" title="Settings"></v-btn>
					<v-btn id="sendRoomBtn" @click="sendConversationMessage" color="button" title="Send a message">Chat</v-btn>
				</div>
			</div>
		</div>
		<div class="socialConversations" v-else>
			<div class="socialConversationsPanel">
				<input @keydown.enter.prevent="createConversation" v-model="newConversationUsername" placeholder="Enter an username..." maxlength="20">
				<v-btn flat variant="text" class="newConversationButton h-100" @click="createConversation()" title="Start a conversation"><v-icon icon="mdi-account-plus"></v-icon></v-btn>
			</div>
			<div class="conversation" v-for="conversation in conversations" :key="conversation.id" @click="selectConversation(conversation)">
				<div class="conversationAvatar">
					<img class="avatar" :src="getUserAvatarUrl(conversation.sender.avatar)" :alt="conversation.sender.username">
				</div>
				<div class="conversationInfo">
					<span class="username" :style="{ color: conversation.sender.usernameColor }">{{ conversation.sender.username }}</span>
					<span class="lastMessage">{{ getLastMessage(conversation) }}</span>
				</div>
				<span class="conversationArrow"></span>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref, nextTick, defineAsyncComponent, onMounted, onUnmounted } from 'vue'
import throttle from 'lodash/throttle'
import { useSocialStore } from '@/stores/social.store'
import { socket } from '@/socket/socket'
import { User } from '@/interfaces/user.interface'
import { Conversation } from '@/interfaces/conversation.interface'
import { getUserAvatarUrl } from '@/helpers'

const props = defineProps<{
	activeTab: string
	users: User[]
	selectedConversation: Conversation | null
	conversations: Conversation[]
}>()

const socialStore = useSocialStore()
const inputConversationMessage = ref<string>('')
const newConversationUsername = ref<string>('')
const showChatPaused = ref<boolean>(false)
const showUserCard = ref(false)
const currentUserId = ref(0)
const userCardPosition = ref({ top: 0, left: 0 })
const chatTextarea = ref<HTMLElement | null>(null)
let prevScrollPosition = 0

const handleTextareaInput = () => {
	const textarea = chatTextarea.value
	if (textarea) {
		textarea.style.height = 'auto'
		textarea.style.height = `${textarea.scrollHeight}px`
	}
}

const createConversation = async() => {
	await socialStore.createConversation(newConversationUsername.value)
	newConversationUsername.value = ''
}

const selectConversation = async(conversation: Conversation | null) => {
	await socialStore.selectConversation(conversation)
	prevScrollPosition = 0
	showChatPaused.value = false
	const conversationMessages = document.getElementById('conversationMessages')
	if (conversationMessages && conversationMessages.lastElementChild) {
		conversationMessages.lastElementChild.scrollIntoView({ behavior: 'smooth', block: 'end' })
	}
}

const getLastMessage = (conversation: Conversation): string => {
	const messages = conversation.messages
	if (messages && messages.length > 0) {
		const latestMessage = messages[messages.length - 1]
		return `${latestMessage.sender.username}: ${latestMessage.text}`.replace('/\r?\n|\r/', '')
	}
	return ''
}

const sendConversationMessage = async() => {
	if (inputConversationMessage.value.trim() !== '') {
		const button = document.getElementById('sendConversationBtn')
		if (button) {
			button.classList.add('flash')
			setTimeout(() => {
				button.classList.remove('flash')
			}, 250)
		}
		socket.emit('sendConversationMessage', { text: inputConversationMessage.value, recipient: props.selectedConversation?.sender.id })
		inputConversationMessage.value = ''
	}
	await nextTick()
	handleTextareaInput()
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
	const wrapper = document.getElementById('conversationMessages')
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
	const socialChatRect = document.querySelector('.socialConversations')?.getBoundingClientRect()
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
.socialConversationsWrapper {
	display: flex;
	flex: 1;
	overflow: hidden;

	.socialConversations {
		flex: 1;
		display: flex;
		flex-flow: column;
		align-items: stretch;
		overflow: hidden;
		overflow-y: scroll;
		position: relative;

		.socialConversationsPanel {
			display: flex;
			flex-direction: row;
			text-align: right;
			border-bottom: 1px solid rgba(255, 255, 255, 0.025);
			height: 28px;
			text-align: left;

			.newConversationButton{
				color: rgb(223, 220, 215);
				border: none;
				border-radius: 0.15rem;
				background: none;
				padding: 0.25rem;
				font-family: Verdana;
				font-size: 1rem;
				font-weight: 800;
				transition: 0.2s all ease-in-out;
				margin: 0;
				width: 20%;
				border-left: 1px solid rgba(255, 255, 255, 0.025);
			}

			.newConversationButton:hover{
				cursor: pointer;
				background-color: rgba(255, 255, 255, 0.025);
			}

			input {
				font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
				color: rgb(223, 220, 215);
				font-size: 14px;
				margin: 0.20rem;
				font-weight: 300;
				background: none;
				border: none;
				width: 80%;
				padding: 0.25rem;
			}
		}

		.conversation {
			background-color: rgba(0, 0, 0, 0.0);
			display: flex;
			position: relative;
			justify-content: space-between;
			align-items: center;
			padding: 0.5rem;

			.conversationAvatar {
				width: 20%;
				text-align: center;

				.avatar {
					margin: 0.25rem;
					border-radius: 50%;
					width: 38px;
					height: 38px;
				}
			}

			.conversationInfo {
				display: flex;
				flex-direction: column;
				width: 80%;
				text-align: left;

				.username {
					width: 80%;
					font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
					color: rgb(223, 220, 215);
					font-size: 15px;
					line-height: 1rem;
					font-weight: 600;
					margin: 0.20rem;
					text-overflow: ellipsis;
					white-space: nowrap;
					overflow: hidden;
				}

				.lastMessage {
					width: 80%;
					font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
					color: rgb(223, 220, 215);
					font-size: 12px;
					line-height: 1rem;
					font-weight: 400;
					margin: 0.20rem;
					font-style: italic;
					text-overflow: ellipsis;
					white-space: nowrap;
					overflow: hidden;
				}
			}

			.conversationArrow {
				display: none;
				font-family: Verdana;
				font-size: 1rem;
				font-weight: 800;
				margin-left: auto;
				color: transparent;
				transition: color 0.2s;
				display: flex;
				align-items: center;
				height: 1.5rem;
			}

			.conversationArrow::after {
				display: none;
				content: ">";
			}
		}

		.conversation:hover {
			cursor: pointer;
			background-color: rgba(0, 0, 0, 0.20);

			.conversationArrow {
				color: rgb(223, 220, 215);
			}
		}

		.socialConversationPanel {
			display: flex;
			border-bottom: 1px solid rgb(255, 255, 255, 0.025);
			flex-direction: row;
			align-items: center;
			text-align: left;

			.backButton {
				color: rgb(223, 220, 215);
				border: none;
				border-radius: 0.15rem;
				background: none;
				padding: 0.25rem;
				font-family: Verdana;
				font-size: 1rem;
				font-weight: 800;
				transition: 0.2s all ease-in-out;
				margin: 0;
				width: 10%;
				height: 100%;
				border-left: 1px solid rgba(255, 255, 255, 0.025);
			}

			.backButton:hover{
				cursor: pointer;
				background-color: rgba(255, 255, 255, 0.025);
			}

			.avatar {
				margin: 0.25rem;
				width: 38px;
				height: 38px;
				border-radius: 50%;
				border: 1.5px solid rgba(0, 255, 42, 0.25);
			}

			.username {
				width: 60%;
				font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
				color: rgb(223, 220, 215);
				font-size: 15px;
				line-height: 1rem;
				font-weight: 600;
				margin: 0.20rem;
				text-overflow: ellipsis;
				white-space: nowrap;
				overflow: hidden;
			}

			.username:hover {
				cursor: pointer;
			}
		}

		.socialConversationMessages {
			flex: 1;
			font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
			overflow-y: scroll;
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
				}

				.message:hover {
					background-color: rgba(255, 255, 255, 0.16);
				}
			}
		}

		.socialConversationInput {
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

		.socialConversationContainer {
			position: relative;
			overflow: hidden;
			height: 100%;
		}

		.socialConversationOverlay {
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
}
</style>
