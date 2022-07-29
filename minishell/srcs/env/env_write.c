/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:04:12 by albaur            #+#    #+#             */
/*   Updated: 2022/07/01 14:55:39 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_write(char *path, char **env)
{
	size_t	i;
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
