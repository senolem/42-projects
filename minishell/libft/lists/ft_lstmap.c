/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:44:34 by faventur          #+#    #+#             */
/*   Updated: 2022/03/04 16:45:03 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_lstmap() function iterates in the list passed as a parameter
** and applies the f function to the content of every element of the
** list. It creates a new list resulting from the successive
** applications of f. The del function is present in order to destroy
** an element if necessary.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;

	new_lst = NULL;
	temp = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (temp == NULL)
		{
			ft_lstclear(&temp, del);
			break ;
		}
		ft_lstadd_back(&new_lst, temp);
		lst = lst->next;
	}
	ft_lstclear(&lst, del);
	return (new_lst);
}
