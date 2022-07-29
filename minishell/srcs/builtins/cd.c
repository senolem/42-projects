/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:46:09 by albaur            #+#    #+#             */
/*   Updated: 2022/07/20 11:00:40 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_exec(char *tmp, char ***env)
{
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	env_set("OLDPWD", tmp, env);
	env_set("PWD", cwd, env);
}

static int	cd_min(char **str)
{
	size_t	i;
	char	*tmp[3];

	tmp[0] = "cd";
	tmp[1] = "~";
	tmp[2] = 0;
	i = 0;
	if (ft_arrlen(str) == 1)
	{
		builtin_cd(tmp);
		return (-1);
	}
	while (str[1][i])
	{
		if (ft_isalnum(str[1][i]) > 0 || str[1][i] == '.'
				|| str[1][i] == '/' || str[1][i] == '~')
			return (1);
		++i;
	}
	return (-1);
}

static int	cd_tilde(char *path, char *tmp, char ***env)
{
	int		i;
	char	*ptmp;
	char	*home;

	i = 0;
	++path;
	home = env_get("HOME", *env);
	ptmp = ft_strjoin(home, path);
	free(home);
	i = chdir(ptmp);
	if (i == 0)
	{
		env_set("OLDPWD", tmp, env);
		env_set("PWD", ptmp, env);
	}
	free(ptmp);
	return (i);
}

static int	cd_exit(char *tmp, char ***env, char **path)
{
	perror(ft_strjoin("minishell: cd: ", path[1]));
	(void)tmp;
	free(tmp);
	ft_arr_freer(*env);
	return (1);
}

int	builtin_cd(char	**path)
{
	int		i;
	char	*tmp;
	char	**env;

	if (!path || cd_min(path) == -1)
		return (0);
	i = 0;
	env = env_read(ENV_FILE);
	tmp = env_get("PWD", env);
	if (path[1][0] == '~')
		i = cd_tilde(path[1], tmp, &env);
	else
	{
		i = chdir(path[1]);
		if (i == 0)
			cd_exec(tmp, &env);
	}
	if (i != 0)
		return (cd_exit(tmp, &env, path));
	env_write(ENV_FILE, env);
	free(tmp);
	ft_arr_freer(env);
	return (0);
}
