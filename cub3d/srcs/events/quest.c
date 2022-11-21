/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quest.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:07:19 by albaur            #+#    #+#             */
/*   Updated: 2022/11/17 17:32:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	update_quest_hud_exit(t_data *data, t_vec pos)
{
	if (data->map->map[pos.y][pos.x] == '9' && data->quest.done != 3)
	{
		data->quest.exit_key->img->enabled = 1;
		if (data->key == MLX_KEY_E)
		{
			printf("You escaped in %fs\n", data->timer);
			data->map->minimap->img->enabled = 0;
			data->quest.exit_key->img->enabled = 0;
			mlx_image_to_window(data->mlx, data->quest.exit_bg->img, 0, 0);
			data->quest.exit_win->img->enabled = 1;
			data->quest.done = 3;
			data->enemy.alive = 0;
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
			data->ray_data.m.focus = 1;
			data->key = 0;
		}
	}
	else if (data->quest.done != 3)
		data->quest.exit_key->img->enabled = 0;
}

static void	update_quest_hud(t_data *data)
{
	t_vec	pos;

	pos.x = data->ray_data.camera.pos.x + data->ray_data.camera.dir.x;
	pos.y = data->ray_data.camera.pos.y + data->ray_data.camera.dir.y;
	if (data->map->map[pos.y][pos.x] == '8')
	{
		data->quest.pickup->img->enabled = 1;
		if (data->key == MLX_KEY_E)
		{
			if (data->quest.n_pickup == 0)
				data->quest.exit_pos = pos;
			ma_sound_start(&data->audio.pickup);
			data->map->map[pos.y][pos.x] = '1';
			++data->quest.n_pickup;
			printf("\rCollected pages: %zu/%zu",
				data->quest.n_pickup, data->quest.n_pages);
			fflush(stdout);
			if (data->quest.n_pages - data->quest.n_pickup == 0)
				ft_printf("\nA portal opened up somewhere.\n");
			data->key = 0;
		}
	}
	else
		data->quest.pickup->img->enabled = 0;
	update_quest_hud_exit(data, pos);
}

static void	update_quest_fade(t_data *data)
{
	if (data->timer >= data->shading.timer + 0.025
		&& data->shading.shading_lock == 0 && data->shading.ratio < 2.5)
	{
		data->shading.timer = data->timer;
		data->shading.shading_lock = 1;
		data->shading.ratio += 0.035;
	}
	else if (data->timer >= data->shading.timer + 0.025)
		data->shading.shading_lock = 0;
}

void	update_quest(t_data *data)
{
	update_quest_hud(data);
	if (data->quest.done < 2 && data->quest.n_pages != 0
		&& data->quest.n_pages == data->quest.n_pickup)
	{
		if (data->quest.done == 0)
		{
			data->map->map[data->quest.exit_pos.y]
			[data->quest.exit_pos.x] = '9';
			data->enemy.disable_ai = 1;
			data->ray_data.sprite.sprites[0].x = -1;
			data->ray_data.sprite.sprites[0].y = -1;
			ma_sound_stop(&data->audio.creeping_down);
			ma_sound_start(&data->audio.unraveled);
			data->quest.done = 1;
		}
		update_quest_fade(data);
		if (data->shading.ratio >= 2.5)
			data->quest.done = 2;
	}
}
