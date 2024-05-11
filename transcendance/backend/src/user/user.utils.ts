import { join } from 'path'

export const getPath = (pathFromData: string, filename: string) => {
	const root = process.cwd()
	const path = join(root, pathFromData, filename)
	return path
}
