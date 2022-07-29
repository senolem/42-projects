/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:56:54 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 15:36:21 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strncpy() function is similar to the strcpy() function, except that
** at most n bytes of src are copied. Warning: If there is no null byte
** among the first n bytes of src, the string placed in dest will not be
** null-terminated.
** 
** If the length of src is less than n, strncpy() writes additional null
** bytes to dest to ensure that a total of n bytes are written.
** 
** Return Value: The strncpy() function returns a pointer to the destination
** string dest.
*/

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
