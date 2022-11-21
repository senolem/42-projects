/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:15:14 by albaur            #+#    #+#             */
/*   Updated: 2022/11/10 16:37:53 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	update_enemy_distant(t_data *data, t_vec2 start,
	t_s_caster	*sprite, t_vec2 *pos)
{
	size_t		i;
	t_ray		*ray;

	ray = &data->ray_data;
	sprite = &ray->sprite;
	data->enemy.warning_text->img->enabled = 0;
	data->audio.lock2 = 0;
	data->enemy.kill_countdown = KILLCOUNTDOWN;
	data->enemy.kill_timer = 0.0;
	if (data->timer >= data->enemy.move_timer + MOVECOUNTDOWN)
		data->enemy.move_countdown--;
	if (data->enemy.move_countdown <= 0)
	{
		i = rand() % 3;
		if (i < 2)
			ma_sound_start(&data->audio.smiler[i]);
		*pos = pathfinding_pos_dist(data, start, ray->camera.pos, MINDISTANCE);
		sprite->sprites[0].x = pos->x;
		sprite->sprites[0].y = pos->y;
		data->enemy.move_countdown = MOVECOUNTDOWN;
		data->enemy.move_timer = data->timer;
	}
}

void	update_enemy_close(t_data *data, double dist)
{
	if (data->enemy.kill_timer == 0.0)
		data->enemy.kill_timer = data->timer;
	if (data->audio.lock2 == 0)
		ma_sound_start(&data->audio.scare);
	data->audio.lock2 = 1;
	data->enemy.warning_text->img->enabled = 1;
	if (data->timer >= data->enemy.kill_timer + KILLCOUNTDOWN
		|| dist <= 1.5)
		data->enemy.kill_countdown = 0.0;
}

void	update_enemy(t_data *data, t_ray *ray)
{
	t_s_caster	*sprite;
	t_vec2		start;
	t_vec2		pos;
	double		dist;

	sprite = &ray->sprite;
	if (data->enemy.disable_ai == 1)
		return ;
	start = (t_vec2){sprite->sprites[0].x, sprite->sprites[0].y};
	dist = ft_vect2_distance_calc(start, data->ray_data.camera.pos);
	if (dist <= 8.0 && !ma_sound_is_playing(&data->audio.geiger))
		ma_sound_start(&data->audio.geiger);
	if (dist <= 5.0)
		update_enemy_close(data, dist);
	if (dist > 8.0 && ma_sound_is_playing(&data->audio.geiger))
		ma_sound_stop(&data->audio.geiger);
	else if (dist > 5.0)
		update_enemy_distant(data, start, sprite, &pos);
}
