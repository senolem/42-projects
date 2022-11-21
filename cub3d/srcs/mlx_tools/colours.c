/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:54:00 by faventur          #+#    #+#             */
/*   Updated: 2022/10/27 15:33:16 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

/*
** Examples d'utilisation de mes fonctions lerp_double() et inv_lerp():
** t_color	a = {255, 0, 0, 255};
** t_color	b = {45, 45, 0, 255};
** double	rgb = lerp_double(rgb_to_hex(a), rgb_to_hex(b), 0.76);
** double	t = inv_lerp(rgb_to_hex(a), rgb_to_hex(b), rgb);
** printf("%f\n", t);
*/

t_color	new_color(int r, int g, int b, int a)
{
	t_color	color;

	color.r = (char)r;
	color.g = (char)g;
	color.b = (char)b;
	color.a = (char)a;
	return (color);
}

int	add_shade(double distance, int color)
{
	t_color	rgb;
	t_color	black;

	rgb = hex_to_rgb(color);
	black = hex_to_rgb(0xff000000);
	if (distance >= 0 && distance <= 1)
	{
		rgb = lerp(rgb, black, distance);
		color = rgb_to_hex(rgb);
		return (color);
	}
	return (0x0);
}

int	get_opposite(int color)
{
	t_color	rgb;

	rgb = hex_to_rgb(color);
	color = rgb_to_hex(rgb);
	return (color);
}

double	lerp_double(double a, double b, double t)
{
	a += t * (b - a);
	return (a);
}

double	inv_lerp(double a, double b, double value)
{
	double	t;

	t = (value - a) / (b - a);
	return (t);
}
