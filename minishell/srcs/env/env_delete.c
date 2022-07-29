/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:32:29 by albaur            #+#    #+#             */
/*   Updated: 2022/07/01 15:55:01 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_delete(char *str, char ***env)
{
	t_delete	d;

	d.i = 0;
	d.j = 0;
	d.k = env_search(str, *env);
	d.ptr = *env;
	d.new = malloc(sizeof(char *) * (ft_arrlen(d.ptr)));
	if (!d.new)
		return (NULL);
	while (d.ptr[d.j])
	{
		if (d.j == d.k)
			free(d.ptr[d.j]);
		else
		{
			d.new[d.i] = d.ptr[d.j];
			++d.i;
		}
		++d.j;
	}
	d.new[d.i] = 0;
	free(*env);
	return (d.new);
}
