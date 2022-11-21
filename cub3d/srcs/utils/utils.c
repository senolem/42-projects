/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:46:30 by faventur          #+#    #+#             */
/*   Updated: 2022/11/16 13:05:14 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_vec	ft_get_x_and_y(char **map, char prop)
{
	t_vec	coord;

	coord.x = 0;
	coord.y = 0;
	while (map[coord.y])
	{
		while (map[coord.y][coord.x])
		{
			if (map[coord.y][coord.x] == prop)
				return (coord);
			coord.x++;
		}
		coord.x = 0;
		coord.y++;
	}
	coord.x = 3000;
	coord.y = 3000;
	return (coord);
}

void	ft_uchar_arr_display(unsigned char *arr, size_t size)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < size)
	{
		ft_printf("%d\n", arr[i]);
		i++;
	}
}

void	ft_print_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	int		i;
	int		tmp;
	double	tmp_dist;

	i = 0;
	tmp = 0;
	tmp_dist = 0;
	while (i < amount - 1)
	{
		if (dist[i] < dist[i + 1])
		{
			tmp_dist = dist[i];
			tmp = order[i];
			dist[i] = dist[i + 1];
			order[i] = order[i + 1];
			dist[i + 1] = tmp_dist;
			order[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

double	check_double_overflow(double value)
{
	if (value > 1)
		return (1);
	else if (value < -1)
		return (-1);
	return (value);
}
