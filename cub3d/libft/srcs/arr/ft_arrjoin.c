/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:19:05 by albaur            #+#    #+#             */
/*   Updated: 2022/06/16 15:20:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrjoin(char **arr1, char **arr2)
{
	char	**new;
	int		len1;
	int		len2;

	if (!arr1 && !arr2)
		return (NULL);
	len1 = ft_arrlen(arr1);
	len2 = ft_arrlen(arr2) + len1;
	new = malloc(sizeof(char *) * (len1 + 1));
	if (!new)
		return (NULL);
	new[len2] = 0;
	while (len2--)
	{
		if (len2 >= len1)
			new[len2] = ft_strdup(arr2[len2 - len1]);
		else
			new[len2] = ft_strdup(arr1[len2]);
		if (!new[len2])
		{
			free(new);
			return (NULL);
		}
	}
	return (new);
}
