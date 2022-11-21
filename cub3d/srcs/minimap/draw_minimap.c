/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:07:41 by faventur          #+#    #+#             */
/*   Updated: 2022/11/16 17:51:54 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	minimap_get(t_map *map, int x, int y)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (i < y && i < map->buf_size)
	{
		pos += map->size_arr[i];
		i++;
	}
	pos += x;
	if (x < 0 || y < 0 || (y < map->buf_size && x >= map->size_arr[y])
		|| y >= map->size.y)
		return (0);
	if (map->map_str[pos] == '1' || map->map_str[pos] == '8'
		|| map->map_str[pos] == '9')
		return (1);
	else
		return (0);
}

void	draw_tiles(t_vec2 pos, t_vec vec, t_shape rect, t_data *data)
{
	if (minimap_get(data->map, vec.x + (int)(pos.x), vec.y + (int)(pos.y)))
		draw_rect(data->map->minimap->img, rect, 0xB8922CFF);
}

void	draw_position(t_data *data)
{
	t_shape	rec;
	float	f;

	f = 0;
	rec.height = 2;
	rec.width = 2;
	while (f < 1)
	{
		f += 0.1f;
		rec.x = 105 + (cos(data->player.yaw) * f) * 10;
		rec.y = 77 + (sin(data->player.yaw) * f) * 10;
		draw_rect(data->map->minimap->img, rec, 0xD7FFFFFF);
	}
	rec.x = 104;
	rec.y = 77;
	draw_rect(data->map->minimap->img, rec, 0xFF0000FF);
}

void	draw_minimap(t_data	*data)
{
	t_vec		vec;
	t_shape		rect;
	t_minimap	*map;

	map = data->map->minimap;
	mlx_draw_square(map->img, 210, 150, 0x00000000);
	map->pos.x -= (map->pos.x - data->ray_data.camera.pos.x) * 0.17;
	map->pos.y -= (map->pos.y - data->ray_data.camera.pos.y) * 0.17;
	rect.width = 12;
	rect.height = 12;
	rect.x = -fabs(fmod(map->pos.x, 1)) * rect.width;
	vec.x = -8;
	while (vec.x <= 8)
	{
		vec.y = -7;
		rect.y = -fabs(fmod(map->pos.y, 1)) * rect.height;
		while (++vec.y <= 7)
		{
			draw_tiles(map->pos, vec, rect, data);
			rect.y += rect.height + 1;
		}
		rect.x += rect.width + 1;
		++vec.x;
	}
	draw_position(data);
}
