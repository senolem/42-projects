/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:33:59 by albaur            #+#    #+#             */
/*   Updated: 2022/11/10 11:21:00 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	init_direction_child(t_data *data, t_ray *ray)
{
	if (data->map->dir == 'E')
	{
		data->player.start_direction = 0;
		ray->camera.dir.x = 1;
		ray->camera.dir.y = 0;
		ray->camera.plane.x = 0;
		ray->camera.plane.y = (double)data->player.fov / 100;
	}
	if (data->map->dir == 'W')
	{
		data->player.start_direction = 2;
		ray->camera.dir.x = -1;
		ray->camera.dir.y = 0;
		ray->camera.plane.x = 0;
		ray->camera.plane.y = -(double)data->player.fov / 100;
	}
}

void	init_direction(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray_data;
	if (data->map->dir == 'N')
	{
		data->player.start_direction = 3;
		ray->camera.dir.x = 0;
		ray->camera.dir.y = -1;
		ray->camera.plane.x = (double)data->player.fov / 100;
		ray->camera.plane.y = 0;
	}
	if (data->map->dir == 'S')
	{
		data->player.start_direction = 1;
		ray->camera.dir.x = 0;
		ray->camera.dir.y = 1;
		ray->camera.plane.x = -(double)data->player.fov / 100;
		ray->camera.plane.y = 0;
	}
	init_direction_child(data, ray);
}
