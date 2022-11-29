/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:33:16 by albaur            #+#    #+#             */
/*   Updated: 2022/04/04 15:14:48 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		i;
	char	*toreturn;
	long	nb;

	nb = n;
	i = ft_intlen(nb);
	toreturn = (char *)malloc(i * sizeof(char) + 1);
	if (!toreturn)
		return (0);
	toreturn[i--] = '\0';
	if (nb == 0)
		toreturn[0] = 48;
	if (nb < 0)
	{
		toreturn[0] = '-';
		nb = nb * -1;
	}
	while (nb)
	{
		toreturn[i] = 48 + (nb % 10);
		nb = nb / 10;
		i--;
	}
	return (toreturn);
}
