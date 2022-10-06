/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:46:30 by faventur          #+#    #+#             */
/*   Updated: 2022/10/02 16:04:58 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_prop_init(t_prop *obj)
{
	obj->start_pos = 0;
}

t_vector	ft_get_coordinates(char **map, char prop)
{
	t_vector	coord;

	coord.x = 0;
	coord.y = 0;
	while (map[coord.y])
	{
		while (map[coord.y][coord.x])
		{
			if (map[coord.y][coord.x] == prop)
			{
				coord.y *= 65;
				coord.x *= 65;
				return (coord);
			}
			coord.x++;
		}
		coord.x = 0;
		coord.y++;
	}
	coord.x = 3000;
	coord.y = 3000;
	return (coord);
}

t_vector	ft_get_x_and_y(char **map, char prop)
{
	t_vector	coord;

	coord.x = 0;
	coord.y = 0;
	while (map[coord.y])
	{
		while (map[coord.y][coord.x])
		{
			if (map[coord.y][coord.x] == prop)
				return (coord);
			coord.x++;
		}
		coord.x = 0;
		coord.y++;
	}
	coord.x = 3000;
	coord.y = 3000;
	return (coord);
}

t_vector	ft_get_char_pos(char **map)
{
	t_vector	pos;

	pos = ft_get_x_and_y(map, 'P');
	if (pos.x == 3000)
		pos = ft_get_x_and_y(map, 'L');
	if (pos.x == 3000)
		pos = ft_get_x_and_y(map, 'F');
	if (pos.x == 3000)
		pos = ft_get_x_and_y(map, 'B');
	return (pos);
}
