/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_complement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:11:36 by faventur          #+#    #+#             */
/*   Updated: 2022/11/14 17:18:53 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	check_door(t_ray *ray)
{
	if (ray->map->map[ray->map_pos.y][ray->map_pos.x] == '2')
	{
		if (ft_vect2_distance_calc(ray->camera.pos,
				(t_vec2){ray->map_pos.x, ray->map_pos.y}) <= 2.5)
			ray->door.door_map[ray->map_pos.y][ray->map_pos.x].sliding = 1;
	}
	else if (ray->map->map[ray->map_pos.y][ray->map_pos.x] == '7')
	{
		if (ft_vect2_distance_calc(ray->camera.pos,
				(t_vec2){ray->map_pos.x, ray->map_pos.y}) > 2.5)
		ray->door.door_map[ray->map_pos.y][ray->map_pos.x].sliding = 2;
	}
}

void	door_complement_pt2(t_ray *ray)
{
	ray->wall_x_offset = 0.5 * ray->step_coord.x;
	ray->wall_distance = (ray->map_pos.x - ray->camera.pos.x
			+ ray->wall_x_offset
			+ (1 - ray->step_coord.x) / 2) / ray->ray_dir.x;
	ray->wall_x = ray->camera.pos.y + ray->wall_distance * ray->ray_dir.y;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->ray_side.x - (ray->ray_delta.x / 2) < ray->ray_side.y)
	{
		if (1.0 - ray->wall_x <= ray->door.door_map[ray->map_pos.y]
			[ray->map_pos.x].offset)
		{
			ray->hit = 0;
			ray->wall_x_offset = 0;
		}
	}
	else
	{
		ray->map_pos.y += ray->step_coord.y;
		ray->side = 1;
		ray->ray_tex = 0;
		ray->wall_x_offset = 0;
	}
}

void	door_complement(t_ray *ray)
{
	ray->wall_y_offset = 0.5 * ray->step_coord.y;
	ray->wall_distance = (ray->map_pos.y - ray->camera.pos.y
			+ ray->wall_y_offset
			+ (1 - ray->step_coord.y) / 2) / ray->ray_dir.y;
	ray->wall_x = ray->camera.pos.x + ray->wall_distance * ray->ray_dir.x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->ray_side.y - (ray->ray_delta.y / 2) < ray->ray_side.x)
	{
		if (1.0 - ray->wall_x <= ray->door.door_map[ray->map_pos.y]
			[ray->map_pos.x].offset)
		{
			ray->hit = 0;
			ray->wall_y_offset = 0;
		}
	}
	else
	{
		ray->map_pos.x += ray->step_coord.x;
		ray->side = 0;
		ray->ray_tex = 0;
		ray->wall_y_offset = 0;
	}
}
