/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:48:03 by faventur          #+#    #+#             */
/*   Updated: 2022/07/11 13:25:58 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	pipe_counter(t_stack *stack)
{
	size_t	i;
	t_node	*node;

	i = 0;
	node = stack->top;
	while (node)
	{
		if (!ft_tokcmp(node->content, pipe_type))
			++i;
		node = node->next;
	}
	return (i);
}
