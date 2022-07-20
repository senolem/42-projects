/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:23:13 by albaur            #+#    #+#             */
/*   Updated: 2022/04/05 11:44:06 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rotate_a(t_struct *list)
{
	int	i;
	int	tmp;

	i = 0;
	if (list->len_a > 1)
	{
		tmp = list->stack_a[i];
		while (i < list->len_a - 1)
		{
			list->stack_a[i] = list->stack_a[i + 1];
			i++;
		}
		list->stack_a[list->len_a - 1] = tmp;
		write(1, "ra\n", 3);
	}
}

void	rotate_b(t_struct *list)
{
	int	i;
	int	tmp;

	i = 0;
	if (list->len_b > 1)
	{
		tmp = list->stack_b[i];
		while (i < list->len_b - 1)
		{
			list->stack_b[i] = list->stack_b[i + 1];
			i++;
		}
		list->stack_b[list->len_b - 1] = tmp;
		write(1, "rb\n", 3);
	}
}

void	rotate_ab(t_struct *list)
{
	int	i;
	int	tmp;

	i = -1;
	if (list->len_a > 1)
	{
		tmp = list->stack_a[i];
		while (++i < list->len_a)
			list->stack_a[i] = list->stack_a[i + 1];
		list->stack_a[list->len_a - 1] = tmp;
	}
	i = -1;
	if (list->len_b > 1)
	{
		tmp = list->stack_b[i];
		while (++i < list->len_b)
			list->stack_b[i] = list->stack_b[i + 1];
		list->stack_b[list->len_b - 1] = tmp;
	}
	write(1, "rr\n", 3);
}
