/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:36:16 by albaur            #+#    #+#             */
/*   Updated: 2022/11/15 16:27:32 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	free_doors_map(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < (size_t)data->map->size.y)
		free(data->ray_data.door.door_map[i]);
	free(data->ray_data.door.door_map);
}

void	free_exit(t_data *data)
{
	free_data(data);
	throw_err_ex("Malloc error");
}

void	close_hook(void *ptr)
{
	t_data	*data;

	data = ptr;
	mlx_close_window(data->mlx);
}

void	free_data(t_data *data)
{
	mlx_terminate(data->mlx);
	free_audio(data);
	free_textures(data);
	free_doors_map(data);
	free(data->map->minimap);
	free(data->ray_data.sprite.sprites);
	free(data->ray_data.sprite.order);
	free(data->ray_data.sprite.sprite_dist);
	free(data->ray_data.sprite.z_buffer);
	free(data->map->size_arr);
	free(data->map->map_str);
	free(data->enemy.valid_pos);
	if (data->map->mode == 1)
	{
		free(data->map->floor_texture);
		free(data->map->ceiling_texture);
	}
	free(data->map->north_texture);
	free(data->map->south_texture);
	free(data->map->east_texture);
	free(data->map->west_texture);
	ft_arr_freer(data->map->map);
	free(data->map);
}
