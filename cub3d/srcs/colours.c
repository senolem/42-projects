/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:54:00 by faventur          #+#    #+#             */
/*   Updated: 2022/09/21 13:37:41 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "forms_and_colours.h"

/*
** The new_color() function returns a new color, each value going from 0 to
** 255.
** 
** The turn_pixel_to_color() function turns the four first chars of the
** <pixel> string into the <color> structure. Pixels are defined as follows:
** the first char is blue, the second one is green, the third one is red and
** the fourth one represents the alpha or transparency. This order depends
** on the system, and it is defined by the endian.
** 
** The turn_img_to_color() function turns all the pixels of  the <image>
** structure into the <color> structure. The loops repeat for each pixel
** of the image as it was a 2D table, and it is applied the formula to
** separate the colors into the struct.
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

void	turn_pixel_to_color(char *pixel, t_color color)
{
	pixel[0] = color.b;
	pixel[1] = color.g;
	pixel[2] = color.r;
	pixel[3] = color.a;
}
/*
void	turn_img_to_color(t_image *image, t_color color)
{
	int	x;
	int	y;

	y = 0;
	while (y < image->size.y)
	{
		x = 0;
		while (x < image->size.x)
		{
			turn_pixel_to_color(
				&image->pixels[x * 4 + image->line_size * y],
				color);
			x++;
		}
		y++;
	}
}
*/