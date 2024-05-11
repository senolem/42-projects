<template>
	<v-row justify="center" style="margin: 0">
		<v-dialog
			class="block"
			v-model="dialog"
			persistent
			width="auto"
		>
			<template v-slot:activator="{ props }">
				<v-btn
					prepend-icon="mdi-security"
					v-bind="props"
				>
					Enable Two-Factor Authentication
				</v-btn>
			</template>
			<v-card>
				<v-card-text>
					<v-row>
						<v-col>
							<img :src="qrCode" alt="QR code" class="qr-code">
							<div class="secret-title">Your 2FA secret is:</div>
							<div class="secret">{{ secret }}</div>
							<v-btn prepend-icon="mdi-account-key" @click="getQRCode">Regenerate 2FA Key</v-btn>
						</v-col>
					</v-row>
					<v-card-actions class="actions ma-0 pa-0">
						<v-col class="ma-0 pa-0">
							<v-btn @click="dialog = false" width="100%">Cancel</v-btn>
						</v-col>
						<v-col class="ma-0 pa-0">
							<otp :secret="secret" @update:otp="otpValue = $event" @update:dialog="dialog = $event" />
						</v-col>
					</v-card-actions>
				</v-card-text>
			</v-card>
		</v-dialog>
	</v-row>
</template>

<style scoped lang="scss">
.qr-code {
  display: block;
  margin-left: auto;
  margin-right: auto;
  margin-top: 4px;
  margin-bottom: 4px;
  padding-top: 8px;
  padding-bottom: 4px;
}

.secret {
  font-weight: bold;
  background: #565656;
  padding: 3px;
  border: 0.2px solid #505050;
  border-radius: 3px;
  color: rgb(28, 138, 255);
  margin-left: auto;
  margin-right: auto;
  margin-top: 4px;
  margin-bottom: 4px;
  padding-top: 4px;
  padding-bottom: 4px;
}
</style>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
import axios from 'axios'
import { notify } from '@kyvg/vue3-notification'
import otp from '@/profile/otp.component.vue'

const dialog = ref(false)
const qrCode = ref<string>('')
const secret = ref<string>('')
const otpValue = ref<string>('')

const getQRCode = async() => {
	const headers = {
		'Content-Type': 'image/png',
		withCredentials: true
	}
	try {
		const res = await axios.post(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/auth/generate`, { headers })

		if (res.status === 201) {
			qrCode.value = res.data.data.dataUrl
			secret.value = res.data.data.secret
		} else {
			console.error(`Error generating QR code: ${res.data.message}`)
			notify({
				title: `Failed to generate QR code: ${res.statusText}`,
				type: 'error'
			})
		}
	} catch (error: any) {
		console.error(`Error generating QR code: ${error}`)
		notify({
			title: `Failed to generate QR code: ${error}`,
			type: 'error'
		})
	}
}

onMounted(async() => {
	await getQRCode()
})
</script>
