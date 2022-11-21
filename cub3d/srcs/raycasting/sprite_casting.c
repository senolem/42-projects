/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:25:41 by faventur          #+#    #+#             */
/*   Updated: 2022/11/10 12:25:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	line_drawer_looper(t_data *data, t_ray *ray, t_var *v, int i)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	v->y = sprite->draw_start.y;
	while (v->y < sprite->draw_end.y)
	{
		sprite->d = (v->y) * 256 - HEIGHT * 128 + sprite->sprite_height
			* 128;
		sprite->tex.y = ((sprite->d * v->height)
				/ sprite->sprite_height) / 256;
		v->color = ray->tex_buf[sprite->sprites
		[sprite->order[i]].texture]
		[v->width * sprite->tex.y + sprite->tex.x];
		if ((v->color & 0xFFFFFFFF) != 0)
			mlx_put_pixel(data->screen.display.img, sprite->stripe,
				v->y, v->color);
		v->y++;
	}
}

void	line_drawer(t_data *data, t_ray *ray, t_var *v, int i)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	sprite->stripe = sprite->draw_start.x;
	v->width = data->textures[sprite->sprites[sprite->order[i]].texture]
		.img->height;
	v->height = data->textures[sprite->sprites[sprite->order[i]].texture]
		.img->width;
	while (sprite->stripe < sprite->draw_end.x)
	{
		sprite->tex.x = (int)(256 * (sprite->stripe - (-sprite->sprite_width / 2
						+ sprite->sprite_screen_x)) * v->width
				/ sprite->sprite_width) / 256;
		if (sprite->transform.y > 0 && sprite->stripe > 0
			&& sprite->stripe < WIDTH
			&& sprite->transform.y < sprite->z_buffer[sprite->stripe])
			line_drawer_looper(data, ray, v, i);
		sprite->stripe++;
	}
}

void	points_lines_designer(t_ray *ray)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->sprite_height / 2 + HEIGHT / 2;
	if (sprite->draw_end.y >= HEIGHT)
		sprite->draw_end.y = HEIGHT - 1;
	sprite->sprite_width = abs((int)(HEIGHT / (sprite->transform.y)));
	sprite->draw_start.x = -sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end.x >= WIDTH)
		sprite->draw_end.x = WIDTH - 1;
}

void	doing_some_math(t_ray *ray, int i)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	sprite->sprite.x = sprite->sprites[sprite->order[i]].x - ray->camera.pos.x;
	sprite->sprite.y = sprite->sprites[sprite->order[i]].y - ray->camera.pos.y;
	sprite->inv_det = 1.0 / (ray->camera.plane.x * ray->camera.dir.y
			- ray->camera.dir.x * ray->camera.plane.y);
	sprite->transform.x = sprite->inv_det * (ray->camera.dir.y
			* sprite->sprite.x - ray->camera.dir.x * sprite->sprite.y);
	sprite->transform.y = sprite->inv_det * (-ray->camera.plane.y
			* sprite->sprite.x + ray->camera.plane.x * sprite->sprite.y);
	sprite->sprite_screen_x = (int)((WIDTH / 2) * (1 + sprite->transform.x
				/ sprite->transform.y));
	sprite->sprite_height = abs((int)(HEIGHT / (sprite->transform.y)));
	sprite->draw_start.y = -sprite->sprite_height / 2 + HEIGHT / 2;
}

void	sprite_caster(t_data *data, t_ray *ray, t_var *v)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		doing_some_math(ray, i);
		points_lines_designer(ray);
		line_drawer(data, ray, v, i);
		i++;
	}
}
