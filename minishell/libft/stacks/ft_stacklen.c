/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacklen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:59:05 by albaur            #+#    #+#             */
/*   Updated: 2022/07/20 15:00:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

int	ft_stacklen(t_stack *stack)
{
	size_t	len;
	t_node	*node;

	node = stack->top;
	len = 0;
	while (node)
	{
		node = node->next;
		++len;
	}
	return (len);
}
