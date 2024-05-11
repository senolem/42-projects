<template>
	<h1>Leaderboard</h1>
	<EasyDataTable
		v-model:server-options="serverOptions"
		:server-items-length="serverItemsLength"
		:loading="loading"
		:headers="headers"
		:items="items"
		table-class-name="datatable"
		must-sort
	/>
</template>

<script setup lang="ts">
import { notify } from '@kyvg/vue3-notification'
import { ref, watch, onMounted } from 'vue'
import type { Header, Item, ServerOptions } from 'vue3-easy-data-table'
import axios from 'axios'

const headers: Header[] = [
	{ text: 'Username', value: 'username', sortable: true },
	{ text: 'XP', value: 'xp', sortable: true },
	{ text: 'Victories in a Row', value: 'victoriesInARow', sortable: true, width: 100 },
	{ text: 'Total Victories', value: 'totalVictories', sortable: true, width: 100 }
]

const serverOptions = ref<ServerOptions>({
	page: 1,
	rowsPerPage: 5,
	sortBy: 'xp',
	sortType: 'desc'
})

const items = ref<Item[]>([])
const loading = ref(false)
const serverItemsLength = ref(0)

async function fetchLeaderboard(options: ServerOptions) {
	loading.value = true
	try {
		const resLeaderboard = await axios.get(`${process.env.VUE_APP_BACKEND_PROTOCOL}://${process.env.VUE_APP_BACKEND_URL}/leaderboard?page=${options.page}&itemsPerPage=${options.rowsPerPage}&sortBy=${options.sortBy}&sortType=${options.sortType}`, {
			withCredentials: true
		})
		items.value = resLeaderboard.data.data.leaderboard
		serverItemsLength.value = resLeaderboard.data.data.totalItems
	} catch (error) {
		console.error(`Failed to fetch leaderboard: ${error}`)
		notify({
			title: `Failed to fetch leaderboard: ${error}`,
			type: 'error'
		})
	}
	loading.value = false
}

watch(serverOptions, (value) => {
	fetchLeaderboard(value)
}, { deep: true })

onMounted(async() => {
	fetchLeaderboard(serverOptions.value)
})
</script>

<style lang="scss" scoped>
.datatable {
    --easy-table-border: 1px solid rgb(28, 28, 28);
    --easy-table-row-border: 1px solid rgb(75, 75, 75);
    --easy-table-header-font-size: 14px;
    --easy-table-header-height: 50px;
    --easy-table-header-font-color: rgb(156, 153, 148);
    --easy-table-header-background-color: rgb(28, 28, 28);
    --easy-table-header-item-padding: 10px 15px;
    --easy-table-body-even-row-font-color: #fff;
    --easy-table-body-even-row-background-color: #4c5d7a;
    --easy-table-body-row-font-color: rgb(223, 220, 215);
    --easy-table-body-row-background-color: rgb(33, 33, 33);
    --easy-table-body-row-height: 50px;
    --easy-table-body-row-font-size: 14px;
    --easy-table-body-row-hover-font-color: rgb(146, 81, 231);
    --easy-table-body-row-hover-background-color: rgb(40, 40, 40);
    --easy-table-body-item-padding: 10px 15px;
    --easy-table-footer-background-color: rgb(28, 28, 28);
    --easy-table-footer-font-color: rgb(156, 153, 148);
    --easy-table-footer-font-size: 14px;
    --easy-table-footer-padding: 0px 10px;
    --easy-table-footer-height: 50px;
    --easy-table-rows-per-page-selector-width: 70px;
    --easy-table-rows-per-page-selector-option-padding: 10px;
    --easy-table-rows-per-page-selector-z-index: 1;
    --easy-table-scrollbar-track-color: #2d3a4f;
    --easy-table-scrollbar-color: #2d3a4f;
    --easy-table-scrollbar-thumb-color: #4c5d7a;;
    --easy-table-scrollbar-corner-color: #2d3a4f;
    --easy-table-loading-mask-background-color: #2d3a4f;
}
</style>
