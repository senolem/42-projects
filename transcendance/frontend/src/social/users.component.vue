<template>
	<div class="socialUsers" v-show="activeTab === 'users'">
		<div class="socialUsersContainer">
			<div class="user" v-for="user in users" :key="user.id" @click="showCard(user.id, $event)">
				<img class="avatar" :src="getUserAvatarUrl(user.avatar)" :alt="user.username">
				<span class="username" :style="{ color: user.usernameColor }">{{ user.username }}</span>
			</div>
			<div class="socialConversationOverlay">
				<div v-if="showUserCard" class="userCard" :style="{ top: userCardPosition.top + 'px', left: userCardPosition.left + 'px' }">
					<userCard :id="currentUserId" @update:activeTab="$emit('update:activeTab', $event)" @update:show-user-card="showUserCard = $event" />
				</div>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref, defineAsyncComponent, onMounted, onUnmounted } from 'vue'
import { User } from '@/interfaces/user.interface'
import { getUserAvatarUrl } from '@/helpers'

defineProps<{
	activeTab: string
	users: User[]
}>()

const showUserCard = ref(false)
const currentUserId = ref(0)
const userCardPosition = ref({ top: 0, left: 0 })

const showCard = (userId: number, event: MouseEvent) => {
	if (showUserCard.value) {
		return
	}
	event.stopPropagation()
	currentUserId.value = userId
	showUserCard.value = true

	const target = event.target as HTMLElement
	const boundingRect = target.getBoundingClientRect()
	const socialChatRect = document.querySelector('.socialUsers')?.getBoundingClientRect()
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
.socialUsers {
	flex: 1;
	display: flex;
	flex-flow: column;
	align-items: stretch;
	overflow: hidden;
	overflow-y: scroll;

	.user {
		padding: 0.5rem;
		border-bottom: 1px solid rgba(255, 255, 255, 0.025);
		border-collapse: collapse;
		display: flex;
		flex-flow: row;
		align-items: center;
		transition: 0.2s all ease-in-out;
		color: rgb(223, 220, 215);

		.username {
			font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
			color: rgb(223, 220, 215);
			font-weight: 700;
			font-size: 15px;
			margin-left: 0.25rem;
		}

		.avatar {
			margin: 0.25rem;
			width: 32px;
		}
	}

	.user:hover {
		cursor: pointer;
		background-color: rgba(0, 0, 0, 0.2);
	}
}
</style>
