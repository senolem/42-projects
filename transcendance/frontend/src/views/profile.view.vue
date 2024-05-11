<template>
<template v-if="!loading">
	<div class="profile" v-if="user">
		<div class="profileBox">
			<div class="profileBanner">
				<ProfileBanner :user="user" :pending-requests="pendingRequests" :friends="friends" :is-added="isAdded" :is-blocked="isBlocked" :request-sent="requestSent" :request-received="requestReceived" @update="onUpdate"/>
			</div>
			<div class="profileDetails">
				<ProfileDetails :user="user" :pending-requests="pendingRequests" :friends="friends" :match-history="matchHistory" @update="onUpdate"/>
			</div>
		</div>
	</div>
</template>
<template v-else>
	<div class="profile">
		<div class="profileBox">
			<div class="profileBanner">
				<ProfileBannerSkeleton></ProfileBannerSkeleton>
			</div>
			<div class="profileDetails">
				<ProfileDetailsSkeleton></ProfileDetailsSkeleton>
			</div>
		</div>
	</div>
</template>
</template>

<style lang="scss" scoped>
.profile {
	overflow: hidden;
	text-align: center;

	.profileBox {
		margin-left: auto;
		margin-right: auto;
		max-width: 75vw;

		@media (max-width: 768px) {
			padding: 4px 4px 4px 4px;
			max-width: 100vw;
		}

		.profileBanner {
			width: 100%;
			padding: 4px 12px 4px 12px;

			@media (max-width: 768px) {
				padding: 4px 4px 4px 4px;
			}
		}

		.profileDetails
		{
			padding: 4px 12px 4px 12px;

			@media (max-width: 768px) {
				padding: 4px 4px 4px 4px;
			}
		}
	}
}
</style>

<script setup lang="ts">
import { ref, watch } from 'vue'
import { storeToRefs } from 'pinia'
import { useRoute } from 'vue-router'
import { useHead } from '@unhead/vue'
import axios, { AxiosResponse } from 'axios'
import { useSocialStore } from '@/stores/social.store'
import { notify } from '@kyvg/vue3-notification'
import ProfileBanner from '@/profile/profileBanner.component.vue'
import ProfileBannerSkeleton from '@/skeletons/profileBanner.skeleton.vue'
import ProfileDetails from '@/profile/profileDetails.component.vue'
import ProfileDetailsSkeleton from '@/skeletons/profileDetails.skeleton.vue'
import { User } from '@/interfaces/user.interface'
import { Scores } from '@/interfaces/scores.interface'

const socialStore = useSocialStore()
const username = ref<string>('')
const route = useRoute()
const user = ref<User | null>(null)
const pendingRequests = ref<User[] | null>(null)
const friends = ref<User[] | null>(null)
const matchHistory = ref<Scores[]>([])
const isBlocked = ref(false)
const isAdded = ref(false)
const requestSent = ref(false)
const requestReceived = ref(false)
const { getDoUpdateProfile } = storeToRefs(socialStore)
const loading = ref(true)

const fetchData = async () => {
	loading.value = true
	try {
		const userRes = await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/users?username=${username.value}`, {
			withCredentials: true
		})
		if (userRes.status === 200) {
			isAdded.value = false
			isBlocked.value = false
			requestReceived.value = false
			requestSent.value = false

			user.value = userRes.data.data.user
			let pendingRes, friendsRes, relationshipRes, blockedRes, matchHistoryRes: AxiosResponse

			if (user.value?.id === socialStore.getOwnUser?.id) {
				[pendingRes, friendsRes, matchHistoryRes] = await Promise.all([
					axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/friends/pending`, {
						withCredentials: true
					}),
					axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/${user?.value?.id}/friends`, {
						withCredentials: true
					}),
					axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/scores?id=${user.value?.id}&limit=10&index=0`, {
						withCredentials: true
					})
				])
			} else {
				[pendingRes, friendsRes, relationshipRes, blockedRes, matchHistoryRes] = await Promise.all([
					axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/friends/pending`, {
						withCredentials: true
					}),
					axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/${user?.value?.id}/friends`, {
						withCredentials: true
					}),
					axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/friends/${user.value?.id}`, {
						withCredentials: true
					}),
					axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/blocked/${user.value?.id}`, {
						withCredentials: true
					}),
					axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/scores?id=${user.value?.id}&limit=10&index=0`, {
						withCredentials: true
					})
				])

				const relationship = relationshipRes.data.data.relationship
				if (relationship) {
					relationship.accepted ? isAdded.value = true : (relationship.senderId === user.value?.id ? requestReceived.value = true : requestSent.value = true)
				}

				isBlocked.value = blockedRes.data.data.blockedUser
			}
			pendingRequests.value = pendingRes.data.data.pendingRequests.map((item: { sender: string }) => item.sender)
			friends.value = friendsRes.data.data.friends
			matchHistory.value = matchHistoryRes.data.data.scores
			loading.value = false
		}
	} catch (error) {
		console.error('Error while fetching data :', error)
		notify({
			title: `Error while fetching data : ${error}`,
			type: 'error'
		})
	}
}

const onUpdate = () => {
	fetchData()
}

watch(
	() => route.params.username, async(toParams) => {
		if (toParams) {
			username.value = toParams as string
			fetchData()
		}
	},
	{ immediate: true }
)

watch(getDoUpdateProfile, (value: boolean) => {
	if (value) {
		fetchData()
		socialStore.setDoUpdateProfile(false)
	}
})

useHead({
	title: `Transcendance - ${username.value ? username.value : 'Unknown'} Profile`
})
</script>
