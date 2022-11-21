/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:11:13 by albaur            #+#    #+#             */
/*   Updated: 2022/04/22 08:21:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	toreturn;

	i = 0;
	sign = 1;
	toreturn = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		if (toreturn * sign > 2147483647)
			return (-1);
		else if (toreturn * sign < -2147483648)
			return (0);
		toreturn = (str[i] - '0') + (toreturn * 10);
		i++;
	}
	return (toreturn * sign);
}
