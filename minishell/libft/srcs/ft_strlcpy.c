/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:52:13 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 20:12:56 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strlcpy() function copies a string. Unlike the strncpy(3) function,
** strlcpy() takes the full size of the buffer (not just the length) and
** guarantees to NUL-terminate the result (as long as size is larger than
** 0. Note that a byte for the NUL should be included in size. Also note
** that strlcpy() only operates on NUL-terminated strings.
** 
** The strlcpy() function copies up to size - 1 characters from the NUL-
** terminated string src to dst, NUL-terminating the result.
** 
** Return Values: The strlcpy() function returns the total length of the
** string it tried to create. It was done to make truncation detection
** simple.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	if (!dest || !src)
		return (0);
	i = 0;
	srclen = ft_strlen(src);
	if (size <= 0)
		return (srclen);
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}
