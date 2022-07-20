/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:46:40 by albaur            #+#    #+#             */
/*   Updated: 2022/06/19 16:16:23 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**env_read(char *path)
{
	int		i;
	int		fd;
	char	buffer[2];
	char	*tmp;
	char	**env;

	i = 1;
	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY, 0777);
	if (fd < 0)
		return (NULL);
	while (i > 0)
	{
		i = read(fd, buffer, 1);
		if (i == -1)
			return (NULL);
		buffer[i] = 0;
		tmp = ft_strjoin(tmp, buffer);
	}
	env = ft_split(tmp, '\n');
	close(fd);
	if (!env)
		return (NULL);
	return (env);
}

char *env_get(char *str, char **env)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (!str || !env)
		return (NULL);
	tmp = ft_strjoin(str, "=");
	if (!tmp)
		return (NULL);
	if (env_search(str, env))
	{
		i = env_search(str, env);
		tmp2 = ft_strdup(env[i] + ft_strlen(tmp));
		if (!tmp2)
			return (NULL);
		return (tmp2);
	}
	return (0);
}

char	**env_add(char *str, char ***env)
{
	int		i;
	char	**ptr;
	char	**new;

	i = 0;
	ptr = *env;
	new = malloc(sizeof(char *) * (ft_arrlen(ptr) + 2));
	if (!new)
		return (NULL);
	while (ptr[i])
	{
		new[i] = ft_strdup(ptr[i]);
		++i;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = 0;
	free(*env);
	return (new);
}

void	env_set(char *str, char *value, char ***env)
{
	int		i;
	char	*tmp;
	char	**ptr;

	ptr = *env;
	tmp = ft_strjoin(str, "=");
	tmp = ft_strjoin(tmp, value);
	if (env_search(str, *env) >= 0)
	{
		i = env_search(str, *env);
		ptr[i] = tmp;
	}
	else
		*env = env_add(tmp, env);
}


void	env_write(char *path, char **env)
{
	int		i;
	int		fd;

	i = 0;
	if (!path || !env)
		return ;
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return ;
	while (env[i])
	{
		ft_putendl_fd(env[i], fd);
		++i;
	}
	close(fd);
}
