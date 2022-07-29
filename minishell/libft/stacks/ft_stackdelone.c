/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 20:16:24 by faventur          #+#    #+#             */
/*   Updated: 2022/07/19 13:01:47 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_stackdelone() function frees the memory of the element passed
** as a parameter with the del function and free(3). The memory of next
** mustn't be freed.
*/

#include "stacks.h"

void	ft_stackdelone(t_stack *stack, t_node *node, void (*del)(void *))
{
	if (!node || !stack || !stack->top || !del)
		return ;
	if (node->next == NULL)
	{
		stack->bottom = node->prev;
		if (stack->bottom)
			stack->bottom->next = NULL;
	}
	else if (node->prev == NULL)
	{
		stack->top = node->next;
		if (stack->top)
			stack->top->prev = NULL;
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	del(node->content);
	free(node);
}
