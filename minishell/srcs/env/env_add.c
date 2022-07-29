/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:54:59 by albaur            #+#    #+#             */
/*   Updated: 2022/07/01 15:54:44 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_add(char *str, char ***env)
{
	size_t	i;
	char	**ptr;
	char	**new;

	i = 0;
	ptr = *env;
	new = malloc(sizeof(char *) * (ft_arrlen(ptr) + 2));
	if (!new)
		return (NULL);
	while (ptr[i])
	{
		new[i] = ptr[i];
		++i;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
	{
		free(new);
		return (NULL);
	}
	new[i + 1] = 0;
	free(*env);
	return (new);
}
