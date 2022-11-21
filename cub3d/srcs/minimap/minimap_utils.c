/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:44:45 by albaur            #+#    #+#             */
/*   Updated: 2022/11/15 16:28:47 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	get_size_arr(t_data *data, int y)
{
	int	i;

	data->map->size_arr = malloc(sizeof(int) * y);
	if (!data->map->size_arr)
		return ;
	i = 0;
	while (data->map->map[i])
	{
		data->map->size_arr[i] = ft_strlen(data->map->map[i]);
		++i;
	}
}

void	get_map_str(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (data->map->map[i])
	{
		j += ft_strlen(data->map->map[i]);
		++i;
	}
	data->map->map_str = malloc(sizeof(char) * j + 1);
	get_size_arr(data, i);
	if (!data->map->map_str)
		free_exit(data);
	i = -1;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
			data->map->map_str[k++] = data->map->map[i][j];
	}
	data->map->map_str[k] = 0;
}

void	get_map_size(t_data *data)
{
	size_t	i;

	i = 0;
	data->map->size.x = 0;
	while (data->map->map[i])
	{
		data->map->size.x = fmax(data->map->size.x,
				ft_strlen(data->map->map[i]));
		++i;
	}
	data->map->buf_size = i;
	data->map->size.y = i;
}

void	draw_rect(mlx_image_t *img, t_shape rect, int color)
{
	size_t	i;
	size_t	j;
	size_t	height;
	size_t	width;

	i = fmax(rect.x, 0);
	height = img->height;
	width = img->width;
	while ((int)i < rect.x + rect.width && i < width)
	{
		j = fmax(rect.y, 0);
		while ((int)j < rect.y + rect.height && j < height)
		{
			mlx_put_pixel(img, i, j, color);
			++j;
		}
		i++;
	}
}
