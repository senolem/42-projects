/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_remove_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:49:33 by faventur          #+#    #+#             */
/*   Updated: 2022/06/21 15:26:48 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_stack_remove_if() function removes from the passed list any
** element the data of which is "equal" to the reference data.
*/

#include "stacks.h"

static void	ft_stack_remove_if_pt2(t_stack *begin_list, void *data_ref,
	int (*cmp)())
{
	t_node	*current;
	t_node	*tmp;
	t_node	*prev;

	prev = begin_list->top;
	current = begin_list->top->next;
	while (current)
	{
		if (!cmp(current->content, data_ref))
		{
			tmp = current;
			current = current->next;
			current->prev = tmp->prev;
			prev->next = current;
			free(tmp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	ft_stack_remove_if(t_stack *begin_list, void *data_ref, int (*cmp)())
{
	t_node	*tmp;

	if (begin_list == NULL)
		return ;
	while (!cmp(data_ref, begin_list->top->content))
	{
		tmp = begin_list->top;
		begin_list->top = begin_list->top->next;
		begin_list->top->prev = NULL;
		free(tmp);
	}
	ft_stack_remove_if_pt2(begin_list, data_ref,
		cmp);
}
