/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 04:49:45 by albaur            #+#    #+#             */
/*   Updated: 2022/04/22 10:58:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_lstc_delete(t_component **lst, int x, int y)
{
	t_component	*tmp;
	t_component	*target;

	tmp = *lst;
	if (tmp && tmp->x == x && tmp->y == y)
	{
		*lst = tmp->next;
		free(tmp);
		tmp = NULL;
		return ;
	}
	while (tmp && tmp->next)
	{
		if (tmp->next->x == x && tmp->next->y == y)
		{
			target = tmp->next;
			tmp->next = tmp->next->next;
			free(target);
			target = NULL;
		}
		tmp = tmp->next;
	}
}

int	ft_lstc_add(t_component **lst, int x, int y)
{
	t_component	*new;

	new = (t_component *)malloc(sizeof(t_component));
	if (!new)
		return (0);
	new->x = x;
	new->y = y;
	new->next = NULL;
	ft_lstc_add_back(lst, new);
	return (1);
}

void	ft_lstc_add_back(t_component **lst, t_component *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ft_lstc_last(*lst)->next = new;
}

t_component	*ft_lstc_last(t_component *component)
{
	if (!component)
		return (0);
	while (component->next)
		component = component->next;
	return (component);
}

void	get_back_to_head(t_data *data)
{
	while (data->hud.num != data->hud.num->head)
		data->hud.num = data->hud.num->next;
}
