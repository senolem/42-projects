/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:11:30 by albaur            #+#    #+#             */
/*   Updated: 2022/04/11 09:39:34 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	stack_to_index(t_struct *list)
{
	int	i;
	int	*stmp;
	int	tmp;

	i = 0;
	stmp = malloc(sizeof(int) * list->len_a);
	if (!stmp)
	{
		free(stmp);
		push_swap_error(list);
	}
	tmp = get_min(list->stack_a, list->len_a);
	stmp[tmp] = 0;
	while (++i < list->len_a)
	{
		tmp = get_next_min(list->stack_a, list->len_a, list->stack_a[tmp]);
		stmp[tmp] = i;
	}
	while (i >= 0)
	{
		list->stack_a[i] = stmp[i];
		i--;
	}
	free(stmp);
}

int	check_sort(t_struct *list)
{
	int	i;

	i = 0;
	while (i < list->len_a)
	{
		if (list->stack_a[i] > list->stack_a[i + 1] && i < list->len_a - 1)
			return (0);
		i++;
	}
	return (1);
}

int	push_swap_algo(t_struct *list)
{
	if (check_sort(list))
		return (1);
	if (list->len_a == 2)
		swap_a(list);
	else if (list->len_a == 3)
		sort_3(list);
	else if (list->len_a == 4)
		sort_4(list);
	else if (list->len_a == 5)
		sort_5(list);
	else if (list->len_a > 5)
	{
		stack_to_index(list);
		radix_sort(list);
	}
	return (0);
}
