/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:32:32 by albaur            #+#    #+#             */
/*   Updated: 2022/11/17 17:29:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	init_struct2(t_data *data, t_ray *ray)
{
	data->render_delay = 1;
	data->screen.display.size.x = WIDTH;
	data->screen.display.size.y = HEIGHT;
	ray->resolution.x = data->screen.display.size.x;
	ray->resolution.y = data->screen.display.size.y;
	ray->half_width = ray->resolution.x / 2;
	data->player.fov = 70;
	init_direction(data);
	data->player.yaw = M_PI / 2 * data->player.start_direction;
	data->delay = 0;
	get_map_size(data);
	get_map_str(data);
	init_enemy(data);
	init_sprites(data, ray);
	data->enemy.lock = 0;
	data->enemy.kill_timer = 0.0;
	data->enemy.move_timer = 0.0;
	data->enemy.yoshie_timer = 0.0;
	data->enemy.selena_timer = 0.0;
	data->enemy.kill_countdown = KILLCOUNTDOWN;
	data->enemy.move_countdown = MOVECOUNTDOWN;
	data->player.footstep_timer = 0;
	data->player.footstep_lock = 0;
	init_doors(data);
}

void	init_struct(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray_data;
	ft_bzero(ray, sizeof(*ray));
	ray->camera.pos.x = 0.5 + data->map->spawn_pos.x;
	ray->camera.pos.y = 0.5 + data->map->spawn_pos.y;
	data->player.speed.movement = 0.08;
	data->player.speed.rotation = 0.3;
	ray->k.pcos = cos(data->player.speed.rotation);
	ray->k.psin = sin(data->player.speed.rotation);
	ray->k.ncos = cos(-data->player.speed.rotation);
	ray->k.nsin = sin(-data->player.speed.rotation);
	ray->m.pcos = cos(data->player.speed.rotation / 2);
	ray->m.psin = sin(data->player.speed.rotation / 2);
	ray->m.ncos = cos(-data->player.speed.rotation / 2);
	ray->m.nsin = sin(-data->player.speed.rotation / 2);
	data->shading.ratio = 0.7;
	data->shading.shading_lock = 0;
	data->shading.timer = 0.0;
	init_struct2(data, ray);
}
