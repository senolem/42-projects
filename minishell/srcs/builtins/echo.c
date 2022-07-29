/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:41:15 by faventur          #+#    #+#             */
/*   Updated: 2022/07/25 14:28:45 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_arr_display(char **arr, size_t i)
{
	if (arr[i] == NULL)
		return ;
	while (arr[i + 1])
	{
		ft_printf("%s ", arr[i]);
		i++;
	}
	ft_printf("%s", arr[i]);
}

int	builtin_echo(char **av)
{
	if (!av || !*av)
		return (-1);
	if (!ft_strcmp(av[1], "-n"))
		echo_arr_display(av, 2);
	else
	{
		echo_arr_display(av, 1);
		ft_putchar('\n');
	}
	ft_arr_freer(av);
	return (0);
}
