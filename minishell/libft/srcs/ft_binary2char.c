/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary2char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:47:32 by faventur          #+#    #+#             */
/*   Updated: 2022/05/10 18:15:48 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The mt_binary2char() function transforms a binary into a character.
*/

#include "libft.h"

char	ft_binary2char(char *binary)
{
	char	c;
	int		i;
	int		y;

	if (!binary)
		return (0);
	i = 7;
	y = 0;
	c = 0;
	while (i >= 0)
	{
		if (binary[i] == '1')
			c += ft_power(2, y);
		i--;
		y++;
	}
	return (c);
}
