/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:36:35 by faventur          #+#    #+#             */
/*   Updated: 2022/11/05 15:16:04 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

double	ft_vect2_distance_calc(t_vec2 start, t_vec2 finish)
{
	double	distance;

	distance = sqrtf(powf(start.x - finish.x, 2) + powf(start.y - finish.y, 2));
	return (distance);
}

t_vec	ft_inttovec(int x, int y)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vec2	ft_doubletovec2(double x, double y)
{
	t_vec2	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

void	ft_vec_swap(t_vec *start, t_vec *finish)
{
	t_vec	tmp;

	tmp.x = start->x;
	tmp.y = start->y;
	start->x = finish->x;
	start->y = finish->y;
	finish->x = tmp.x;
	finish->y = tmp.y;
}

void	ft_vec2_swap(t_vec2 *start, t_vec2 *finish)
{
	t_vec2	tmp;

	tmp.x = start->x;
	tmp.y = start->y;
	start->x = finish->x;
	start->y = finish->y;
	finish->x = tmp.x;
	finish->y = tmp.y;
}
