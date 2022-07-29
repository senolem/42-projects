/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:10:57 by faventur          #+#    #+#             */
/*   Updated: 2022/05/03 15:03:01 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	btree_insert_data(t_btree **root, void *item, int (*cmpf)
			(void *, void *))
{
	t_btree	*new;

	new = btree_create_node(item);
	if (root)
	{
		if (*root)
		{
			if (cmpf(item, (*root)->item) < 0)
			{
				if ((*root)->left)
					btree_insert_data(&(*root)->left, item, cmpf);
				else
					(*root)->left = new;
			}
			else
			{
				if ((*root)->right)
					btree_insert_data(&(*root)->right, item, cmpf);
				else
					(*root)->right = new;
			}
		}
		else
			*root = new;
	}
}
