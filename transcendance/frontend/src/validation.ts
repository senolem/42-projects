// validation.ts

export const validateUsername = (value: string): string | boolean => {
	if (!value || !value.length || /^[a-zA-Z0-9]{1,20}$/.test(value)) {
		return true
	}
	return 'Username must be alphanumeric and between 1 and 20 characters long, alphanumeric only'
}

export const validatePassword = (value: string): string | boolean => {
	if (!value || !value.length || /(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,128}/.test(value)) {
		return true
	}
	return 'Password must be at least 8 characters long and must contain at least a lowercase letter, a number, and a uppercase letter'
}

export const validateRepeatPassword = (password: string, repeatPassword: string): string | boolean => {
	if (repeatPassword === password) {
		return true
	}
	return 'Passwords do not match'
}

export const validateAvatar = async (value: FileList | null): Promise<string | boolean> => {
	if (!value || !value.length || value[0].size <= 2097152) {
		return true
	}
	if (await !checkFileDimensions(value[0], 3000, 3000)) {
		return true
	}
	return 'The size of the avatar should not exceed 2 MB and width and height should not exceed 3000 x 3000 pixels.'
}

export const validateBackground = async (value: FileList | null): Promise<string | boolean> => {
	if (!value || !value.length || value[0].size <= 5242880) {
		return true
	}
	if (await !checkFileDimensions(value[0], 3000, 3000, 900, 900)) {
		return true
	}
	return 'The size of the background image should not exceed 5 MB and width and height should be between 900 x 900 and 3000 x 3000 pixels.'
}

export const checkFileDimensions = (fileBlob: Blob, maxWidth: number, maxHeight: number, minWidth?: number, minHeight?: number) => {
	return new Promise((resolve, reject) => {
		if (fileBlob instanceof Blob) {
			const image = new Image()
			const reader = new FileReader()
			reader.readAsDataURL(fileBlob)
			reader.onload = () => {
				if (typeof reader.result === 'string') {
					image.src = reader.result
				} else {
					resolve(false)
				}
			}
			image.onload = () => {
				if (minWidth && minHeight) {
					resolve(((image.width >= minWidth && image.width <= maxWidth) && (image.height >= minHeight && image.height <= maxHeight)))
				} else {
					resolve(image.width <= maxWidth && image.height <= maxHeight)
				}
			}
			reader.onerror = error => reject(error)
		} else {
			resolve(false)
		}
	})
}
