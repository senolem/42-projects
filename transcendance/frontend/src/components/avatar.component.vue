<template>
	<div class="avatar">
		<div :style="{ position: 'relative', display: 'inline-block' }">
			<v-avatar :image="avatar" :size="size" />
			<v-tooltip v-if="status" top>
				<template v-slot:activator="{ props }">
					<div v-bind="props">
						<div v-if="status" :style="getStatusDotStyle as Record<string, string>"></div>
					</div>
				</template>
				<span>{{ getStatusTooltip }}</span>
			</v-tooltip>
		</div>
	</div>
</template>

<script setup lang="ts">
import { getUserAvatarUrl } from '@/helpers'
import { computed } from 'vue'
import { statusMap } from '@/social/status'

const props = defineProps<{
	size: number,
	filename: string,
	status: number
}>()

const avatar = computed(() => getUserAvatarUrl(props.filename))
const getStatusColor = computed(() => statusMap[props.status]?.color || '#fff')
const getStatusTooltip = computed(() => statusMap[props.status]?.tooltip || 'Unknown')
const getStatusDotStyle = computed(() => {
	const dotSize = Math.max(Math.floor(props.size * 0.2), 16)
	const dotPosition = Math.floor(props.size * 0.06)
	return {
		position: 'absolute',
		bottom: `${dotPosition}px`,
		right: `${dotPosition}px`,
		width: `${dotSize}px`,
		height: `${dotSize}px`,
		backgroundColor: getStatusColor.value,
		border: '4px solid #2c2f33',
		borderRadius: '50%'
	}
})
</script>

<style lang="scss" scoped>
.avatar {
	position: relative;
}
</style>
