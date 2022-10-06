/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:31 by faventur          #+#    #+#             */
/*   Updated: 2022/10/06 14:26:26 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include <stdio.h>

void	mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height,
			uint32_t color)
{
	uint32_t	h;
	uint32_t	w;

	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			mlx_put_pixel(img, w, h, color);
		}
	}
}

static void	draw_line_pt2(mlx_image_t *img, t_vector2 start, t_vector2 finish,
		uint32_t color)
{
	float	w;
	float	p;
	int		y;
	float	x;

	if (start.y > finish.y)
		ft_vec2_swap(&start, &finish);
	w = (finish.x - start.x) / (finish.y - start.y);
	p = start.x - w * start.y;
	y = (int)start.y;
	while (y < (int)finish.y)
	{
		x = w * (float)y + p;
		printf("%f %d\n", x, y);
		mlx_put_pixel(img, (int)x, y, color);
		y++;
	}
}

void	draw_line(mlx_image_t *img, t_vector2 start, t_vector2 finish,
		uint32_t color)
{
	float	m;
	float	b;
	int		x;
	float	y;

	if (finish.x != start.x)
		m = (finish.y - start.y) / (finish.x - start.x);
	if (finish.x != start.x && fabsf(m) <= 1)
	{
		if (start.x > finish.x)
			ft_vec2_swap(&start, &finish);
		b = start.y - m * start.x;
		x = (int)start.x;
		while (x < (int)finish.x)
		{
			y = m * (float)x + b;
			mlx_put_pixel(img, x, (int)y, color);
			x++;
		}
	}
	else
		draw_line_pt2(img, start, finish, color);
}

void	draw_vertical_line(mlx_image_t *img, t_vector draw_start,
			int draw_end, uint32_t color)
{
	while (draw_start.y < draw_end)
	{
		mlx_put_pixel(img, draw_start.x, draw_start.y, color);
		draw_start.x++;
	}
}
