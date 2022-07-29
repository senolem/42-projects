/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:52:00 by faventur          #+#    #+#             */
/*   Updated: 2022/05/04 14:13:58 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	*btree_search_item(t_btree *root, void *data_ref, int (*cmpf)
			(void *, void *))
{
	void	*ptr;

	if (root)
	{
		if (root->left)
			ptr = btree_search_item(root->left, data_ref, cmpf);
		if (cmpf(data_ref, root->item) == 0)
		{
			ptr = root->item;
			return (ptr);
		}
		if (root->right)
			ptr = btree_search_item(root->right, data_ref, cmpf);
		return (ptr);
	}
	return (NULL);
}
