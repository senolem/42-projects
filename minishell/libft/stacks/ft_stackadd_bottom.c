/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackadd_bottom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:19:24 by faventur          #+#    #+#             */
/*   Updated: 2022/04/18 17:09:01 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_stackadd_bottom() function adds the new element at the bottom of
** the stack passed as a parameter.
*/

#include "stacks.h"

t_stack	*ft_stackadd_bottom(t_stack *stack, t_node *new)
{
	if (stack != NULL && new != NULL)
	{
		if (stack->bottom == NULL)
		{
			new->prev = NULL;
			stack->top = new;
			stack->bottom = new;
		}
		else
		{
			stack->bottom->next = new;
			new->prev = stack->bottom;
			stack->bottom = new;
		}
		stack->length++;
	}
	return (stack);
}
