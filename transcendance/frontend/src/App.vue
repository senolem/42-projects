<template>
	<v-app>
		<notifications position="top center" classes="customNotification"/>
		<NavigationComponent />
		<v-main>
			<router-view />
		</v-main>
	</v-app>
</template>

<script lang="ts">
import NavigationComponent from '@/components/navigation.component.vue'

export default {
	components: {
		NavigationComponent
	}
}
</script>

<style lang="scss">
* {
	box-sizing: border-box;
	padding: 0;
	margin: 0;
	font: inherit;
}

html, body{
	height: 100vh;
	background: rgb(68, 50, 92);
}

h1, h2 {
		margin-bottom: 1rem;
}

h1 {
		font-family: 'Kanit', sans-serif;
		color: rgb(223, 220, 215);
		font-size: 3.5em;
		width: 100%;
		border-bottom: 0.5px solid rgba(255, 255, 255, 0.1);
		text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5);
}

.v-main {
	height: 100%;
}

textarea:focus, input:focus{
	outline: none;
}

img, .roomName, .roomPrivacy, .socialChatMessages .message .type, i {
	-webkit-touch-callout: none; /* iOS Safari */
	-webkit-user-select: none; /* Safari */
	-khtml-user-select: none; /* Konqueror HTML */
	-moz-user-select: none; /* Old versions of Firefox */
	-ms-user-select: none; /* Internet Explorer/Edge */
	user-select: none;
}

.customNotification {
	font-family: 'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;

	.notification-title {
		margin: 0 5px 5px;
		padding: 10px;
		font-size: 14px;
		color: #fff;
	}

	&.info {
		background: #44a4fc;
		border-left: 5px solid #187fe7;

		.notification-title::before {
			font-size: 16px;
			font-family: Arial;
			content: 'i';
			display: inline-block;
			align-items: center;
			justify-content: center;
			width: 20px;
			height: 20px;
			border: 2px solid #fff;
			border-radius: 50%;
			font-weight: bold;
			text-align: center;
			line-height: 1;
			margin-right: 10px;
		}
	}

	&.success {
		background: #68cd86;
		border-left: 5px solid #42a85f;

		.notification-title::before {
			font-size: 16px;
			font-family: Arial;
			content: '\2713';
			display: inline-block;
			margin-right: 10px;
			font-weight: bold;
		}
	}

	&.warn {
		background: #ffb648;
		border-left: 5px solid #f48a06;

		.notification-title::before {
			font-size: 16px;
			font-family: Arial;
			content: '\26A0';
			display: inline-block;
			margin-right: 10px;
			font-weight: bold;
		}
	}

	&.error {
		background: #e54d42;
		border-left: 5px solid #b82e24;

		.notification-title::before {
			font-size: 16px;
			font-family: Arial;
			content: '\2717';
			display: inline-block;
			margin-right: 10px;
			font-weight: bold;
		}
	}
}

.customNotification:hover {
	cursor: pointer;
}
</style>
