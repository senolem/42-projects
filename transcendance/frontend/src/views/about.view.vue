<template>
	<v-container class="aboutWrapper" fill-height>
		<v-row justify="center" align="center">
			<v-col cols="auto">
				<v-card class="pa-4">
					<v-card-title class="text-h3">Project Transcendance</v-card-title>
					<v-list :items="team"></v-list>
				</v-card>
			</v-col>
		</v-row>
	</v-container>
</template>

<script lang="ts" setup>
import { ref } from 'vue'
import { useHead } from '@unhead/vue'

useHead({
	title: 'Transcendance - About'
})

const team = ref([
	{
		title: 'Project team',
		props: {
			class: 'header'
		}
	},
	{
		title: 'albaur',
		props: {
			href: 'https://profile.intra.42.fr/users/albaur',
			target: 'blank'
		}
	},
	{
		title: 'averon',
		props: {
			href: 'https://profile.intra.42.fr/users/averon',
			target: 'blank'
		}
	},
	{
		title: 'faventur',
		props: {
			href: 'https://profile.intra.42.fr/users/faventur',
			target: 'blank'
		}
	},
	{
		title: 'Technologies used',
		props: {
			class: 'header'
		}
	},
	{
		title: 'Vue.js (Frontend)',
		props: {
			prependIcon: 'custom:VueJS',
			href: 'https://vuejs.org/',
			target: 'blank'
		}
	},
	{
		title: 'Nest.js (Backend)',
		props: {
			prependIcon: 'custom:NestJS',
			href: 'https://nestjs.com/',
			target: 'blank'
		}
	},
	{
		title: 'Cocos Creator (Game engine)',
		props: {
			prependIcon: 'custom:CocosCreator',
			href: 'https://vuetifyjs.com/',
			target: 'blank'
		}
	},
	{
		title: 'Colyseus (Multiplayer server Framework)',
		props: {
			prependIcon: 'custom:Colyseus',
			href: 'https://colyseus.io/',
			target: 'blank'
		}
	},
	{
		title: 'cannon-es (Server-side physics engine)',
		props: {
			prependIcon: 'custom:CannonEs',
			href: 'https://github.com/pmndrs/cannon-es',
			target: 'blank'
		}
	},
	{
		title: 'Vuetify (Vue Component Framework)',
		props: {
			prependIcon: 'custom:Vuetify',
			href: 'https://vuetifyjs.com/',
			target: 'blank'
		}
	}
])
</script>

<style lang="scss">
.aboutWrapper {
	display: flex;
	height: 100%;
	text-align: center;
	align-content: center;

	.v-row {
		width: 100%;

		.v-card {

			.v-card-title {
				font-family: 'Kanit', sans-serif !important;
				color: rgb(223, 220, 215);
				font-weight: 400;
				border-bottom: 0.5px solid rgba(255, 255, 255, 0.1);
				line-height: 3rem;
				white-space: normal;
				text-shadow: 1px 1px 2px rgb(183, 159, 214);
			}

			.v-list {

				.v-list-item {
					display: flex;
					flex-direction: row;
					justify-content: center;
					z-index: 1;

					.v-list-item-title {
						color: rgb(223, 220, 215);
						font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
						font-weight: 400;
					}

					.v-list-item__prepend {
						z-index: 2;
						justify-content: flex-start;

						.v-list-item__spacer {
							width: 4px;
						}
					}
				}
			}

			& .header {
				.v-list-item-title {
					text-align: right;
					font-weight: 600 !important;
					font-size: 18px;
				}
			}
		}
	}
}
</style>
