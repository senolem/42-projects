/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:05:18 by faventur          #+#    #+#             */
/*   Updated: 2022/07/19 13:51:35 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_stackiter() function iterates in the stack passed as a parameter
** and applies the f function to the content of every element.
*/

#include "stacks.h"

void	ft_stackiter(t_stack *stack, void (*f)(void *))
{
	t_node	*current;

	if (!stack || stack->top || !f)
		return ;
	current = stack->top;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
}
