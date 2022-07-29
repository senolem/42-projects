/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:41:11 by albaur            #+#    #+#             */
/*   Updated: 2022/07/15 19:33:41 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_set_arg(char *var, char *value)
{
	char	**env;

	env = env_read(ENV_FILE);
	env_set(var, value, &env);
	env_write(ENV_FILE, env);
	ft_arr_freer(env);
}

char	*env_get_arg(char *var)
{
	char	*pwd;
	char	**env;

	env = env_read(ENV_FILE);
	pwd = env_get(var, env);
	ft_arr_freer(env);
	return (pwd);
}

char	*env_get_pwd(void)
{
	char	*pwd;
	char	**env;

	env = env_read(ENV_FILE);
	pwd = env_get("PWD", env);
	ft_arr_freer(env);
	return (pwd);
}

int	env_get_shlvl(void)
{
	char	*pwd;
	char	**env;
	int		shlvl;

	env = env_read(ENV_FILE);
	pwd = env_get("SHLVL", env);
	shlvl = ft_atoi(pwd);
	ft_arr_freer(env);
	free(pwd);
	return (shlvl);
}
