/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op_reverse_rotate.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:30:39 by albaur            #+#    #+#             */
/*   Updated: 2022/04/05 11:44:24 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rotate_reverse_a(t_struct *list)
{
	int	i;
	int	tmp;

	i = list->len_a - 1;
	if (list->len_a > 1)
	{
		tmp = list->stack_a[list->len_a - 1];
		while (i >= 0)
		{
			list->stack_a[i] = list->stack_a[i - 1];
			i--;
		}
		list->stack_a[0] = tmp;
		write(1, "rra\n", 4);
	}
}

void	rotate_reverse_b(t_struct *list)
{
	int	i;
	int	tmp;

	i = list->len_b - 1;
	if (list->len_b > 1)
	{
		tmp = list->stack_b[list->len_b - 1];
		while (i >= 0)
		{
			list->stack_b[i] = list->stack_b[i - 1];
			i--;
		}
		list->stack_b[0] = tmp;
		write(1, "rrb\n", 4);
	}
}

void	rotate_reverse_ab(t_struct *list)
{
	int	i;
	int	tmp;

	i = list->len_a;
	if (list->len_a > 1)
	{
		tmp = list->stack_a[list->len_a - 1];
		while (--i >= 0)
			list->stack_a[i] = list->stack_a[i - 1];
		list->stack_a[0] = tmp;
	}
	i = list->len_b;
	if (list->len_b > 1)
	{
		tmp = list->stack_b[list->len_b - 1];
		while (--i >= 0)
			list->stack_b[i] = list->stack_b[i - 1];
		list->stack_b[0] = tmp;
	}
	write(1, "rrr\n", 4);
}
