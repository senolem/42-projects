/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:49:33 by faventur          #+#    #+#             */
/*   Updated: 2022/06/01 15:38:34 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_lst_remove_if() function removes from the passed list any
** element the data of which is "equal" to the reference data.
*/

#include "libft.h"

void	ft_lst_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*current;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	current = *begin_list;
	if (!cmp(current->content, data_ref))
	{
		*begin_list = current->next;
		free(current);
		ft_lst_remove_if(begin_list, data_ref, cmp);
	}
	current = *begin_list;
	ft_lst_remove_if(&current->next, data_ref, cmp);
}
