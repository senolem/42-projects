/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:58:08 by albaur            #+#    #+#             */
/*   Updated: 2022/04/28 14:11:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	server_handler(int sig, siginfo_t *info, void *nullpointer)
{
	static int				i = 8;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

	(void)nullpointer;
	client_pid = info->si_pid;
	c |= (sig == SIGUSR2);
	i--;
	if (i == 0)
	{
		if (c != 0)
			ft_putchar_fd(c, 1);
		else
		{
			kill(client_pid, SIGUSR1);
			ft_printf("\n");
		}
		c = 0;
		i = 8;
	}
	else
		c <<= 1;
}

int	server_start(void)
{
	pid_t				pid;
	struct sigaction	sig;

	pid = getpid();
	sig.sa_sigaction = server_handler;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) != 0
		|| sigaction(SIGUSR2, &sig, NULL) != 0)
	{
		ft_printf("\x1B[31mError : Unable to receive a message.\n");
		return (0);
	}
	ft_printf("Server \x1B[32mstarted\x1B[0m.\nPID : \x1B[33m%i\n\x1B[0m", pid);
	while (1)
		pause();
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_printf("\x1B[31mError : Server must be started without arguments.\n");
		return (0);
	}
	ft_printf("Starting server...\n");
	server_start();
	ft_printf("Server \x1B[31mstopped\x1B[0m.\n");
	return (0);
}
