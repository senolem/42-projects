<template>
	<v-container class="loginWrapper" fill-height>
		<v-row justify="center" align="center">
			<v-col cols="auto">
				<v-form class="loginForm pa-8" v-model="valid">
					<h1 class="text-h4 pa-2">Sign In</h1>
					<v-text-field class="py-2" v-model="username" :counter="20" label="Username" required></v-text-field>
					<v-text-field class="py-2" v-model="password" :counter="128" label="Password" type="password" required></v-text-field>
					<div class="d-flex flex-column">
						<div class="loginButton">
							<v-btn color="button" text="Login" @click="login"></v-btn>
						</div>
						<div class="loginOauthButton">
							<v-btn prependIcon="custom:FortyTwo" text="Login with 42 Intra" variant="outlined" @click="login42"></v-btn>
						</div>
					</div>
					<div class="d-flex flex-row mt-4 links">
						<a href="#">Forgot Password?</a>
						<a @click="signup">Signup</a>
					</div>
				</v-form>
			</v-col>
		</v-row>
	</v-container>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import { useHead } from '@unhead/vue'
import { notify } from '@kyvg/vue3-notification'
import axios, { AxiosError } from 'axios'
import { router } from '@/router'

useHead({
	title: 'Transcendance - Sign In'
})
const username = ref<string>('')
const password = ref<string>('')
const valid = ref<boolean>(false)

const login42 = () => {
	window.location.href = `${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/42/callback`
}

const login = async() => {
	if (username.value.trim() === '' && password.value.trim() === '') {
		console.error('You must provide an username and a password')
		notify({
			title: 'You must provide an username and a password',
			type: 'warn'
		})
		return
	} else if (username.value.trim() === '') {
		console.error('You must provide an username and a password')
		notify({
			title: 'You must provide an username',
			type: 'warn'
		})
		return
	} else if (password.value.trim() === '') {
		console.error('You must provide a password')
		notify({
			title: 'You must provide a password',
			type: 'warn'
		})
		return
	} else if (!/^[a-zA-Z0-9]{1,20}$/.test(username.value)) {
		console.error('You must provide a valid username')
		notify({
			title: 'You must provide a valid username',
			type: 'warn'
		})
		return
	} else if (!/(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,128}/.test(password.value)) {
		console.error('You must provide a valid password')
		notify({
			title: 'You must provide a valid password',
			type: 'warn'
		})
		return
	}
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/login`, {
			username: username.value,
			password: password.value
		}, {
			withCredentials: true
		})
		if (res.status === 200) {
			router.push({ path: '2fa' })
		} else {
			console.error(`Failed to login : ${res.statusText}`)
			notify({
				title: `Failed to login : ${res.statusText}`,
				type: 'error'
			})
		}
	} catch (error) {
		if (error instanceof AxiosError) {
			console.error(`Failed to login : ${error.response?.data.message}`)
			notify({
				title: `Failed to login : ${error.response?.data.message}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to login : ${error}`)
			notify({
				title: `Failed to login : ${error}`,
				type: 'error'
			})
		}
	}
}

const signup = () => {
	router.push({ path: 'signup' })
}
</script>

<style lang="scss" scoped>
.loginWrapper {
	display: flex;
	height: 100%;
	text-align: center;
	align-content: center;

	.loginForm {
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

		.loginButton {
			padding-bottom: 1rem;
			border-bottom: 1px solid rgba(255, 255, 255, 0.05);

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
