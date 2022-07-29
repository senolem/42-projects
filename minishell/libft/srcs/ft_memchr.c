/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:13:11 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 17:24:42 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memchr() function scans the initial n bytes of the memory area
** pointed to by s for the first instance of c. Both c and the bytes
** of the memory area pointed to by s are interpreted as unsigned char.
** 
** Return Value: The memchr() function returns a pointer to the matching
** byte or NULL if the character does not occur in the given memory area.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (!s || !n)
		return (NULL);
	while (n > 0 && *(unsigned char *)s != (unsigned char)c)
	{
		s++;
		n--;
	}
	if (n == 0)
		return (NULL);
	return ((void *)s);
}
