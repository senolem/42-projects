/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:07:23 by albaur            #+#    #+#             */
/*   Updated: 2022/07/24 11:45:45 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_launch(char **cmd_args)
{
	int	i;

	i = -99;
	if (cmd_args)
	{
		if (ft_strncmp("cd\0", cmd_args[0], 3) == 0)
			i = builtin_cd(cmd_args);
		else if (ft_strncmp("env\0", cmd_args[0], 4) == 0)
			i = builtin_env(cmd_args);
		else if (ft_strncmp("exit\0", cmd_args[0], 5) == 0)
			i = builtin_exit(cmd_args);
		else if (ft_strncmp("export\0", cmd_args[0], 7) == 0)
			i = builtin_export(cmd_args);
		else if (ft_strncmp("pwd\0", cmd_args[0], 4) == 0)
			i = builtin_pwd(cmd_args);
		else if (ft_strncmp("unset\0", cmd_args[0], 6) == 0)
			i = builtin_unset(cmd_args);
		else if (ft_strncmp("echo\0", cmd_args[0], 5) == 0)
			i = builtin_echo(cmd_args);
		return (i);
	}
	return (-99);
}
