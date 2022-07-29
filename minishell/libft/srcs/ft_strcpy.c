/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:55:47 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 15:30:15 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strcpy() function copies the string pointed to by src, including
** the terminating null byte ('\0'), to the buffer pointed to by dest.
** The strings may not overlap, and the destination string dest must be
** large enough to receive the copy. Beware of buffer overruns! (See BUGS.)
** 
** Return Value: The strcpy() function returns a pointer to the destination
** string dest.
*/

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
