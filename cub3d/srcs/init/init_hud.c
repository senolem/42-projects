/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:10:29 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 17:26:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	init_hud_draw2(t_data *data)
{
	data->hud.sprites[0].img->enabled = 1;
	data->enemy.warning_text = malloc(sizeof(t_image));
	if (!data->enemy.warning_text)
		free_exit(data);
	data->enemy.warning_text->texture = mlx_load_xpm42("images/run.xpm42");
	if (!data->enemy.warning_text->texture)
		free_exit(data);
	data->enemy.warning_text->img = mlx_texture_to_image(data->mlx,
			&data->enemy.warning_text->texture->texture);
	mlx_image_to_window(data->mlx, data->enemy.warning_text->img,
		WIDTH / 2 - 100, HEIGHT / 2 - 200);
	mlx_image_to_window(data->mlx, data->quest.pickup->img,
		WIDTH / 2 - 100, HEIGHT / 2 + 100);
	mlx_image_to_window(data->mlx, data->quest.exit_key->img,
		WIDTH / 2 - 100, HEIGHT / 2 + 100);
	mlx_image_to_window(data->mlx, data->quest.exit_win->img,
		0, 0);
	data->enemy.warning_text->img->enabled = 0;
	if (!data->enemy.warning_text->img)
		free_exit(data);
	mlx_image_to_window(data->mlx, data->map->minimap->img, 0, 0);
}

void	init_hud_draw(t_data *data)
{
	ssize_t	i;

	i = -1;
	while (++i < 20)
	{
		data->hud.sprites[i].img = mlx_texture_to_image(data->mlx,
				&data->hud.sprites[i].texture->texture);
		if (!data->hud.sprites[i].img)
		{
			free_data(data);
			throw_err_ex("Malloc error");
		}
		data->hud.sprites[i].img->enabled = 0;
	}
	i = -1;
	while (++i < 20)
	{
		mlx_image_to_window(data->mlx, data->hud.sprites[i].img, 0, 0);
		data->hud.sprites[i].img->enabled = 0;
	}
	init_hud_draw2(data);
}

static void	init_hud_var(t_data *data, char *base, ssize_t *i)
{
	ft_strcpy(base, "images/hands/hands_");
	*i = -1;
	data->hud.pos = 0;
	data->hud.sprites = malloc(sizeof(t_image) * 20);
	if (!data->hud.sprites)
		free_exit(data);
}

void	init_hud(t_data *data)
{
	ssize_t	i;
	char	base[20];
	char	*str;
	char	*itoa;

	init_hud_var(data, base, &i);
	while (++i < 20)
	{
		if (i < 9)
			str = ft_strjoin(base, "0");
		else
			str = ft_strdup("images/hands/hands_");
		itoa = ft_itoa(i + 1);
		str = ft_concat(str, itoa);
		str = ft_concat(str, ".xpm42");
		data->hud.sprites[i].texture = mlx_load_xpm42(str);
		if (!data->hud.sprites[i].texture)
		{
			free_data(data);
			throw_err_ex("Malloc error");
		}
		free(str);
		free(itoa);
	}
}
