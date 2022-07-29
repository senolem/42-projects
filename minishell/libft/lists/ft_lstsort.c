/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:04:30 by faventur          #+#    #+#             */
/*   Updated: 2022/06/01 16:18:36 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_lstsort() function sorts the list given as a parameter, using
** the function pointer cmp to select the order to apply, and returns a
** pointer to the first element of the sorted list.
*/

#include "libft.h"

void	ft_lstsort(t_list **begin_list, int (*cmp)())
{
	t_list	*current;
	t_list	*temp;
	void	*temporary;

	current = *begin_list;
	temporary = NULL;
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
