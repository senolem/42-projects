/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:36:12 by albaur            #+#    #+#             */
/*   Updated: 2022/07/15 22:45:40 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_error(int i, char **cmd_args)
{
	if (i == 1)
		ft_printf("minishell: %s: %s\n", cmd_args[0], strerror(errno));
	else if (i == 2)
		ft_printf("minishell: %s: command not found\n", cmd_args[0]);
	else if (i == 3)
		ft_printf("minishell: %s: is directory\n", cmd_args[0]);
}
