/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algo_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:30:00 by albaur            #+#    #+#             */
/*   Updated: 2022/04/08 18:05:09 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_3(t_struct *list)
{
	if (list->stack_a[1] < list->stack_a[0])
		swap_a(list);
	if (!check_sort(list))
		rotate_reverse_a(list);
	if (list->stack_a[1] < list->stack_a[0])
		swap_a(list);
}

void	sort_4(t_struct *list)
{
	int	i;
	int	min;

	i = 0;
	min = list->stack_a[get_min(list->stack_a, list->len_a)];
	while (i < list->len_a)
	{
		if (list->stack_a[0] == min)
			push_b(list);
		else if (list->stack_a[list->len_a - 1] == min)
		{
			rotate_reverse_a(list);
			push_b(list);
		}
		else
			rotate_a(list);
		i++;
	}
	sort_3(list);
	push_a(list);
}

static void	sort_5_get_min_max(t_struct *list, int min, int max)
{
	int	i;

	i = 0;
	while (i < list->len_a)
	{
		if (list->stack_a[0] == min || list->stack_a[0] == max)
			push_b(list);
		else if (list->stack_a[list->len_a - 1] == min
			|| list->stack_a[list->len_a - 1] == max)
		{
			rotate_reverse_a(list);
			push_b(list);
		}
		else
			rotate_a(list);
		i++;
	}
}

void	sort_5(t_struct *list)
{
	int	n;
	int	min;
	int	max;

	n = list->len_a - 3;
	min = list->stack_a[get_min(list->stack_a, list->len_a)];
	max = list->stack_a[get_max(list->stack_a, list->len_a)];
	sort_5_get_min_max(list, min, max);
	sort_3(list);
	while (n)
	{
		push_a(list);
		if (list->stack_a[0] == max)
			rotate_a(list);
		push_a(list);
		n--;
	}
}

void	radix_sort(t_struct *list)
{
	int	i;
	int	j;
	int	bits;

	i = 0;
	bits = ft_intlen(ft_dectobin(list->len_a - 1));
	while (i < bits)
	{
		j = 0;
		while (j++ < list->max_length)
		{
			if (((list->stack_a[0] >> i) & 1) == 1)
				rotate_a(list);
			else
				push_b(list);
		}
		while (list->len_b != 0)
			push_a(list);
		i++;
	}
}
