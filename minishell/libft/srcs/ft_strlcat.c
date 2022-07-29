/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:45:34 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 17:52:41 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strlcat() function concatenates strings. Unlike the strncat(3)
** function, strlcat() takes the full size of the buffer (not just the 
** length) and guarantees to NUL-terminate the result (as long as there
** is at least one byte free in dst). Note that a byte for the NUL should
** be included in size. Also note tat strlcat() only operates on NUL-
** terminated strings.
** 
** The strlcat() function appends the NUL-terminated string src to the end of
** dst. It will append at most size - strlen(dst) - 1 bytes, NUL-terminating
** the result.
** 
** Return Values: The strlcat() function returns the total length of the string
** it tried to create. That means the initial length of dst plus the length of
** src. It was done to make truncation detection simple.
*/

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	if (!dest || !src)
		return (0);
	i = 0;
	j = ft_strlen(dest);
	dest_len = j;
	src_len = ft_strlen(src);
	if (size <= 0)
		return (src_len);
	while ((j < size - 1 && src[i] != '\0') && size != 0)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	if (size < dest_len)
		return (src_len + size);
	else
		return (src_len + dest_len);
}
