/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:38:46 by albaur            #+#    #+#             */
/*   Updated: 2022/04/28 14:07:49 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	client_confirmation(int pid)
{
	ft_printf(" \x1B[32mMessage sent !\n", pid);
}

void	client_send(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;

	if (argc != 3)
	{
		ft_printf("\x1B[31mError : Too much/not enough arguments.\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (signal(SIGUSR1, client_confirmation) == SIG_ERR)
	{
		ft_printf("\x1B[31mError : Cannot send message.\n");
		exit (1);
	}
	client_send(pid, argv[2]);
	return (0);
}
