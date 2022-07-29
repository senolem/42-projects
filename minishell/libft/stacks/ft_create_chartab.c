/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_chartab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:24:38 by faventur          #+#    #+#             */
/*   Updated: 2022/06/01 17:25:32 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_create_chartab() function creates, with malloc(3) a string
** array from the stack passed as a parameter.
*/

#include "stacks.h"

char	**ft_create_chartab(t_stack *stack)
{
	t_node	*current;
	char	**arr;
	int		i;

	arr = (char **)malloc(sizeof(char *) * (ft_stacksize(stack)) + 1);
	if (!stack || !arr)
		return (NULL);
	current = stack->top;
	i = 0;
	while (current->next)
	{
		arr[i] = ft_strdup(current->content);
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
