/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:08:24 by faventur          #+#    #+#             */
/*   Updated: 2022/11/16 15:38:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	wall_distance_calculator(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_distance = (ray->map_pos.x - ray->camera.pos.x
				+ ray->wall_x_offset + (1 - ray->step_coord.x) / 2)
			/ ray->ray_dir.x;
	else
		ray->wall_distance = (ray->map_pos.y - ray->camera.pos.y
				+ ray->wall_y_offset + (1 - ray->step_coord.y) / 2)
			/ ray->ray_dir.y;
}

void	ft_check_walls(t_ray *ray)
{
	ray->ray_tex = ray->map->map[ray->map_pos.y][ray->map_pos.x] - '0';
	if (ray->ray_tex != 0)
	{
		if (ray->ray_tex == 1 || ray->ray_tex == 8 || ray->ray_tex == 9)
		{
			ray->hit = 1;
			ray->wall_x_offset = 0;
		}
		else if (ray->ray_tex >= 2 && ray->ray_tex <= 7)
		{
			ray->hit = 1;
			if (ray->side == 1)
				door_complement(ray);
			else
				door_complement_pt2(ray);
			check_door(ray);
		}
		else
			ray->ray_tex = 0;
	}
}

void	ray_launcher(t_ray *ray)
{
	ray->hit = 0;
	ray->wall_x_offset = 0;
	ray->wall_y_offset = 0;
	while (ray->hit == 0)
	{
		if (ray->ray_side.x < ray->ray_side.y)
		{
			ray->ray_side.x += ray->ray_delta.x;
			ray->map_pos.x += ray->step_coord.x;
			ray->side = 0;
		}
		else
		{
			ray->ray_side.y += ray->ray_delta.y;
			ray->map_pos.y += ray->step_coord.y;
			ray->side = 1;
		}
		ft_check_walls(ray);
	}
}

void	rayside_calculator(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_coord.x = -1;
		ray->ray_side.x = (ray->camera.pos.x - ray->map_pos.x)
			* ray->ray_delta.x;
	}
	else
	{
		ray->step_coord.x = 1;
		ray->ray_side.x = (ray->map_pos.x + 1.0 - ray->camera.pos.x)
			* ray->ray_delta.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_coord.y = -1;
		ray->ray_side.y = (ray->camera.pos.y - ray->map_pos.y)
			* ray->ray_delta.y;
	}
	else
	{
		ray->step_coord.y = 1;
		ray->ray_side.y = (ray->map_pos.y + 1.0 - ray->camera.pos.y)
			* ray->ray_delta.y;
	}
}

void	ray_delta_calculator(t_ray *ray)
{
	if (ray->ray_dir.x == 0)
		ray->ray_delta.x = 1e30;
	else
		ray->ray_delta.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->ray_delta.y = 1e30;
	else
		ray->ray_delta.y = fabs(1 / ray->ray_dir.y);
}
