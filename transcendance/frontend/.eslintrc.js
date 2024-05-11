module.exports = {
	root: true,
	env: {
		node: true,
		'vue/setup-compiler-macros': true
	},
	extends: [
		'plugin:vue/vue3-essential',
		'@vue/standard',
		'@vue/typescript/recommended'
	],
	parserOptions: {
		ecmaVersion: 2020
	},
	rules: {
		'no-console': process.env.NODE_ENV === 'production' ? 'warn' : 'off',
		'no-debugger': process.env.NODE_ENV === 'production' ? 'warn' : 'off',
		indent: [1, "tab"],
		'no-tabs': 0,
		'camelcase': 'off',
		'vue/multi-word-component-names': 'off',
		'space-before-function-paren': 'off',
		'@typescript-eslint/no-explicit-any': 'off',
		'@typescript-eslint/no-var-requires': 'off'
	}
}
