/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:43:20 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 13:41:46 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	get_color_ret(char **colors, int ret)
{
	ft_arr_freer(colors);
	return (ret);
}

static t_color	get_color_rgb(char **colors)
{
	t_color	rgba;

	rgba.r = ft_atoi(colors[0]);
	rgba.g = ft_atoi(colors[1]);
	rgba.b = ft_atoi(colors[2]);
	rgba.a = 255;
	return (rgba);
}

static int	get_color_invalid(t_color rgba)
{
	if (rgba.r < 0 || rgba.r > 255 || rgba.g < 0 || rgba.g > 255
		|| rgba.b < 0 || rgba.b > 255)
		return (1);
	else
		return (0);
}

static void	get_color_mode(int mode, t_map *mapStruct, t_color rgba)
{
	if (mode == 0)
				mapStruct->floor_color = rgba;
	else if (mode == 1)
				mapStruct->ceiling_color = rgba;
}

int	get_color(char *str, t_map *mapStruct, int mode)
{
	t_getcolor	c;

	c.i = 2;
	c.j = -1;
	while (str[c.i])
	{
		if (str[c.i] == ' ')
			++c.i;
		else if (ft_isascii(str[c.i]) == 1)
		{
			c.colors = ft_split(str + c.i, ',');
			if (ft_arrlen(c.colors) != 3)
				return (get_color_ret(c.colors, -1));
			if (get_color_check(c.colors, c.j))
				return (get_color_ret(c.colors, -1));
			c.rgba = get_color_rgb(c.colors);
			if (get_color_invalid(c.rgba))
				return (get_color_ret(c.colors, -1));
			get_color_mode(mode, mapStruct, c.rgba);
			return (get_color_ret(c.colors, 0));
		}
		else
			return (-1);
	}
	return (-1);
}
