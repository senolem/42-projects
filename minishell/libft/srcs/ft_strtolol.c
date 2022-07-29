/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:00:43 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 15:50:33 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strtolol(const char *str)
{
	size_t		i;
	long long	rt;
	int			pm;

	if (!str)
		return (0);
	rt = 0;
	i = 0;
	pm = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			pm *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rt = rt * 10 + (str[i] - 48);
		if (rt * pm > 2147483647)
			return (0);
		else if (rt * pm < -2147483648)
			return (0);
		i++;
	}
	return (1);
}
