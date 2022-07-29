/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackinsert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:36:14 by faventur          #+#    #+#             */
/*   Updated: 2022/06/22 16:36:13 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

static void	ft_nodelinker(t_stack *stack, t_node *current, t_node *new)
{
	if (current->next == NULL)
		stack = ft_stackadd_bottom(stack, new);
	else if (current->prev == NULL)
		stack = ft_stackadd_top(stack, new);
	else
	{
		current->next->prev = new;
		current->prev->next = new;
		new->prev = current->prev;
		new->next = current;
		stack->length++;
	}
}

t_stack	*ft_stackinsert(t_stack *stack, t_node *node, int position)
{
	t_node	*temp;
	int		i;

	if (stack != NULL && node != NULL)
	{
		temp = stack->top;
		i = 1;
		while (temp != NULL && i <= position)
		{
			if (position == i)
				ft_nodelinker(stack, temp, node);
			else
				temp = temp->next;
			i++;
		}
	}
	return (stack);
}
