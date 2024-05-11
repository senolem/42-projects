<template>
	<v-container class="loginWrapper" fill-height>
		<v-row justify="center" align="center">
			<v-col cols="auto">
				<v-form class="loginForm pa-8" v-model="valid">
					<h1 class="text-h4 pa-2">Sign Up</h1>
					<v-text-field class="py-2" v-model="username" :counter="20" label="Username" required></v-text-field>
					<v-text-field class="py-2" v-model="password" :counter="128" label="Password" type="password" required></v-text-field>
					<v-text-field class="py-2" v-model="repeatPassword" :counter="128" label="Repeat Password" type="password" required></v-text-field>
					<div class="d-flex flex-column">
						<div class="signupButton">
							<v-btn color="button" text="Sign Up" @click="signup"></v-btn>
						</div>
					</div>
				</v-form>
			</v-col>
		</v-row>
	</v-container>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import { notify } from '@kyvg/vue3-notification'
import axios, { AxiosError } from 'axios'
import { useHead } from '@unhead/vue'
import { router } from '@/router'

useHead({
	title: 'Transcendance - Sign Up'
})

const username = ref<string>('')
const password = ref<string>('')
const repeatPassword = ref<string>('')
const valid = ref<boolean>(false)

const signup = async() => {
	if (username.value.trim() === '' && password.value.trim() === '') {
		console.error('You must provide a username and a password')
		notify({
			title: 'You must provide a username and a password',
			type: 'warn'
		})
		return
	} else if (username.value.trim() === '') {
		console.error('You must provide a username')
		notify({
			title: 'You must provide a username',
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
	} else if (password.value.trim() !== repeatPassword.value.trim()) {
		console.error('The specified passwords must be identical')
		notify({
			title: 'The specified passwords must be identical',
			type: 'warn'
		})
		return
	}
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/register`, {
			username: username.value,
			password: password.value
		}, {
			withCredentials: true
		})
		if (res.status === 200) {
			router.push({ path: 'login', query: { success: 1 } })
		} else {
			console.error(`Failed to sign up : ${res.statusText}`)
			notify({
				title: `Failed to sign up : ${res.statusText}`,
				type: 'error'
			})
		}
	} catch (error) {
		if (error instanceof AxiosError) {
			console.error(`Failed to sign up : ${error.response?.data.message}`)
			notify({
				title: `Failed to sign up : ${error.response?.data.message}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to sign up : ${error}`)
			notify({
				title: `Failed to sign up : ${error}`,
				type: 'error'
			})
		}
	}
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

		.signupButton {

			.v-btn {
				width: 100%;
			}
		}
	}
}
</style>
