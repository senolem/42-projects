/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_quest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:34:11 by albaur            #+#    #+#             */
/*   Updated: 2022/11/17 12:29:49 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_quest_walls(t_data *data, t_image *texture)
{
	texture[15].texture = mlx_load_xpm42("images/wall_page.xpm42");
	tex_to_img(data, texture, 15);
	texture[16].texture = mlx_load_xpm42("images/exit.xpm42");
	tex_to_img(data, texture, 16);
}

static void	init_quest_textures_load(t_data *data)
{
	t_shape	background;

	background.height = HEIGHT;
	background.width = WIDTH;
	background.x = 0;
	background.y = 0;
	data->quest.pickup->texture = mlx_load_xpm42("images/pickup.xpm42");
	data->quest.exit_key->texture = mlx_load_xpm42("images/exit_key.xpm42");
	data->quest.exit_win->texture = mlx_load_xpm42("images/exit_win.xpm42");
	draw_rect(data->quest.exit_bg->img, background, 0xFFFFFF47);
	data->quest.pickup->img = mlx_texture_to_image(data->mlx,
			&data->quest.pickup->texture->texture);
	data->quest.exit_key->img = mlx_texture_to_image(data->mlx,
			&data->quest.exit_key->texture->texture);
	data->quest.exit_win->img = mlx_texture_to_image(data->mlx,
			&data->quest.exit_win->texture->texture);
	if (!data->quest.pickup->texture || !data->quest.exit_key->texture
		|| !data->quest.exit_win->texture)
		free_exit(data);
}

static void	init_quest_textures(t_data *data)
{
	data->quest.pickup = malloc(sizeof(t_image));
	data->quest.exit_key = malloc(sizeof(t_image));
	data->quest.exit_win = malloc(sizeof(t_image));
	data->quest.exit_bg = malloc(sizeof(t_image));
	data->quest.exit_bg->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->quest.pickup || !data->quest.exit_key || !data->quest.exit_win
		|| !data->quest.exit_bg)
		free_exit(data);
	init_quest_textures_load(data);
}

void	init_quest(t_data *data)
{
	size_t	i;
	size_t	j;

	i = -1;
	data->quest.n_pages = 0;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
		{
			if (data->map->map[i][j] == '8')
				++data->quest.n_pages;
		}
	}
	init_quest_textures(data);
	data->quest.pickup->img->enabled = 0;
	data->quest.exit_key->img->enabled = 0;
	data->quest.exit_win->img->enabled = 0;
	data->quest.n_pickup = 0;
	data->quest.done = 0;
	if (data->quest.n_pages)
		ft_printf("Find %d pages to escape.\n", data->quest.n_pages);
	else
		ft_printf("No pages in the map. You can't escape.");
}
