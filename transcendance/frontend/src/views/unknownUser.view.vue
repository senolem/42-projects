<template>
	<v-container class="notFoundWrapper" fill-height>
		<v-row justify="center" align="center">
			<v-col cols="auto">
				<v-card class="pa-4">
					<v-card-title class="mb-4 text-h3">404 User Unknown</v-card-title>
					<v-card-text class="mb-2 text-h6">The requested user profile does not exist on the server</v-card-text>
					<v-btn class="mb-2" color="button" prepend-icon="mdi-home" to="/">Home</v-btn>
				</v-card>
			</v-col>
		</v-row>
	</v-container>
</template>

<script setup lang="ts">
import { useHead } from '@unhead/vue'

useHead({
	title: 'Transcendance - User Unknown'
})
</script>

<style lang="scss" scoped>
.notFoundWrapper {
	display: flex;
	height: 100%;
	text-align: center;
	align-content: center;

	.v-row {
		width: 100%;

		.v-card {

			.v-card-title {
				font-family: 'Kanit', sans-serif !important;
				font-weight: 400;
				border-bottom: 0.5px solid rgba(255, 255, 255, 0.1);
				line-height: 3rem;
				white-space: normal;
			}

			.v-card-text {
				font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
				font-weight: 500;
			}
		}
	}
}
</style>
