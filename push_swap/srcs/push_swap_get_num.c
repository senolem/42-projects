/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_get_num.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:59:10 by albaur            #+#    #+#             */
/*   Updated: 2022/04/05 11:11:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	get_min(int	*stack, int len)
{
	int	min;
	int	itmp;

	min = 2147483647;
	while (len - 1 >= 0)
	{
		if (stack[len - 1] < min)
		{
			min = stack[len - 1];
			itmp = len - 1;
		}
		len--;
	}
	return (itmp);
}

int	get_next_min(int *stack, int len, int tmp)
{
	int	min;
	int	itmp;

	min = 2147483647;
	while (len - 1 >= 0)
	{
		if (stack[len - 1] < min && stack[len - 1] > tmp)
		{
			min = stack[len - 1];
			itmp = len - 1;
		}
		len--;
	}
	return (itmp);
}

int	get_max(int *stack, int len)
{
	int	max;
	int	itmp;

	max = -2147483647;
	while (len - 1 >= 0)
	{
		if (stack[len - 1] > max)
		{
			max = stack[len - 1];
			itmp = len - 1;
		}
		len--;
	}
	return (itmp);
}
