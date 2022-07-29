/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:04:30 by faventur          #+#    #+#             */
/*   Updated: 2022/06/01 16:18:19 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_stacksort() function sorts the list given as a parameter, using
** the function pointer cmp to select the order to apply, and returns a
** pointer to the first element of the sorted list.
*/

#include "stacks.h"

void	ft_stacksort(t_stack *begin_list, int (*cmp)())
{
	t_node	*current;
	t_node	*temp;
	void	*temporary;

	current = begin_list->top;
	while (current->next)
	{
		temp = current->next;
		while (temp)
		{
			if (cmp(current->content, temp->content) > 0)
			{
				temporary = temp->content;
				temp->content = current->content;
				current->content = temporary;
			}
			temp = temp->next;
		}
		current = current->next;
	}
}
