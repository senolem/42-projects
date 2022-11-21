/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_casting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:13:13 by faventur          #+#    #+#             */
/*   Updated: 2022/11/10 12:26:43 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	floor_casting_calculator(t_data *data, t_ray *ray, t_var *var)
{
	ray->fl.cell.x = (int)(ray->fl.floor.x);
	ray->fl.cell.y = (int)(ray->fl.floor.y);
	ray->fl.t.x = (int)(var->width * (ray->fl.floor.x - ray->fl.cell.x))
		& (var->width - 1);
	ray->fl.t.y = (int)(var->height * (ray->fl.floor.y - ray->fl.cell.y))
		& (var->height - 1);
	ray->fl.floor.x += ray->fl.floor_step.x;
	ray->fl.floor.y += ray->fl.floor_step.y;
	ray->fl.floor_tex = 5;
	ray->fl.ceiling_tex = 4;
	var->width = data->textures[4].img->width;
	var->height = data->textures[4].img->height;
	var->color = ray->tex_buf[ray->fl.floor_tex][var->width * ray->fl.t.y
		+ ray->fl.t.x];
	var->color = get_shading(data, var->color, ray->fl.row_distance);
	mlx_put_pixel(data->screen.display.img, var->x, var->y, var->color);
	var->width = data->textures[5].img->width;
	var->height = data->textures[5].img->height;
	var->color = ray->tex_buf[ray->fl.ceiling_tex][var->width * ray->fl.t.y
		+ ray->fl.t.x];
	var->color = get_shading(data, var->color, ray->fl.row_distance);
	mlx_put_pixel(data->screen.display.img, var->x, ray->resolution.y
		- var->y - 1, var->color);
	++var->x;
}

void	floor_casting_init(t_ray *ray, t_var *var)
{
	ray->fl.ray_dir0.x = ray->camera.dir.x - ray->camera.plane.x;
	ray->fl.ray_dir0.y = ray->camera.dir.y - ray->camera.plane.y;
	ray->fl.ray_dir1.x = ray->camera.dir.x + ray->camera.plane.x;
	ray->fl.ray_dir1.y = ray->camera.dir.y + ray->camera.plane.y;
	ray->fl.p = var->y - ray->resolution.y / 2;
	if (ray->fl.p == 0)
		ray->fl.p = 1;
	ray->fl.pos_z = 0.5 * ray->resolution.y;
	ray->fl.row_distance = ray->fl.pos_z / ray->fl.p;
	ray->fl.floor_step.x = ray->fl.row_distance
		* (ray->fl.ray_dir1.x - ray->fl.ray_dir0.x) / ray->resolution.x;
	ray->fl.floor_step.y = ray->fl.row_distance
		* (ray->fl.ray_dir1.y - ray->fl.ray_dir0.y) / ray->resolution.x;
	ray->fl.floor.x = ray->camera.pos.x + ray->fl.row_distance
		* ray->fl.ray_dir0.x;
	ray->fl.floor.y = ray->camera.pos.y + ray->fl.row_distance
		* ray->fl.ray_dir0.y;
}

void	floor_casting(t_data *data, t_ray *ray)
{
	t_var	var;

	ft_bzero(&var, sizeof(var));
	while (var.y < ray->resolution.y)
	{
		floor_casting_init(ray, &var);
		var.x = 0;
		while (var.x < ray->resolution.x)
			floor_casting_calculator(data, ray, &var);
		var.y++;
	}
}
