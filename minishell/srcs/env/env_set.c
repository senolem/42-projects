/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:55:20 by albaur            #+#    #+#             */
/*   Updated: 2022/07/15 19:29:52 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_set(char *str, char *value, char ***env)
{
	int		i;
	char	*tmp;
	char	**ptr;

	if (!str || !value || !*env)
		return ;
	ptr = *env;
	tmp = ft_strjoin(str, "=");
	if (!tmp)
		return ;
	tmp = ft_concat(tmp, value);
	if (!tmp)
		return ;
	if (env_search(str, *env) >= 0)
	{
		i = env_search(str, *env);
		free(ptr[i]);
		ptr[i] = tmp;
	}
	else
	{
		*env = env_add(tmp, env);
		free(tmp);
	}
}
