/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:00:52 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 15:49:07 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strstr() function finds the first occurrence of the substring
** needle in the string haystack. The terminating null bytes are not
** compared.
** 
** Return Value: This function returns a pointer to the beginning of
** the substring, or NULL if the substring is not found.
*/

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!haystack || !needle)
		return (NULL);
	i = 0;
	if (ft_strlen(haystack) < ft_strlen(needle))
		return (NULL);
	while (i <= ft_strlen(haystack) - ft_strlen(needle))
	{
		j = 0;
		while (j < ft_strlen(needle))
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
