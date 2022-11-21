/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:59:33 by faventur          #+#    #+#             */
/*   Updated: 2022/10/27 15:30:52 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	rgb_to_hex(t_color rgb)
{
	return (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

t_color	lerp(t_color a, t_color b, double t)
{
	a.r += (b.r - a.r) * t;
	a.g += (b.g - a.g) * t;
	a.b += (b.b - a.b) * t;
	a.a += (b.a - a.a) * t;
	return (a);
}

t_color	hex_to_rgb(uint32_t hex_value)
{	
	t_color	rgb;

	rgb.r = ((hex_value >> 24) & 0xff);
	rgb.g = ((hex_value >> 16) & 0xff);
	rgb.b = ((hex_value >> 8) & 0xff);
	rgb.a = ((hex_value) & 0xff);
	return (rgb);
}

void	turn_pixel_to_color(char *pixel, t_color color)
{
	pixel[0] = color.b;
	pixel[1] = color.g;
	pixel[2] = color.r;
	pixel[3] = color.a;
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
