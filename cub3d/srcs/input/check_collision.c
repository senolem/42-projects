/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:17:09 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 16:12:50 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	check_collision3(t_data *data, t_var *var, int mode, char *c)
{
	t_ray	*ray;

	ray = &data->ray_data;
	if (mode == 6)
	{
		var->slide = sin(var->alpha + M_PI / 2);
		*c = data->map->map[(int)((sin(var->alpha + M_PI / 2) * var->movement)
				+ ray->camera.pos.y)][(int)(ray->camera.pos.x)];
	}
	else if (mode == 7)
	{
		var->slide = cos(var->alpha + M_PI / 2);
		*c = data->map->map[(int)(ray->camera.pos.y)]
		[(int)((cos(var->alpha + M_PI / 2) * var->movement)
				+ ray->camera.pos.x)];
	}
}

static void	check_collision2(t_data *data, t_var *var, int mode, char *c)
{
	t_ray	*ray;

	ray = &data->ray_data;
	if (mode == 4)
	{
		var->slide = -sin(var->alpha + M_PI / 2);
		*c = data->map->map[(int)((-sin(var->alpha + M_PI / 2) * var->movement)
				+ ray->camera.pos.y)][(int)(ray->camera.pos.x)];
	}
	else if (mode == 5)
	{
		var->slide = -cos(var->alpha + M_PI / 2);
		*c = data->map->map[(int)(ray->camera.pos.y)]
		[(int)((-cos(var->alpha + M_PI / 2)
					* var->movement) + ray->camera.pos.x)];
	}
	else
		check_collision3(data, var, mode, c);
}

int	check_collision(t_data *data, t_var *var, int mode)
{
	t_ray	*ray;
	char	c;

	ray = &data->ray_data;
	if (mode == 0 || mode == 3)
		var->slide = ray->camera.dir.x * var->movement;
	if (mode == 1 || mode == 2)
		var->slide = ray->camera.dir.y * var->movement;
	if (mode == 0)
		c = data->map->map[(int)(ray->camera.pos.y)]
		[(int)(ray->camera.pos.x + var->slide)];
	else if (mode == 1)
		c = data->map->map[(int)(ray->camera.pos.y + var->slide)]
		[(int)(ray->camera.pos.x)];
	else if (mode == 2)
		c = data->map->map[(int)(ray->camera.pos.y - var->slide)]
		[(int)(ray->camera.pos.x)];
	else if (mode == 3)
		c = data->map->map[(int)(ray->camera.pos.y)]
		[(int)(ray->camera.pos.x - var->slide)];
	else
		check_collision2(data, var, mode, &c);
	if (c != '1' && c != '8' && c != '9')
		return (0);
	return (1);
}
