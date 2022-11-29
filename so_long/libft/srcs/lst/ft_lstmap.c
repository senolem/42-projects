/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:33:16 by albaur            #+#    #+#             */
/*   Updated: 2022/03/02 11:18:49 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;

	if (!lst || !f)
		return (0);
	list = ft_lstnew(lst->content);
	if (!list)
		return (0);
	list->content = f(list->content);
	list->next = ft_lstmap(lst->next, f, del);
	return (list);
}
