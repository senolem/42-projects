<template>
	<div class="contentWrapper">
		<div class="gameWrapper">
			<GameComponent />
		</div>
		<SocialComponent />
	</div>
</template>

<script setup lang="ts">
import { useHead } from '@unhead/vue'
import GameComponent from '@/components/game.component.vue'
import SocialComponent from '@/components/social.component.vue'

useHead({
	title: 'Transcendance - Home'
})
</script>

<style lang="scss" scoped>
.contentWrapper {
	height: 100%;
	display: flex;
	flex: 1;
	overflow: hidden;
	position: relative;
}

.gameWrapper {
	display: flex;
	flex: 1;
	padding: 0.25em;
	overflow: hidden;
}
</style>
