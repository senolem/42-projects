/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op_swap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:22:48 by albaur            #+#    #+#             */
/*   Updated: 2022/04/05 11:22:49 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap_a(t_struct *list)
{
	int	tmp;

	if (list->len_a > 1)
	{
		tmp = list->stack_a[0];
		list->stack_a[0] = list->stack_a[1];
		list->stack_a[1] = tmp;
		write(1, "sa\n", 3);
	}
}

void	swap_b(t_struct *list)
{
	int	tmp;

	if (list->len_b > 1)
	{
		tmp = list->stack_b[0];
		list->stack_b[0] = list->stack_b[1];
		list->stack_b[1] = tmp;
		write(1, "sb\n", 3);
	}
}

void	swap_ab(t_struct *list)
{
	int	tmp;

	if (list->len_a > 1)
	{
		tmp = list->stack_a[0];
		list->stack_a[0] = list->stack_a[1];
		list->stack_a[1] = tmp;
	}
	if (list->len_b > 1)
	{
		tmp = list->stack_b[0];
		list->stack_b[0] = list->stack_b[1];
		list->stack_b[1] = tmp;
	}
	write(1, "ss\n", 3);
}
