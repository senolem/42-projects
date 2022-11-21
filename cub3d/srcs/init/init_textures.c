/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:19:27 by faventur          #+#    #+#             */
/*   Updated: 2022/11/16 17:32:04 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	check_texture_integrity(t_data *data, t_image *texture)
{
	if (!texture[0].texture || !texture[1].texture || !texture[2].texture
		|| !texture[3].texture || (data->map->mode == 1
			&& (!texture[4].texture || !texture[5].texture))
		|| !texture[15].texture || !texture[16].texture)
		return (1);
	else
		return (0);
}

static int	check_image_integrity(t_data *data, t_image *texture)
{
	if (!texture[0].img || !texture[1].img || !texture[2].img
		|| !texture[3].img || (data->map->mode == 1
			&& (!texture[4].img || !texture[5].img)) || !texture[15].img
		|| !texture[16].texture)
		return (1);
	else
		return (0);
}

void	tex_to_img(t_data *data, t_image *texture, size_t i)
{
	texture[i].img = mlx_texture_to_image(data->mlx,
			&texture[i].texture->texture);
}

static void	from_texture_to_image(t_data *data, t_image *texture)
{
	t_ray	*ray;
	size_t	i;

	ray = &data->ray_data;
	i = -1;
	tex_to_img(data, texture, 0);
	tex_to_img(data, texture, 1);
	tex_to_img(data, texture, 2);
	tex_to_img(data, texture, 3);
	if (data->map->mode == 1)
	{
		tex_to_img(data, texture, 4);
		tex_to_img(data, texture, 5);
	}
	if (check_image_integrity(data, texture))
		return ;
	while (++i < 6)
	{
		if ((i == 4 || i == 5) && data->map->mode != 1)
			continue ;
		ray->tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
	}
	init_enemy_texture(data, texture);
	init_door_texture(data, texture);
}

void	*init_textures(t_data *data)
{
	t_image	*texture;

	data->textures = malloc(sizeof(t_image) * 17);
	texture = data->textures;
	data->ray_data.tex_buf = malloc(sizeof(uint32_t *) * 17);
	if (!data->textures || !data->ray_data.tex_buf)
		free_exit(data);
	ft_bzero(texture, sizeof(*texture));
	texture[0].texture = mlx_load_xpm42(data->map->north_texture);
	texture[1].texture = mlx_load_xpm42(data->map->south_texture);
	texture[2].texture = mlx_load_xpm42(data->map->east_texture);
	texture[3].texture = mlx_load_xpm42(data->map->west_texture);
	if (data->map->mode == 1)
	{
		texture[4].texture = mlx_load_xpm42(data->map->ceiling_texture);
		texture[5].texture = mlx_load_xpm42(data->map->floor_texture);
	}
	init_quest_walls(data, texture);
	if (check_texture_integrity(data, texture))
		free_exit(data);
	from_texture_to_image(data, texture);
	if (check_image_integrity(data, texture))
		free_exit(data);
	return (texture);
}
