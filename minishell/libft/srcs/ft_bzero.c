/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:15:27 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 21:13:51 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The bzero() function sets the first n bytes of the area starting 
** at s to zero.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	if (!s || n <= 0)
		return ;
	while (n--)
		*(unsigned char *)s++ = '\0';
}
