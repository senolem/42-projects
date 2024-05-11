/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:54:51 by faventur          #+#    #+#             */
/*   Updated: 2023/02/13 16:57:24 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The atoi() function converts the initial portion of the string
** pointed to by nptr to int.
** 
** Return Value: The converted value.
*/

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		counter;
	long	res;

	counter = 0;
	res = 0;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if ((*nptr && *nptr == '-' && counter++ == 0) || (*nptr && *nptr == '+'))
		nptr++;
	while ((*nptr >= '0' && *nptr <= '9') && *nptr)
		res = res * 10 + (*nptr++ - '0');
	if (counter == 1)
		res *= -1;
	if (res > 2147483647)
		return (-1);
	if (res < -2147483648)
		return (0);
	return (res);
}
