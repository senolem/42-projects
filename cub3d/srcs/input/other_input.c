/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:12:47 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 13:17:02 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	key_input_focus(t_data *data, t_ray *ray)
{
	if (data->key == (keys_t)MLX_KEY_F)
	{
		if (ray->m.focus == 0)
			ray->m.focus = 1;
		else
			ray->m.focus = 0;
		data->key = 0;
	}
	if (data->key == (keys_t)MLX_KEY_M)
	{
		if (data->audio.volume == 0.0)
		{
			data->audio.volume = 1.0;
			ma_engine_set_volume(data->audio.audio_engine, 1.0);
		}
		else
		{
			data->audio.volume = 0.0;
			ma_engine_set_volume(data->audio.audio_engine, 0.0);
		}
		data->key = 0;
	}
}

static void	key_input_arrows_pt2(t_data *data, t_ray *ray, t_var *var)
{
	if (data->key == (keys_t)MLX_KEY_D)
	{
		if (ray->camera.dir.y > 0)
			var->alpha = acos(check_double_overflow(ray->camera.dir.x));
		else
			var->alpha = -acos(check_double_overflow(ray->camera.dir.x));
		if (!check_collision(data, var, 6))
			ray->camera.pos.y = (var->slide * var->movement)
				+ ray->camera.pos.y;
		if (!check_collision(data, var, 7))
			ray->camera.pos.x += (var->slide * var->movement);
	}
	else
		key_input_focus(data, ray);
}

void	key_input_arrows(t_data *data, t_ray *ray, t_var *var)
{
	if (data->key == (keys_t)MLX_KEY_A)
	{
		if (ray->camera.dir.y > 0)
			var->alpha = acos(check_double_overflow(ray->camera.dir.x));
		else
			var->alpha = -acos(check_double_overflow(ray->camera.dir.x));
		if (!check_collision(data, var, 4))
			ray->camera.pos.y = (var->slide * var->movement)
				+ ray->camera.pos.y;
		if (!check_collision(data, var, 5))
			ray->camera.pos.x += (var->slide * var->movement);
	}
	else
		key_input_arrows_pt2(data, ray, var);
}
