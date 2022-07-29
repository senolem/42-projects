/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:42:55 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 15:51:03 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strrchr() function finds the last occurrence of c (converted to a
** character) in string. The ending null character is considered part of the
** string.
** 
** Return Value: The strrchr() function returns a pointer to the last
** occurrence of c in string. If the given character is not found, a NULL
** pointer is returned.
*/

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*charptr;

	if (!str)
		return (NULL);
	charptr = NULL;
	while (*str != '\0')
	{
		if (*str == (const char)c)
			charptr = (char *)str;
		str++;
	}
	if ((*str) == (const char)c)
		charptr = (char *)str;
	return (charptr);
}
