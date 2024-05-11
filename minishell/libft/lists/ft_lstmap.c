/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:44:34 by faventur          #+#    #+#             */
/*   Updated: 2022/11/21 10:32:34 by faventur         ###   ########.fr       */
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

void	*ft_lst_content_creator(t_list *lst, t_list *new_lst,
		void *(*f)(void *), void (*del)(void *))
{
	void	*tmp2;

	tmp2 = f(lst->content);
	if (!tmp2)
	{
		ft_lstclear(&new_lst, del);
		return (NULL);
	}
	return (tmp2);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;
	void	*tmp2;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		tmp2 = ft_lst_content_creator(lst, new_lst, f, del);
		if (!tmp2)
			return (NULL);
		temp = ft_lstnew(tmp2);
		if (temp == NULL)
		{
			ft_lstclear(&new_lst, del);
			free(tmp2);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, temp);
		lst = lst->next;
	}
	return (new_lst);
}
