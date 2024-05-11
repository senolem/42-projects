<template>
	<div class="main">
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, text, text, avatar, text" />
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, text, text, avatar, text" />
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, text, text, avatar, text" />
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, text, text, avatar, text" />
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, text, text, avatar, text" />
		<br>
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, actions" />
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, actions" />
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, actions" />
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, actions" />
		<v-skeleton-loader class="px-8 py-4 skeleton" color="surface" type="avatar, actions" />
	</div>
</template>

<style lang="scss" scoped>
.main {
	width: 100%;
	height: 100%;
	background: rgb(87, 63, 117);
	border-radius: 1vw;
	overflow: hidden;
	padding: 16px;
}
.skeleton{
	color: rgb(223, 220, 215);
	margin-bottom: 4px;
}
</style>
