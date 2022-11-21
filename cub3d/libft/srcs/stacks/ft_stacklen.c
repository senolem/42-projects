/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacklen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:59:05 by albaur            #+#    #+#             */
/*   Updated: 2022/10/11 16:42:12 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
