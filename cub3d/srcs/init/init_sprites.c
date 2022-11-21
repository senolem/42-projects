/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:34:31 by faventur          #+#    #+#             */
/*   Updated: 2022/11/15 16:28:39 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_enemy(t_data *data)
{
	t_vec	tmp;

	srand(time(NULL));
	data->enemy.disable_ai = 0;
	data->enemy.alive = 1;
	pathfinding_dist_check(data, MINDISTANCE);
	pathfinding_list_pos(data);
	data->enemy.pos = pathfinding_pos_dist(data, (t_vec2){0, 0},
			data->ray_data.camera.pos, MINDISTANCE);
	if (data->enemy.pos.x == -1 && data->enemy.pos.y == -1)
	{
		tmp = pathfinding_get_pos(data);
		data->enemy.pos = (t_vec2){tmp.x + 0.5, tmp.y + 0.5};
		data->enemy.disable_ai = 1;
	}
	data->enemy.kill_countdown = KILLCOUNTDOWN;
	data->enemy.move_countdown = MOVECOUNTDOWN;
	if (data->enemy.disable_ai == 1)
		printf("Map too small ! Disabling AI...\n");
}

void	init_sprites_pos(t_data *data, t_ray *ray)
{
	size_t		i;
	t_s_caster	*sprite;

	i = 0;
	sprite = &data->ray_data.sprite;
	while (i < 3)
	{
		sprite->order[i] = i;
		sprite->sprite_dist[i] = ((ray->camera.pos.x - sprite->sprites[i].x)
				* (ray->camera.pos.x - sprite->sprites[i].x)
				+ (ray->camera.pos.y - sprite->sprites[i].y)
				* (ray->camera.pos.y - sprite->sprites[i].y));
		i++;
	}
	sort_sprites(sprite->order, sprite->sprite_dist, 3);
}

void	init_sprites(t_data *data, t_ray *ray)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	sprite->sprites = malloc(sizeof(t_sprite) * 3);
	sprite->order = malloc(sizeof(int) * 3);
	sprite->sprite_dist = malloc(sizeof(double) * 3);
	sprite->z_buffer = malloc(sizeof(double) * ray->resolution.x);
	if (!sprite->sprites || !sprite->z_buffer || !sprite->order
		|| !sprite->sprite_dist)
		free_exit(data);
	sprite->sprites[0].x = data->enemy.pos.x;
	sprite->sprites[0].y = data->enemy.pos.y;
	sprite->sprites[0].texture = 6;
	sprite->sprites[1].x = -1;
	sprite->sprites[1].y = -1;
	sprite->sprites[1].texture = 7;
	sprite->sprites[2].x = -1;
	sprite->sprites[2].y = -1;
	sprite->sprites[2].texture = 8;
	init_sprites_pos(data, ray);
}
