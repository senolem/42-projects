/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:23:13 by faventur          #+#    #+#             */
/*   Updated: 2022/02/28 10:52:18 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strnew() function allocates (with malloc(3)) and returns a
** "fresh" null-terminated string. Every character of the string is
** set to '\0'. If the allocation fails, it returns NULL.
*/

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*room;

	room = (char *)malloc(sizeof(char) * (size + 1));
	if (!room)
		return (NULL);
	ft_bzero(room, size + 1);
	return (room);
}
