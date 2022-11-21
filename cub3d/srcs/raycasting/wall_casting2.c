/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:29:16 by faventur          #+#    #+#             */
/*   Updated: 2022/11/16 15:40:58 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	choose_wall_texture(t_ray *ray)
{
	if (ray->text_select != 0)
		return ;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		ray->text_select = 0;
	if (ray->side == 1 && ray->ray_dir.y > 0)
		ray->text_select = 1;
	if (ray->side == 0 && ray->ray_dir.x < 0)
		ray->text_select = 2;
	if (ray->side == 0 && ray->ray_dir.x > 0)
		ray->text_select = 3;
	if (ray->ray_tex >= 2 && ray->ray_tex <= 9)
		ray->text_select = ray->ray_tex + 7;
}

void	texture_y_pos_calculator(t_data *data, t_ray *ray)
{
	ray->step = 1.0 * data->textures[ray->text_select].img->height
		/ ray->line_height;
	ray->tex_pos = (ray->draw_start - ray->resolution.y / 2
			+ ray->line_height / 2) * ray->step;
}

void	texture_x_pos_calculator(t_data *data, t_ray *ray)
{
	size_t		img_width;
	t_door_data	**map;

	map = ray->door.door_map;
	img_width = data->textures[ray->text_select].img->width;
	if (ray->side == 0)
		ray->wall_x = ray->camera.pos.y + ray->wall_distance * ray->ray_dir.y;
	else
		ray->wall_x = ray->camera.pos.x + ray->wall_distance * ray->ray_dir.x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->ray_tex == 2)
		ray->wall_x += map[ray->map_pos.y][ray->map_pos.y].offset;
	ray->tex.x = (int)(ray->wall_x * (double)img_width);
}

void	wall_line_calculator(t_ray *ray)
{
	ray->line_height = (int)(ray->resolution.y / ray->wall_distance);
	ray->draw_start = -ray->line_height / 2 + ray->resolution.y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + ray->resolution.y / 2;
	if (ray->draw_end >= ray->resolution.y)
		ray->draw_end = ray->resolution.y - 1;
}
