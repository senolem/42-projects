/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 04:44:43 by albaur            #+#    #+#             */
/*   Updated: 2022/05/11 05:59:42 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi(const char *str)
{
	int			i;
	long long	nb;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
			++i;
		}
	}
	while (str[i] >= '0' && str[i] <= '9')
		{
			nb = (str[i] - '0') + (nb * 10);
			++i;
		}
	return (nb * sign);
}

int	main(void)
{
	printf("%i\n", ft_atoi("-4893024"));
}