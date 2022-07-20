/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:21:03 by albaur            #+#    #+#             */
/*   Updated: 2022/06/19 16:16:36 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_search(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(str, env[i], ft_strlen(str)))
			return (i);
		++i;
	}
	return (-1);
}

void	throw_error(t_data *data, char *msg, int err)
{
	free(data);
	if (err != 0)
		errno = err;
	perror(msg);
	exit(EXIT_FAILURE);
}
