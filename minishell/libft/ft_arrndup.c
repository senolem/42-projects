/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:33:29 by albaur            #+#    #+#             */
/*   Updated: 2022/06/16 16:41:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrndup(char **str, int i)
{
	char	**tmp;

	tmp = NULL;
	if (!str || !i)
		return (NULL);
	tmp = malloc(sizeof(char *) * (i + 1));
	tmp[i] = NULL;
	while (i--)
	{
		tmp[i] = ft_strdup(str[i]);
		if (!tmp[i])
		{
			free(tmp);
			return (NULL);
		}
	}
	return (tmp);
}
