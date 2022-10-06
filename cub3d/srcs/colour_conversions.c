/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:59:33 by faventur          #+#    #+#             */
/*   Updated: 2022/04/18 17:30:32 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "forms_and_colours.h"

int	rgb_to_hex_converter(t_color rgb)
{
	return (rgb.a << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b);
}

t_color	lerp(t_color a, t_color b, float t)
{
	a.r += (b.r - a.r) * t;
	a.g += (b.g - a.g) * t;
	a.b += (b.b - a.b) * t;
	a.a += (b.a - a.a) * t;
	return (a);
}

t_color	hex_to_rgb_converter(int hex_value)
{	
	t_color	rgb;

	rgb.a = ((hex_value >> 24) & 0xff);
	rgb.r = ((hex_value >> 16) & 0xff);
	rgb.g = ((hex_value >> 8) & 0xff);
	rgb.b = ((hex_value) & 0xff);
	return (rgb);
}

int	add_shade(double distance, int color)
{
	t_color	rgb;
	t_color	black;

	rgb = hex_to_rgb_converter(color);
	black = hex_to_rgb_converter(0xff000000);
	if (distance >= 0 && distance <= 1)
	{
		rgb = lerp(rgb, black, distance);
		color = rgb_to_hex_converter(rgb);
		return (color);
	}
	return (0x0);
}

int	get_opposite(int color)
{
	t_color	rgb;
	t_color	white;
	t_color	complem;

	rgb = hex_to_rgb_converter(color);
	white = hex_to_rgb_converter(0xffffffff);
	complem.r = white.r - rgb.r;
	complem.g = white.g - rgb.g;
	complem.b = white.b - rgb.b;
	complem.a = white.a - rgb.a;
	color = rgb_to_hex_converter(rgb);
	return (color);
}
