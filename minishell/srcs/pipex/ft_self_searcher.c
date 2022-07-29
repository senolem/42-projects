/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_self_searcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:32:58 by albaur            #+#    #+#             */
/*   Updated: 2022/07/23 09:22:33 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_self_searcher(char **env, char **cmd_args)
{
	char		*args[3];
	char		*insidepwd;
	char		*pwd;

	if (cmd_args[0][0] != '.')
		return (0);
	pwd = ft_getenv("PWD");
	insidepwd = ft_concat(ft_strjoin(pwd, "/"), cmd_args[0]);
	free(pwd);
	args[0] = cmd_args[0];
	args[1] = insidepwd;
	args[2] = 0;
	if (!access(insidepwd, X_OK))
	{
		execve("/bin/bash", args, env);
		ft_arr_freer(env);
		free(insidepwd);
		return (1);
	}
	free(insidepwd);
	return (0);
}
