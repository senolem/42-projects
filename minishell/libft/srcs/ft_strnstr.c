/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:29:35 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 15:44:46 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strnstr() function locates the first occurrence of the null-terminated
** string needle in the	string haystack, where no more than	len characters
** are searched.
** 
** Return Value: If	needle is an empty string, haystack is returned; if
** needle occurs nowhere in	haystack, NULL is returned; otherwise a pointer
** to the first	character of the first occurrence of needle is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!haystack || !needle)
		return (NULL);
	i = 0;
	if (len == 0 && !needle[0])
		return ((char *)haystack);
	if (ft_strlen(haystack) < ft_strlen(needle) || len < ft_strlen(needle))
		return (NULL);
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
			return (&*(char *)(haystack + i));
		i++;
	}
	return (NULL);
}
