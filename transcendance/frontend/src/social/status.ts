interface Status {
	color: string;
	tooltip: string;
}

export const statusMap: Record<string, Status> = {
	1: { color: '#80828c', tooltip: 'Offline' },
	2: { color: '#00ff00', tooltip: 'Online' },
	3: { color: '#7e58b0', tooltip: 'In Lobby' },
	4: { color: '#d4872f', tooltip: 'In Game' }
}
