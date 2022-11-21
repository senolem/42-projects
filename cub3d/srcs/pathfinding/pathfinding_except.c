/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_except.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:30:57 by albaur            #+#    #+#             */
/*   Updated: 2022/11/11 12:46:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_vec2	pathfinding_pos_except(t_data *data, t_vec2 pos, size_t	distance)
{
	int		tries;
	t_vec2	pos2;

	tries = 1500;
	pos2 = pathfinding_pos_dist(data, (t_vec2){0, 0},
			data->ray_data.camera.pos, distance);
	while (pos.x - 0.5 == pos2.x && pos.y - 0.5 == pos2.y)
	{
		pos2 = pathfinding_pos_dist(data, (t_vec2){0, 0},
				data->ray_data.camera.pos, distance);
		if (tries <= 0)
			return ((t_vec2){-1, -1});
		--tries;
	}
	return (pos2);
}

t_vec2	pathfinding_pos_close(t_data *data, t_vec2 pos, int distance)
{
	int		tries;
	t_vec	pos2;
	t_vec2	tmp;
	double	dist;

	tries = 1500;
	while (tries > 0)
	{
		pos2 = pathfinding_get_pos(data);
		tmp = (t_vec2){pos2.x, pos2.y};
		dist = ft_vect2_distance_calc(pos, tmp);
		if (dist <= distance && !(pos.x - 0.5 == tmp.x && pos.y - 0.5 == tmp.y))
			return ((t_vec2){tmp.x + 0.5, tmp.y + 0.5});
		--tries;
	}
	return ((t_vec2){-1, -1});
}
