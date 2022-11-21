/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:13:29 by faventur          #+#    #+#             */
/*   Updated: 2022/10/31 17:11:48 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

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
			mlx_put_pixel(img, w, h, color);
	}
}

void	fill_window(t_data *data, uint32_t color)
{
	mlx_image_t	*frame;
	t_var		var;

	ft_bzero(&var, sizeof(var));
	frame = data->screen.display.img;
	var.width = data->screen.display.size.x;
	var.height = data->screen.display.size.y;
	mlx_draw_square(frame, var.width, var.height, color);
}
