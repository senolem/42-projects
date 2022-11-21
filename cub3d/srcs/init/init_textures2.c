/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:42:39 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 16:10:58 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_enemy_texture(t_data *data, t_image *texture)
{
	size_t	i;

	i = 5;
	if (!data->ray_data.tex_buf)
		throw_err_ex("Malloc error");
	texture[6].texture = mlx_load_xpm42("images/smiler.xpm42");
	texture[7].texture = mlx_load_xpm42("images/selena.xpm42");
	if (rand() % 2)
		texture[8].texture = mlx_load_xpm42("images/yoshie.xpm42");
	else
		texture[8].texture = mlx_load_xpm42("images/jungler.xpm42");
	if (!texture[6].texture || !texture[7].texture || !texture[8].texture)
		throw_err_ex("Malloc error");
	while (++i < 9)
	{
		tex_to_img(data, texture, i);
		if (!texture[i].img)
			throw_err_ex("Malloc error");
		data->ray_data.tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
	}
}

void	init_door_image(t_data *data, t_image *texture)
{
	ssize_t	i;

	i = 8;
	while (++i < 17)
	{
		tex_to_img(data, texture, i);
		if (!texture[i].img)
			throw_err_ex("Malloc error2");
		data->ray_data.tex_buf[i] = uchar_to_arr(texture[i].img->pixels,
				texture[i].img->width, texture[i].img->height);
	}
}

void	init_door_texture(t_data *data, t_image *texture)
{
	ssize_t	i;
	char	base[20];
	char	*str;
	char	*itoa;

	i = -1;
	ft_strcpy(base, "images/fs/fire_door");
	while (++i < 6)
	{
		str = ft_strdup("images/fs/fire_door");
		itoa = ft_itoa(i + 1);
		str = ft_concat(str, itoa);
		str = ft_concat(str, ".xpm42");
		texture[i + 9].texture = mlx_load_xpm42(str);
		if (!texture[i + 9].texture)
			throw_err_ex("Malloc error");
		free(str);
		free(itoa);
	}
	init_door_image(data, texture);
}
