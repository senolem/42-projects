/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:47:11 by faventur          #+#    #+#             */
/*   Updated: 2022/04/15 11:55:15 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_power() function calculates the power of a number.
*/
#include "libft.h"

int	ft_power(int n, int power)
{
	int	result;

	if (power < 0 || !n)
		return (0);
	result = 1;
	while (power--)
		result *= n;
	return (result);
}
