/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:40:04 by faventur          #+#    #+#             */
/*   Updated: 2022/11/09 11:40:46 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memsalloc(size_t count, size_t size, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	while (i < count * size)
	{
		ptr[i] = c;
		i++;
	}
	return (ptr);
}
