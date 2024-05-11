<template>
	<v-row v-if="user" class="component" justify="center" style="margin: 0;">
		<v-dialog
			class="block"
			v-model="dialog"
			persistent
		>
			<template v-slot:activator="{ props }">
				<v-btn class="settingsBtn" prepend-icon="mdi-account-edit" v-bind="props">Settings</v-btn>
			</template>
			<v-card>
				<v-container>
					<v-card-title class="text-center">
						<span class="text-h5 pb-4 mb-4">Profile settings</span>
					</v-card-title>
					<v-card-text>
						<v-form ref="inputForm" lazy-validation>
							<v-row>
								<v-col style="justify-items: center;" md="4" xs="12">
									<v-card style="text-align: center;">
										<v-avatar :image="getUserAvatarUrl(user.avatar)" :size="avatarSize" style="margin-bottom: 2vh;"/>
										<span class="text-h4 d-block username" :style="{ color: user.usernameColor }">{{ user.username }}</span>
									</v-card>
									<v-file-input
										label="Change your avatar"
										accept="image/png, image/jpeg"
										@change="uploadFile"
										ref="avatar"
										:rules="rules.avatarRules"
										style="margin-top: 2vh;"
									></v-file-input>
									<v-btn
										prepend-icon="mdi-delete"
										color="deny"
										block
										@click="removeAvatar"
										:disabled="user.avatar === 'default.png'"
									>Remove avatar</v-btn>
								</v-col>
								<v-col md="8" xs="12">
									<v-text-field
										clearable
										label="New username"
										v-model="form.username"
										:rules="rules.usernameRules"
										type="text"
									></v-text-field>
									<v-text-field
										clearable
										label="New password"
										v-model="form.newPassword"
										:rules="rules.passwordRules"
										type="password"
									></v-text-field>
									<v-text-field
										clearable
										label="Repeat new password"
										v-model="form.repeatPassword"
										:rules="rules.repeatPasswordRules"
										type="password"
									></v-text-field>
									<v-file-input
										label="Change your background image"
										accept="image/png, image/jpeg"
										@change="uploadFile"
										ref="background"
										:rules="rules.backgroundRules"
									></v-file-input>
									<fieldset
										class="pb-2 mb-2"
										style="display: flex; align-items: center; justify-items: center;"
									>
										<span class="ml-2 pl-2" style="color: #bfbfbf; font-family: Inter, Roobert, Arial, sans-serif; font-size: 18px;">Username color</span>
										<VSwatches
											class="ml-3 pl-3 mt-2 pt-2"
											v-model="form.color"
											inline
											shapes="circles"
											:swatches="swatches"
											background-color="transparent" />
									</fieldset>
									<template v-if="!status2FA">
										<QRCode v-if="!secret2FA" />
										<v-row v-else justify="center" style="margin: 0">
												<v-btn prepend-icon="mdi-security" width="100%" @click="enable2FA">Enable Two-Factor Authentication</v-btn>
											</v-row>
									</template>
									<template v-else>
										<v-row justify="center" style="margin: 0">
											<v-btn prepend-icon="mdi-shield-off" width="100%" @click="disable2FA">Disable 2FA</v-btn>
										</v-row>
									</template>
								</v-col>
							</v-row>
						</v-form>
					</v-card-text>
					<v-card-actions>
						<v-spacer></v-spacer>
						<v-btn @click="dialog = false">Close</v-btn>
						<v-btn @click.prevent="submitForm">Save</v-btn>
					</v-card-actions>
				</v-container>
			</v-card>
		</v-dialog>
	</v-row>
</template>

<style scoped lang="scss">
.username {
	font-family: "Inter", "Roobert", "Helvetica Neue", Helvetica, Arial, sans-serif;
	font-size: 20px;
	font-weight: 700;
}
</style>

<script setup lang="ts">
import { ref, onMounted, onUnmounted, watchEffect } from 'vue'
import axios from 'axios'
import { notify } from '@kyvg/vue3-notification'
import { User } from '@/interfaces/user.interface'
import { getUserAvatarUrl, upload, goToUserProfile, setDoUpdateProfile } from '@/helpers'
import QRCode from '@/profile/qrCode.component.vue'
import { validateUsername, validatePassword, validateRepeatPassword, validateAvatar, validateBackground } from '@/validation'
import { fetchUserData } from '@/router/index'
import { ValidateResponse } from '@/interfaces/validateResponse.interface'

const props = defineProps<{
	user: User | null
}>()

const dialog = ref(false)
const inputForm = ref<HTMLFormElement>()
const form = ref({
	username: '',
	newPassword: '',
	repeatPassword: '',
	color: props.user?.usernameColor
})
const rules = ref({
	usernameRules: [validateUsername],
	passwordRules: [validatePassword],
	repeatPasswordRules: [(value: string) => validateRepeatPassword(form.value.newPassword, value)],
	avatarRules: [validateAvatar],
	backgroundRules: [validateBackground]
})
const avatar = ref<HTMLInputElement | null>()
const background = ref<HTMLInputElement | null>()
const avatarForm = new FormData()
const bgForm = new FormData()
const formData = new FormData()
const swatches = [
	'#D4ADCF',
	'#FAEDCA',
	'#20BF55',
	'#FF674D',
	'#7CC6FE',
	'#FFF'
]

const status2FA = ref(props.user?.enable2FA)
const secret2FA = ref(props.user?.secret)

const calculateAvatarSize = () => {
	if (window.innerWidth > 960) {
		return 196
	} else {
		return 128
	}
}

const avatarSize = ref(calculateAvatarSize())

const removeAvatar = async() => {
	try {
		const res = await axios.delete(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/users/me/avatar`, {
			withCredentials: true
		})

		setDoUpdateProfile()
		return res.data.data.updatedAvatar
	} catch (error: any) {
		if (error.response && error.response.status === 404) {
			console.error(`User #${props.user?.id} not found`)
			notify({
				title: `User #${props.user?.id} not found}`,
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

async function uploadFile() {
	if (avatar.value && avatar.value && avatar.value.files && avatar.value.files[0]) {
		avatarForm.set('avatar', avatar.value.files[0])
	}
	if (background.value && background.value && background.value.files && background.value.files[0]) {
		bgForm.set('background', background.value.files[0])
	}
}

async function submitForm() {
	if (inputForm.value) {
		const validateRes = await inputForm.value.validate() as ValidateResponse
		let formRes
		let avatarRes
		let backgroundRes

		if (!validateRes.valid) {
			alert('An error occurred. Please check if each field has been properly filled.')
		} else {
			try {
				for (const [key, value] of Object.entries(form.value)) {
					if (value) {
						formData.set(key, value)
					}
				}
				if (formData.entries().next().done) {
					return null
				}

				if (formData) {
					formRes = await upload('profile', formData)
					for (const key of formData.keys()) {
						formData.delete(key)
					}
				}
				if (avatarForm.has('avatar') && avatar.value) {
					avatarRes = await upload('avatar', avatarForm)
					avatar.value.value = ''
					avatarForm.delete('avatar')
				}
				if (bgForm.has('background') && background.value) {
					backgroundRes = await upload('background', bgForm)
					background.value.value = ''
					bgForm.delete('background')
				}

				if (formRes || avatarRes) {
					await fetchUserData()
				}
				if (formRes) {
					if (formRes.username) {
						goToUserProfile(formRes.username)
					} else if (props.user?.username) {
						setDoUpdateProfile()
					}
				} else if (backgroundRes) {
					setDoUpdateProfile()
				}

				dialog.value = false
			} catch (error) {
				console.error(`An error occurred: ${error}`)
				notify({
					title: 'An error occurred, your settings have not been saved',
					type: 'error'
				})
			}
		}
	}
}

const enable2FA = async() => {
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/2fa`, {
			withCredentials: true
		})

		if (res.status === 201) {
			status2FA.value = true
			return res.data.data.enabled
		} else {
			console.error(`Failed to enable two-factor authentication: ${res.data.message}`)
			notify({
				title: `Failed to enable two-factor authentication: ${res.statusText}`,
				type: 'error'
			})
		}
	} catch (error: any) {
		console.error(`Failed to enable two-factor authentication: ${error}`)
		notify({
			title: `Failed to enable two-factor authentication: ${error}`,
			type: 'error'
		})
	}
}

const disable2FA = async() => {
	try {
		const res = await axios.delete(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/2fa`, {
			withCredentials: true
		})

		if (res.status === 200) {
			status2FA.value = false
			return res.data.data.disabled
		} else {
			console.error(`Failed to disable two-factor authentication: ${res.data.message}`)
			notify({
				title: `Failed to disable two-factor authentication: ${res.statusText}`,
				type: 'error'
			})
		}
	} catch (error: any) {
		console.error(`Failed to disable two-factor authentication: ${error}`)
		notify({
			title: `Failed to disable two-factor authentication: ${error}`,
			type: 'error'
		})
	}
}

onMounted(async() => {
	watchEffect(() => {
		window.addEventListener('resize', () => {
			avatarSize.value = calculateAvatarSize()
		})
	})
})

onUnmounted(async() => {
	window.removeEventListener('resize', () => {
		avatarSize.value = calculateAvatarSize()
	})
})

</script>
