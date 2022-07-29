/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:25:59 by faventur          #+#    #+#             */
/*   Updated: 2022/03/10 13:57:52 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The calloc() function allocates memory for an array of nmemb elements
** of size bytes each and returns a pointer to the allocated memory. The
** memory is set to zero. If nmemb or size is 0, then calloc() returns
** either NULL, or a unique pointer value that can later be successfully
** passed to free().
**
** Return Value: The calloc() function returns a pointer to the allocated
** memory that is suitably aligned for any kind of variable. On error,
** this function returns NULL. NULL may also be returned by a successful
** call to calloc() with nmemb or size equal to zero. 
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*room;

	room = (unsigned char *)malloc(nmemb * size);
	if (!room)
		return (NULL);
	ft_bzero(room, nmemb * size);
	return ((void *)room);
}
