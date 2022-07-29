/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:57:38 by albaur            #+#    #+#             */
/*   Updated: 2022/07/15 22:45:40 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tilde_searcher(char	**path)
{
	size_t	i;

	i = 0;
	while (path[i])
	{
		if (path[i][0] == '~')
			return (1);
	++i;
	}
	return (0);
}

void	tilde_replacer(char **path)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		if (path[i][0] == '~')
		{
			tmp = ft_strdup(path[i]);
			free(path[i]);
			path[i] = ft_strjoin(env_get_arg("HOME"), ++tmp);
		}
		++i;
	}
}
