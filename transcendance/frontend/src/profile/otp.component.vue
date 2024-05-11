<template>
	<v-row justify="center">
		<v-dialog
			class="block"
			persistent
			v-model="dialog"
			width="auto"
		>
			<template v-slot:activator="{ props }">
				<v-btn v-bind="props" width="80%">Confirm</v-btn>
			</template>
			<v-card>
				<v-card-text>
					<v-container>
						<v-row>
							<v-col>
								<v-otp-input
									focused
									v-model="token"
									focus-all
								></v-otp-input>
							</v-col>
						</v-row>
						<v-row justify="center">
							<v-col>
								<v-btn
									width="100%"
									@click="dialog = false"
								>Cancel</v-btn>
							</v-col>
						</v-row>
					</v-container>
				</v-card-text>
			</v-card>
		</v-dialog>
	</v-row>
</template>

<script setup lang="ts">
import { ref, watch } from 'vue'
import axios, { AxiosError } from 'axios'
import { notify } from '@kyvg/vue3-notification'
import { setDoUpdateProfile } from '@/helpers'

const props = defineProps<{
	secret: string
}>()

const token = ref<string>('')
const dialog = ref(false)
const emit = defineEmits(['update:otp', 'update:dialog'])

const register = async() => {
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/confirm`, {
			token: token.value,
			secret: props.secret
		}, {
			withCredentials: true
		})
		if (res.status === 200) {
			dialog.value = false
			emit('update:dialog', false)
			setDoUpdateProfile()
		} else {
			token.value = ''
			console.error(`Failed to register to two-factor authentication: ${res.statusText}`)
			notify({
				title: `Failed to register to two-factor authentication: ${res.statusText}`,
				type: 'error'
			})
		}
	} catch (error) {
		token.value = ''
		if (error instanceof AxiosError) {
			console.error(`Failed to register to two-factor authentication: ${error.response?.data.message}`)
			notify({
				title: `Failed to register to two-factor authentication: ${error.response?.data.message}`,
				type: 'error'
			})
		} else {
			console.error(`Failed to register to two-factor authentication: ${error}`)
			notify({
				title: `Failed to register to two-factor authentication: ${error}`,
				type: 'error'
			})
		}
	}
}

watch(
	() => token.value.length,
	(newLength: number) => {
		if (newLength === 6) {
			emit('update:otp', token.value)
			register()
		}
	}
)
</script>
