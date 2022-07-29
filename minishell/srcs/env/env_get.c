/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:54:32 by albaur            #+#    #+#             */
/*   Updated: 2022/07/04 11:15:01 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(char *str, char **env)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (!str || !env || !*env)
		return (NULL);
	tmp = ft_strjoin(str, "=");
	if (!tmp)
		return (NULL);
	if (env_search(tmp, env) >= 0)
	{
		i = env_search(str, env);
		tmp2 = ft_strdup(env[i] + ft_strlen(tmp));
		if (!tmp2)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
		return (tmp2);
	}
	free(tmp);
	return (NULL);
}
