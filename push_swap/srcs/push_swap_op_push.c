/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:17:08 by albaur            #+#    #+#             */
/*   Updated: 2022/04/05 11:22:32 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_a(t_struct *list)
{
	int	tmp;
	int	i;

	i = 0;
	if (list->len_b > 0)
	{
		tmp = list->stack_a[0];
		list->stack_a[0] = list->stack_b[0];
		while (i < list->len_b - 1)
		{
			list->stack_b[i] = list->stack_b[i + 1];
			i++;
		}
		list->stack_b[list->len_b - 1] = 0;
		list->len_a++;
		i = list->len_a - 1;
		while (i > 0)
		{
			list->stack_a[i] = list->stack_a[i - 1];
			i--;
		}
		list->stack_a[1] = tmp;
		list->len_b--;
		write(1, "pa\n", 3);
	}
}

void	push_b(t_struct *list)
{
	int	tmp;
	int	i;

	i = 0;
	if (list->len_a > 0)
	{
		tmp = list->stack_b[0];
		list->stack_b[0] = list->stack_a[0];
		while (i < list->len_a - 1)
		{
			list->stack_a[i] = list->stack_a[i + 1];
			i++;
		}
		list->stack_a[list->len_a - 1] = 0;
		list->len_b++;
		i = list->len_b - 1;
		while (i > 0)
		{
			list->stack_b[i] = list->stack_b[i - 1];
			i--;
		}
		list->stack_b[1] = tmp;
		list->len_a--;
		write(1, "pb\n", 3);
	}
}
