<template>
	<div v-if="user" class="v-container-fluid">
		<div class="main">
			<div class="friends" v-if="friends && friends.length">
				<div class="title">Friends</div>
				<template v-for="(friend, i) in friends" :key="i">
					<v-card style="background-color: rgb(30, 30, 30);" class="mt-1 mb-1">
						<v-card-item class="header">
							<template v-slot:prepend>
								<v-avatar :image="getUserAvatarUrl(friend.avatar)" :size="48"/>
							</template>
							<v-card-title class="username" :style="{ color: friend.usernameColor }">{{ friend.username }}</v-card-title>
							<v-card-subtitle class="align-items-center d-flex">
								<v-icon class="d-inline-block mr-1" icon="mdi-star" size="16" color="cardStar"></v-icon>
								<div class="level d-inline-block">{{ `Level ${friend.xp}` }}</div>
							</v-card-subtitle>
						</v-card-item>
						<div class="actions">
							<v-btn color="button" prepend-icon="mdi-card-account-details" @click="goToUserProfile(friend.username)">Profile</v-btn>
						</div>
					</v-card>
				</template>
			</div>
			<div class="matchHistory" v-if="matchHistoryCopy && matchHistoryCopy.length">
				<div class="title">Match History</div>
				<v-infinite-scroll class="table" :height="300" :items="matchHistory" :onLoad="loadMatchHistory" mode="manual">
					<template v-for="(item, index) in matchHistory" :key="item">
						<div :class="['item', index % 2 === 0 ? 'even' : '']">
							<div class="leftCol">
								<v-avatar class="avatar" :size="48" :image="getUserAvatarUrl(item.player1?.avatar)"></v-avatar>
								<div class="username" @click="goToUserProfile(item.player1?.username)">{{ item.player1?.username }}</div>
							</div>
							<div class="middleCol">
								<div class="score">{{ item.player1Score }}<span class="separator"> - </span>{{ item.player2Score }}</div>
								<span class="result" :style="{ color: getMatchColor(item) }">{{ getMatchStatus(item) }}</span>
							</div>
							<div class="rightCol">
								<v-avatar class="avatar" :size="48" :image="getUserAvatarUrl(item.player2?.avatar)"></v-avatar>
								<div class="username" @click="goToUserProfile(item.player2?.username)">{{ item.player2?.username }}</div>
							</div>
						</div>
					</template>
				</v-infinite-scroll>
			</div>
			<div v-if="matchStats && matchStats.length">
				<div class="title">Match Statistics</div>
				<v-row align="center" justify="center">
					<v-col cols="6" >
						<canvas id="pie-chart"></canvas>
					</v-col>
				</v-row>
				<v-row align="center" justify="center">
					<canvas id="time-scale"></canvas>
					<canvas id="bar-chart"></canvas>
				</v-row>
			</div>
			<div class="pendingRequests" v-if="pendingRequests && pendingRequests.length && user.id === ownUser?.id">
				<div class="title">Pending Requests</div>
				<div v-for="(request) in pendingRequests" :key="request.id">
					<v-card style="background-color: #1e1e1e;" class="mt-1 mb-1">
						<v-card-item class="header">
							<template v-slot:prepend>
								<v-avatar :image="getUserAvatarUrl(request.avatar)" :size="48"/>
							</template>
							<v-card-title class="username" :style="{ color: request.usernameColor }">{{ request.username }}</v-card-title>
							<v-card-subtitle class="align-items-center d-flex">
								<v-icon class="d-inline-block mr-1" icon="mdi-star" size="16" color="cardStar"></v-icon>
								<div class="level d-inline-block">{{ `Level ${request.xp}`}}</div>
							</v-card-subtitle>
						</v-card-item>
						<div class="actions">
							<v-btn color="approve" prepend-icon="mdi-account-check" @click="acceptRequest(request.id)">Accept</v-btn>
							<v-btn color="deny" prepend-icon="mdi-account-minus" @click="cancelPendingRequest(request.id)">Decline</v-btn>
						</div>
					</v-card>
				</div>
			</div>
			<div class="title" v-if="(!friends || friends && !friends.length) && (!matchHistory || matchHistory && !matchHistory.length) && (!pendingRequests || pendingRequests && !pendingRequests.length)" >Nothing to show yet</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import { useSocialStore } from '@/stores/social.store'
import { User } from '@/interfaces/user.interface'
import { Scores } from '@/interfaces/scores.interface'
import axios from 'axios'
import { notify } from '@kyvg/vue3-notification'
import { getUserAvatarUrl, goToUserProfile, calculateLevel } from '@/helpers'
import Chart from 'chart.js/auto'
import { ChartConfiguration } from 'chart.js'
import ChartDataLabels from 'chartjs-plugin-datalabels'
import 'chartjs-adapter-luxon'
const { DateTime } = require('luxon')
Chart.register(ChartDataLabels)

const props = defineProps<{
	user: User | null
	friends: User[] | null
	pendingRequests: User[] | null
	matchHistory: Scores[]
}>()

const socialStore = useSocialStore()
const ownUser = computed(() => socialStore.getOwnUser)
const matchHistoryCopy = ref<Scores[]>([])
const matchHistoryOffset = ref<number>(0)
matchHistoryCopy.value = props.matchHistory
const matchStats = ref<Scores[]>([])

const emit = defineEmits(['update'])

const getMatchStatus = (score: Scores) => {
	if ((score.player1Score > score.player2Score && score.player1.id === props.user?.id) ||
		(score.player1Score < score.player2Score && score.player2.id === props.user?.id)) {
		if (score.winByForfeit) {
			return 'win by forfeit'
		}
		return 'win'
	} else if ((score.player1Score > score.player2Score && score.player2.id === props.user?.id) ||
		(score.player1Score < score.player2Score && score.player1.id === props.user?.id)) {
		if (score.winByForfeit) {
			return 'lose by forfeit'
		}
		return 'lose'
	} else {
		return 'undefined'
	}
}

const getMatchColor = (score: Scores) => {
	if (score.player1Score === score.player2Score) {
		return 'rgb(170, 170, 170)'
	}
	if ((score.player1Score > score.player2Score && score.player1.id === props.user?.id) ||
		(score.player1Score < score.player2Score && score.player2.id === props.user?.id)) {
		return 'rgb(2, 133, 15)'
	}
	return 'rgb(150, 0, 24)'
}

function get_percentages(scores: string[]) {
	let count = 0
	for (const win of scores) {
		(win === 'win' || win === 'win by forfeit') ? ++count : count += 0
	}
	const victories = count
	const losses = scores.length - victories
	return [victories, losses]
}

async function generatePieChart() {
	if (matchStats.value.length) {
		try {
			const chartElem = document.getElementById('pie-chart') as HTMLCanvasElement
			const data = get_percentages(matchStats.value.map(score => getMatchStatus(score)))
			const chartConfig = {
				type: 'pie',
				data: {
					labels: ['Victories', 'Losses'],
					datasets: [
						{
							data,
							backgroundColor: [
								'rgba(18, 103, 74, 0.8)',
								'rgba(150, 0, 24, 0.8)'
							]

						}
					]
				},
				options: {
					plugins: {
						datalabels: {
							formatter: (value, ctx) => {
								const total = ctx.chart.data.datasets[0].data.reduce((a, b) => a + b, 0)
								const percentage = Math.round((value / total) * 100)
								return `${percentage}%`
							},
							color: '#fff'
						}
					}
				}
			} as ChartConfiguration
			return new Chart(chartElem, chartConfig)
		} catch (error) {
			console.error(`Unable to create the graph: ${error}`)
			notify({
				title: `Error while creating the graph: ${error}`,
				type: 'error'
			})
		}
	}
}

async function generateTimeScale() {
	if (matchStats.value.length) {
		try {
			const chartElem = document.getElementById('time-scale') as HTMLCanvasElement
			const dataset = matchStats.value.map(score => score.player1.id === props?.user?.id ? calculateLevel(score.player1Xp) : calculateLevel(score.player2Xp))
			dataset.push(0)
			const labels = matchStats.value.map(score => DateTime.fromISO(score.updatedAt).setLocale('fr').toFormat('yyyy-MM-dd t'))
			labels.push(DateTime.fromISO(props?.user?.createdAt).setLocale('fr').toFormat('yyyy-MM-dd t'))
			const data = {
				labels: labels.reverse(),
				datasets: [
					{
						label: 'Advancement Level',
						data: dataset.reverse(),
						backgroundColor: 'rgba(249, 105, 14, 0.8)',
						fill: false
					}
				]
			}
			const config = {
				type: 'line',
				data,
				options: {
					plugins: {
						title: {
							text: 'Progress',
							display: true,
							color: '#fff'
						}
					},
					scales: {
						x: {
							time: {
								displayFormats: {
									day: 'MMM D'
								}
							},
							title: {
								display: true,
								text: 'Date',
								color: '#fff'
							},
							ticks: {
								color: '#fff'
							}
						},
						y: {
							title: {
								display: true,
								text: 'Level',
								color: '#fff'
							},
							ticks: {
								color: '#fff'
							}
						}
					}
				}
			} as ChartConfiguration
			return new Chart(chartElem, config)
		} catch (error) {
			console.error(`Unable to create the time scale: ${error}`)
			notify({
				title: `Error while creating the graph: ${error}`,
				type: 'error'
			})
		}
	}
}

async function generateBarChart() {
	if (matchStats.value.length) {
		try {
			const chartElem = document.getElementById('bar-chart') as HTMLCanvasElement
			const labels = matchStats.value.map(score => DateTime.fromISO(score.updatedAt).setLocale('fr').toFormat('yyyy-MM-dd t'))
			const data = {
				labels: labels.reverse(),
				datasets: [
					{
						label: 'Match Length (in seconds)',
						data: matchStats.value.map(score => (score.matchLength)).reverse(),
						backgroundColor: 'rgba(170, 170, 170, 0.5)',
						fill: false
					}
				]
			}
			const config = {
				type: 'bar',
				data,
				options: {
					responsive: true,
					plugins: {
						title: {
							text: 'The longest Match',
							display: true,
							color: '#fff'
						},
						tooltip: {
							callbacks: {
								label: function(tooltipItem) {
									const totalSeconds = Math.floor(tooltipItem.dataset.data[tooltipItem.dataIndex] / 1000)
									const hours = Math.floor(totalSeconds / 3600)
									const minutes = Math.floor((totalSeconds % 3600) / 60)
									const seconds = totalSeconds % 60

									const matchLengthHumanReadable = [hours, minutes, seconds]
										.map(v => v < 10 ? '0' + v : v)
										.join(':')
									return 'Match length: ' + matchLengthHumanReadable
								}
							}
						},
						datalabels: {
							formatter: (value, ctx) => {
								ctx.chart.data.datasets[0].data.map(score => {
									const totalSeconds = Math.floor(score / 1000)
									const hours = Math.floor(totalSeconds / 3600)
									const minutes = Math.floor((totalSeconds % 3600) / 60)
									const seconds = totalSeconds % 60

									const matchLengthHumanReadable = [hours, minutes, seconds]
										.map(v => v < 10 ? '0' + v : v)
										.join(':')
									return {
										text: matchLengthHumanReadable,
										textAlign: 'center'
									}
								})
								const totalSeconds = Math.floor(value / 1000)
								const hours = Math.floor(totalSeconds / 3600)
								const minutes = Math.floor((totalSeconds % 3600) / 60)
								const seconds = totalSeconds % 60

								const matchLengthHumanReadable = [hours, minutes, seconds]
									.map(v => v < 10 ? '0' + v : v)
									.join(':')
								return matchLengthHumanReadable
							},
							color: '#fff',
							display: window.innerWidth > 590
						}
					},
					scales: {
						x: {
							time: {
								displayFormats: {
									day: 'MMM D'
								}
							},
							title: {
								display: true,
								text: 'Date',
								color: '#fff'
							},
							ticks: {
								color: '#fff'
							}
						},
						y: {
							ticks: {
								callback: function (duration: number) {
									const totalSeconds = Math.floor(duration / 1000)
									const hours = Math.floor(totalSeconds / 3600)
									const minutes = Math.floor((totalSeconds % 3600) / 60)
									const seconds = totalSeconds % 60

									const matchLengthHumanReadable = [hours, minutes, seconds]
										.map(v => v < 10 ? '0' + v : v)
										.join(':')
									return matchLengthHumanReadable
								},
								color: '#fff'
							},
							title: {
								display: true,
								text: 'Duration (in seconds)',
								color: '#fff'
							}
						}
					}
				}
			} as ChartConfiguration
			return new Chart(chartElem, config)
		} catch (error) {
			console.error(`Unable to create the time scale: ${error}`)
			notify({
				title: `Error while creating the graph: ${error}`,
				type: 'error'
			})
		}
	}
}

const acceptRequest = async(friendId: number) => {
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/friends/accept/${friendId}`, {
			withCredentials: true
		})

		emit('update')
		return res.data.data.friend
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${friendId} not found`)
			notify({
				title: `User #${friendId} not found}`,
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

const cancelPendingRequest = async(friendId: number) => {
	try {
		const res = await axios.delete(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/relationships/friends/pending/${friendId}`, {
			withCredentials: true
		})

		emit('update')
		return res.data.data.friend
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${friendId} not found`)
			notify({
				title: `User #${friendId} not found}`,
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

const loadMatchStats = async () => {
	try {
		const res = await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/scores?id=${props.user?.id}&limit=500`, {
			withCredentials: true
		})
		if (res.data.data.scores.length) {
			for (const value of res.data.data.scores as Scores[]) {
				matchStats.value.push(value)
			}
		}
	} catch (error: any) {
		console.error(`Failed to fetch stats: ${error}`)
		notify({
			title: `Failed to fetch stats: ${error}`,
			type: 'error'
		})
	}
}

const loadMatchHistory = async({ done }) => {
	try {
		matchHistoryOffset.value += 10
		const res = await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/scores?id=${props.user?.id}&limit=10&index=${matchHistoryOffset.value}`, {
			withCredentials: true
		})
		if (res.data.data.scores.length) {
			for (const value of res.data.data.scores as Scores[]) {
				matchHistoryCopy.value.push(value)
			}
			if (res.data.data.scores.length < 10) {
				done('empty')
			} else {
				done('ok')
			}
		} else {
			done('empty')
		}
	} catch (error: any) {
		matchHistoryOffset.value -= 10
		console.error(`Failed to fetch match history: ${error}`)
		notify({
			title: `Failed to fetch match history: ${error}`,
			type: 'error'
		})
		done('error')
	}
}

onMounted(async() => {
	await loadMatchStats()
	if (matchStats.value.length > 0) {
		generatePieChart()
		generateTimeScale()
		generateBarChart()
	}
})
</script>

<style lang="scss" scoped>
.main {
	width: 100%;
	height: 100%;
	background: rgb(87, 63, 117);
	border-radius: 1vw;
	overflow: hidden;
	padding: 16px;

	.title {
		font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
		font-weight: 500;
		display: inline-block;
		font-size: 20px;
		margin-top: 6px;
		margin-bottom: 6px;
	}

	.friends {
		padding: 0 16px 0 16px;

		.username {
			text-align: left;
		}

		.actions > * {
			margin: 0.25vw;
		}
	}

	.matchHistory {
		.table {
			padding: 0 16px 0 16px;

			.item {
				display: flex;
				align-items: center;
				justify-content: space-between;
				height: 75px;
				padding: 10px;
				border-radius: 10px;
				margin-bottom: 4px;
				background-color: rgb(28, 28, 28);
				box-shadow: 0 4px 8px rgba(0, 0, 0, 0.25);

				.leftCol,
				.middleCol,
				.rightCol {
					flex: 1;
					display: flex;
					align-items: center;
					justify-content: center;
					overflow: hidden;

					.avatar {
						overflow: hidden;
						margin: 0.5vw;
					}

					.username {
						font-size: 18px;
						font-weight: 500;
						margin-left: 2vw;
						overflow: hidden;
						text-overflow: ellipsis;
						white-space: nowrap;
						color: rgb(223, 220, 215);
						transition: 0.2s all ease-in-out;
					}

					.username:hover {
						cursor: pointer;
						color: rgba(223, 220, 215, 0.8);
					}
				}

				.middleCol {
					display: flex;
					flex: 0.8;
					flex-direction: column;
					align-items: center;
					text-align: center;

					.score {
						text-align: center;
						min-width: 75px;
						background-color: rgba(255, 255, 255, 0.05);
						border: 1px solid rgba(255, 255, 255, 0.10);
						border-radius: 4px;
						padding: 2px;
						font-size: 24px;
						overflow: hidden;
						text-overflow: ellipsis;

						.separator {
							font-size: 20px;
							font-weight: 600;
						}
					}

					.result {
						font-size: 16px;
					}
				}
			}
		}
	}

	.pendingRequests {
		padding: 0 16px 0 16px;

		.username {
			text-align: left;
		}

		.actions > * {
			margin: 0.25vw;
		}
	}
}
</style>
