/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:07:13 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 15:30:21 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strcat() function appends the src string to the dest string,
** overwriting the terminating null byte ('\0') at the end of dest, and
** then adds a terminating null byte. The strings may not overlap, and
** the dest string must have enough space for the result. If dest is not
** large enough, program behavior is unpredictable; buffer overruns are a
** favorite avenue for attacking secure programs.
** 
** Return Value: The strcat() function returns a pointer to the resulting
** string dest.
*/

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	if (!dest || !src)
		return (NULL);
	i = 0;
	j = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
