/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:05:14 by faventur          #+#    #+#             */
/*   Updated: 2022/06/11 15:56:17 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include "libft.h"

typedef struct s_btree {
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

t_btree	*btree_create_node(void *item);
void	btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void	btree_apply_infix(t_btree *root, void (*applyf)(void *));
void	btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void	btree_insert_data(t_btree **root, void *item, int (*cmpf)
			(void *, void *));
void	*btree_search_item(t_btree *root, void *data_ref, int (*cmpf)
			(void *, void *));
void	ft_btree_clear(t_btree *root, void (*del)(void *));
int		btree_level_count(t_btree *root);

#endif