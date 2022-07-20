/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 04:07:08 by albaur            #+#    #+#             */
/*   Updated: 2022/04/25 17:02:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	window_init(t_data *data)
{
	int	x;
	int	y;

	x = data->map.columns;
	y = data->map.rows;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, T_S * x, T_S * y,
			"so_long : A Crash Test");
}

void	img_init(t_data *data)
{
	t_tiles		*tiles;
	t_player	*player;

	tiles = &data->tiles;
	player = &data->player;
	img_to_sprite(data, &player->u_move, "move_up", 4);
	img_to_sprite(data, &player->d_move, "move_down", 4);
	img_to_sprite(data, &player->l_move, "move_left", 4);
	img_to_sprite(data, &player->r_move, "move_right", 4);
	img_to_sprite(data, &player->u_idle, "idle_up", 1);
	img_to_sprite(data, &player->d_idle, "idle_down", 1);
	img_to_sprite(data, &player->l_idle, "idle_left", 1);
	img_to_sprite(data, &player->r_idle, "idle_right", 1);
	img_to_sprite(data, &data->storage.sprite, "key", 9);
	img_to_sprite(data, &data->hud.num, "num", 10);
	img_to_sprite(data, &data->hud.health, "health", 3);
	tiles->wall = xpm_to_img(data, "wall.xpm");
	tiles->floor = xpm_to_img(data, "floor.xpm");
	tiles->exit = xpm_to_img(data, "exit_closed.xpm");
	tiles->open_exit = xpm_to_img(data, "exit_opened.xpm");
	data->enemy.img = xpm_to_img(data, "enemy.xpm");
	data->player.sprite = data->player.d_idle;
	data->player.idle = data->player.d_idle;
	data->hud.num->head = data->hud.num;
	data->hud.health->head = data->hud.health;
}

void	game_init(t_data *data)
{
	data->is_moving = 0;
	data->offset = 0;
	data->storage.storage = NULL;
	data->steps = 0;
	data->player.health = 3;
	ft_printf("ʕʘ̅͜ʘ̅ʔ Game starting !\n");
	ft_printf("Initializing window...   ");
	window_init(data);
	ft_printf("Done.\n");
	ft_printf("Initializing images...   ");
	img_init(data);
	ft_printf("Done.\n");
	ft_printf("Rendering tiles...	");
	render_tiles(data);
	ft_printf("Done.\n");
	ft_printf("Rendering sprites...   ");
	render_sprites(data);
	render_exit(data);
	render_enemies(data);
	render_hud(data);
	ft_printf("Done.\n");
}

void	render_init(t_data *data)
{
	render_tiles(data);
	render_item_animate(data);
	render_exit(data);
	render_enemies(data);
	render_hud(data);
	data->player.sprite = data->player.idle;
	put_mlx(data, data->player.sprite->img, data->player.x, data->player.y);
	data->is_moving = 0;
}
