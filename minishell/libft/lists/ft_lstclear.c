/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:53:37 by faventur          #+#    #+#             */
/*   Updated: 2022/11/20 16:03:55 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_lstclear() function suppresses and frees the memory of the
** element passed as a parameter and of all the following elements by
** using the del function and free(3). Finally, the initial pointer is
** to be set to NULL.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->content)
			ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
