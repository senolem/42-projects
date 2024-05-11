import { h } from 'vue'
import type { IconSet, IconProps } from 'vuetify'
import FortyTwo from '@/icons/42.icon.vue'
import CannonEs from './cannon-es.icon.vue'
import CocosCreator from './cocos-creator.icon.vue'
import Colyseus from './colyseus.icon.vue'
import NestJS from './nest-js.icon.vue'
import VueJS from './vue-js.icon.vue'
import Vuetify from './vuetify.icon.vue'

const customSvgNameToComponent: any = {
	FortyTwo,
	CannonEs,
	CocosCreator,
	Colyseus,
	NestJS,
	VueJS,
	Vuetify
}

const customIcons: IconSet = {
	component: (props: IconProps) => h(customSvgNameToComponent[props.icon as string])
}

export { customIcons }
