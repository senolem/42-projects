/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:13:29 by faventur          #+#    #+#             */
/*   Updated: 2022/10/06 11:34:12 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_new_window() function returns a <window> structure containing all the
** coordinates of the new window created.
*/

#include "mlx_utils.h"

int	ft_close(void)
{
	exit(0);
}

void	fill_window(t_program *data, uint32_t color)
{
	mlx_image_t	*frame;

	frame = data->img.img;
	mlx_draw_square(frame, frame->width, frame->height, color);
}