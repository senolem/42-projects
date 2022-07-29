/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:54:51 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 17:22:15 by faventur         ###   ########.fr       */
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
	int		res;
	char	*charptr;

	if (!nptr)
		return (-1);
	counter = 0;
	res = 0;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if ((*nptr && *nptr == '-' && counter++ == 0) || (*nptr && *nptr == '+'))
		nptr++;
	charptr = (char *)nptr;
	while ((*charptr >= '0' && *charptr <= '9'))
		charptr++;
	if (counter == 0 && (charptr - nptr) > 10)
		return (-1);
	else if (counter == 1 && (charptr - nptr) > 11)
		return (0);
	while ((*nptr >= '0' && *nptr <= '9') && *nptr)
		res = res * 10 + (*nptr++ - '0');
	if (counter == 1)
		res *= -1;
	return (res);
}
