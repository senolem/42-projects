/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:26:26 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 17:26:23 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memcmp() function compares the first n bytes (each interpreted as
** unsigned char) of the memory areas s1 and s2.
** 
** Return Value: The memcmp() function returns an integer less than,
** equal to, or greater than zero if the first n bytes of s1 is found,
** respectively, to be less than, to match, or be greater than the first
** n bytes of s2.
** For a nonzero return value, the sign is determined by the sign of the
** difference between the first pair of bytes (interpreted as unsigned
** char) that differ in s1 and s2.
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2 || !n)
		return (0);
	i = 0;
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && i < n - 1)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
