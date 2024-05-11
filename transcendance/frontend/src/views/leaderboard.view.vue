<template>
	<div class="leaderboardWrapper">
		<div class="leaderboardBox">
			<LeaderboardComponent />
		</div>
	</div>
</template>

<script setup lang="ts">
import { useHead } from '@unhead/vue'
import LeaderboardComponent from '@/components/leaderboard.component.vue'

useHead({
	title: 'Transcendance - Leaderboard'
})
</script>

<style lang="scss" scoped>
	.leaderboardWrapper {
		display: flex;
		justify-content: center;
		align-items: center;
		text-align: center;
		overflow: hidden;

		.leaderboardBox {
			padding: 2em;
			word-wrap: break-word;
			box-sizing: border-box;
			border-radius: 0.25em;
			min-width: 50%;
			margin-top: auto;
			margin-bottom: auto;
		}
	}
</style>
