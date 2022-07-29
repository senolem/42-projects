/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:53:37 by faventur          #+#    #+#             */
/*   Updated: 2022/06/11 15:44:37 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_btree_clear() function suppresses and frees the memory of the
** the element passed as a parameter and of all the following elements
** by using the del function and free(3). Finally, the initial pointer
** is to be set to NULL.
*/

#include "ft_btree.h"

void	ft_btree_clear(t_btree *root, void (*del)(void *))
{
	if (!root || !del)
		return ;
	if (root->left)
		ft_btree_clear(root->left, del);
	if (root->right)
		ft_btree_clear(root->right, del);
	del(root->item);
	free(root);
}
