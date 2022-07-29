/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:17:07 by albaur            #+#    #+#             */
/*   Updated: 2022/07/25 12:39:29 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_free(char ***env, char **tmp)
{
	ft_arr_freer(*env);
	if (*tmp)
		free(*tmp);
	return (0);
}

int	ft_exec_min(char *cmd)
{
	size_t	a;
	size_t	b;
	size_t	i;

	a = 0;
	b = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			++a;
		else if (cmd[i] == '.')
			++b;
		++i;
	}
	if (a == 0 && b == 0)
		return (0);
	else if (a > 0 && b > 0)
		return (1);
	else if (a > 0 && b == 0)
		return (2);
	else if (a == 0 && b > 0)
		return (3);
	return (4);
}

int	ft_exec_found(char **env, char **cmd_args, char *cmd, t_var *var)
{
	struct stat	stats;

	(void)var;
	if (stat(cmd_args[0], &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode))
			return (3);
	}
	errno = 0;
	execve(cmd, cmd_args, env);
	ft_arr_freer(env);
	return (0);
}

int	ft_exec_not_found(char **env, char **cmd_args)
{
	if (ft_self_searcher(env, cmd_args))
		return (0);
	if (errno != 0)
	{
		if (ft_exec_min(cmd_args[0]) == 0)
			return (2);
		return (1);
	}
	ft_arr_freer(env);
	return (0);
}

int	ft_exec(char **args, t_var *var)
{
	t_exec	e;

	e.i = 0;
	if (!args || !args[0])
		exit(0);
	set_last_input(args);
	if (tilde_searcher(args))
		tilde_replacer(args);
	e.i = builtin_launch(args);
	if (e.i != -99)
		exit(e.i);
	e.env = env_read(ENV_FILE);
	e.cmd = ft_path_searcher(args[0]);
	if (e.cmd)
		e.i = ft_exec_found(e.env, args, e.cmd, var);
	else
	{
		if (!access(args[0], X_OK) && ft_exec_min(args[0]) > 0)
			e.i = ft_exec_found(e.env, ft_exec_args(args), "/bin/bash", var);
		else
			e.i = ft_exec_not_found(e.env, args);
	}
	ft_exec_error(e.i, args);
	ft_exec_free(&e.env, &e.cmd);
	exit(e.i);
}
