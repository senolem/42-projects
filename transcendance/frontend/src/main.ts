import { createApp } from 'vue'
import { createPinia } from 'pinia'
import { createHead } from '@unhead/vue'
import Notifications from '@kyvg/vue3-notification'
import axios from 'axios'
import App from '@/App.vue'
import { router } from '@/router'
import { interceptError } from './interceptors/login.interceptor'

// Icons
import '@mdi/font/css/materialdesignicons.css'
import { customIcons } from '@/icons/customIcons'

// Vuetify
import 'vuetify/styles'
import { createVuetify, ThemeDefinition } from 'vuetify'
import * as components from 'vuetify/components'
import * as directives from 'vuetify/directives'
import { aliases, mdi } from 'vuetify/iconsets/mdi'

// Table
import Vue3EasyDataTable from 'vue3-easy-data-table'
import 'vue3-easy-data-table/dist/style.css'

// Swatches
import VSwatches from 'vue3-swatches'
import 'vue3-swatches/dist/style.css'

// Theme
const darkTranscendance: ThemeDefinition = {
	dark: true,
	colors: {
		background: 'rgb(68, 50, 92)',
		'background-nav': 'rgb(90, 59, 130)',
		button: 'rgb(102, 63, 153)',
		surface: 'rgb(33, 33, 33)',
		'surface-variant': 'rgb(15, 15, 15)',
		'on-surface-variant': 'rgb(223, 220, 215)',
		primary: 'rgb(223, 220, 215)',
		'primary-darken-1': '#3700B3',
		secondary: '#03DAC6',
		'secondary-darken-1': '#018786',
		error: '#B00020',
		info: '#2196F3',
		success: '#4CAF50',
		warning: '#FB8C00',
		cardStar: '#F7CA18',
		cardTrophy: '#ff3d3d',
		cardAward: '#854dff',
		approve: '#02850f',
		deny: '#960018',
		orangeade: '#FFC300',
		off: '#696969'
	}
}

const vuetify = createVuetify({
	components,
	directives,
	icons: {
		defaultSet: 'mdi',
		aliases,
		sets: {
			mdi,
			custom: customIcons
		}
	},
	theme: {
		defaultTheme: 'darkTranscendance',
		themes: {
			darkTranscendance
		}
	}
})

axios.defaults.withCredentials = true
axios.interceptors.response.use(
	response => response,
	async error => {
		await interceptError(error)
	}
)

const app = createApp(App)
const pinia = createPinia()
const head = createHead()
app.use(head)
app.use(vuetify)
app.use(pinia)
app.use(router)
app.use(Notifications)
app.use(VSwatches)
app.component('EasyDataTable', Vue3EasyDataTable)
app.component('custom', customIcons)
app.mount('body')
