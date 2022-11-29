/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:35:04 by albaur            #+#    #+#             */
/*   Updated: 2022/02/22 14:40:57 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptrdst;
	const char	*ptrsrc;

	ptrdst = dst;
	ptrsrc = src;
	if (!dst && !src)
		return (0);
	while (n--)
		*ptrdst++ = *ptrsrc++;
	return (dst);
}
