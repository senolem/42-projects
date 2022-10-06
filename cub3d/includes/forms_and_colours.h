/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms_and_colours.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:58:12 by faventur          #+#    #+#             */
/*   Updated: 2022/10/06 17:48:24 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMS_AND_COLOURS_H
# define FORMS_AND_COLOURS_H

# include "mlx_utils.h"

t_color	new_color(int r, int g, int b, int a);
t_color	hex_to_rgb_converter(int hex_value);
t_color	lerp(t_color a, t_color b, float t);
int		rgb_to_hex_converter(t_color rgb);
int		add_shade(double distance, int color);
int		get_opposite(int color);
void	turn_pixel_to_color(char *pixel, t_color color);
void	turn_img_to_color(t_image *image, t_color color);

#endif