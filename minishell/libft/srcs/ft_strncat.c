/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:06:58 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 15:35:30 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strncat() function is similar to the strcat() function, except that
** it will use at most n bytes from src; and src does not need to be null-
** terminated if it contains n or more bytes.
** 
** As with strcat(), the resulting string in dest is always null-terminated.
** If src contains n or more bytes, strncat() writes n+1 bytes to dest (n
** from src plus the terminating null byte). Therefore, the size of dest
** must be at least strlen(dest)+n+1.
** 
** Return Value: The strncat() function returns a pointer to the resulting
** string dest.
*/

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	if (!dest || !src)
		return (NULL);
	i = 0;
	j = ft_strlen(dest);
	if (n == 0)
		return (NULL);
	while (i < n && src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
