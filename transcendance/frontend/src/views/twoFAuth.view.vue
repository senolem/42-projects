<template>
	<v-container class="twoFAuthWrapper" fill-height>
		<v-row justify="center" align="center">
			<v-col cols="auto">
				<v-form class="twoFAuthForm pa-8" v-model="valid">
					<h1 class="text-h4 pa-2">Authenticate</h1>
					<v-otp-input v-model="token" />
					<div class="d-flex flex-column">
						<div class="twoFAuthButton">
							<v-btn color="button" text="Cancel" @click="cancel"></v-btn>
						</div>
					</div>
				</v-form>
			</v-col>
		</v-row>
	</v-container>
</template>

<script setup lang="ts">
import { ref, watch } from 'vue'
import { useHead } from '@unhead/vue'
import { notify } from '@kyvg/vue3-notification'
import axios, { AxiosError } from 'axios'
import { router } from '@/router'

useHead({
	title: 'Transcendance - Two-Factor Authentification'
})

const token = ref<string>('')
const valid = ref<boolean>(false)

const authenticate = async() => {
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/verify`, {
			token: token.value
		}, {
			withCredentials: true
		})

		if (res.status === 200) {
			router.push({ path: '2fa', query: { success: 1 } })
		} else {
			token.value = ''
			console.error(`Failed to authenticate by two-factor authentication: ${res.statusText}`)
			notify({
				title: `Failed to authenticate by two-factor authentication: ${res.statusText}`,
				type: 'error'
			})
		}
	} catch (error) {
		token.value = ''
		if (error instanceof AxiosError) {
			console.error(`Failed to authenticate by two-factor authentication: ${error.response?.data.message}`)
			notify({
				title: `Failed to authenticate by two-factor authentication: ${error.response?.data.message}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to authenticate by two-factor authentication: ${error}`)
			notify({
				title: `Failed to authenticate by two-factor authentication: ${error}`,
				type: 'error'
			})
		}
	}
}

async function cancel() {
	try {
		await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/logout`, {
			withCredentials: true
		})

		router.push({ name: 'login' })
		notify({
			title: 'You have successfully been logged out',
			type: 'success'
		})
	} catch (error) {
		console.error(`Logging out failed: ${error}`)
		notify({
			title: `Error while fetching data: ${error}`,
			type: 'error'
		})
	}
}

watch(
	() => token.value.length,
	(newLength: number) => {
		if (newLength === 6) {
			authenticate()
		}
	}
)
</script>

<style lang="scss" scoped>
.twoFAuthWrapper {
	display: flex;
	height: 100%;
	text-align: center;
	align-content: center;

	.twoFAuthForm {
		background-color: rgb(33, 33, 33);
		font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
		font-weight: 400;
		border-radius: 4px;
		min-width: 400px;

		h1 {
			font-family: 'Kanit', sans-serif !important;
			font-weight: 500;
		}

		.links {
			justify-content: space-between;

			a {
				color: rgb(223, 220, 215);
				text-decoration: none;
			}

			a:hover {
				cursor: pointer;
				color: rgba(223, 220, 215, 0.8);
			}
		}

		.twoFAuthButton {
			padding-bottom: 1rem;
			border-bottom: 1px solid rgb(255, 255, 255, 0.05);

			.v-btn {
				width: 100%;
			}
		}

		.loginOauthButton {
			margin-top: 1rem;

			.v-btn {
				width: 100%;
			}
		}
	}
}
</style>
