/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstrbool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:19:16 by faventur          #+#    #+#             */
/*   Updated: 2022/06/26 16:41:22 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_functions.h"

int	ft_strnstrbool(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (len == 0 && !needle[0])
		return (0);
	if (ft_strlen(haystack) < ft_strlen(needle) || len < ft_strlen(needle))
		return (1);
	while (i <= ft_strlen(haystack) - ft_strlen(needle) && i < len)
	{
		j = 0;
		while (j < ft_strlen(needle) && i + j < len)
		{
			if (*(char *)(haystack + i + j) != *(char *)(needle + j))
				break ;
			j++;
		}
		if (j == ft_strlen(needle))
			return (0);
		i++;
	}
	return (1);
}
