/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/11/14 14:45:33 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ray_data_init(t_ray *ray, int x)
{
	ray->camera.camera_x = 2 * x / (double)ray->resolution.x - 1;
	ray->ray_dir.x = ray->camera.dir.x + ray->camera.plane.x
		* ray->camera.camera_x;
	ray->ray_dir.y = ray->camera.dir.y + ray->camera.plane.y
		* ray->camera.camera_x;
	ray->map_pos.x = (int)ray->camera.pos.x;
	ray->map_pos.y = (int)ray->camera.pos.y;
	ray->text_select = 0;
	ray_delta_calculator(ray);
}

void	ray_init(t_data *data, t_ray *ray, t_var var)
{
	ray_data_init(ray, var.x);
	rayside_calculator(ray);
	ray_launcher(ray);
	wall_distance_calculator(ray);
	wall_line_calculator(ray);
	texture_x_pos_calculator(data, ray);
	texture_y_pos_calculator(data, ray);
}

void	ray_casting(t_data *data)
{
	t_ray	*ray;
	t_var	var;

	ft_bzero(&var, sizeof(var));
	ray = &data->ray_data;
	ray->map = data->map;
	init_sprites_pos(data, ray);
	if (data->map->mode == 1)
		floor_casting(data, ray);
	while (var.x < ray->resolution.x)
	{
		ray_init(data, ray, var);
		if (data->map->mode == -1)
		{
			draw_ceiling(data, var.x);
			draw_floor(data, var.x);
		}
		draw_walls(data, var.x);
		ray->sprite.z_buffer[var.x] = ray->wall_distance;
		++var.x;
	}
	sprite_caster(data, ray, &var);
}
