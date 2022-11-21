/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:46:59 by albaur            #+#    #+#             */
/*   Updated: 2022/11/15 16:35:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static size_t	pathfinding_list_pos_get(t_data *data)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	k = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == '0')
				++k;
			++j;
		}
		++i;
	}
	return (k);
}

void	pathfinding_list_pos(t_data *data)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	k = 0;
	data->enemy.valid_pos_n = pathfinding_list_pos_get(data);
	data->enemy.valid_pos = malloc(sizeof(t_vec) * data->enemy.valid_pos_n);
	if (data->enemy.valid_pos_n > 0 && !data->enemy.valid_pos)
		free_exit(data);
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == '0')
			{
				data->enemy.valid_pos[k] = (t_vec){j, i};
				++k;
			}
			++j;
		}
		++i;
	}
}

t_vec	pathfinding_get_pos(t_data *data)
{
	size_t	i;
	size_t	random;

	i = 0;
	random = rand() % (data->enemy.valid_pos_n - 1);
	while (i < random && i < data->enemy.valid_pos_n - 1)
		++i;
	return (data->enemy.valid_pos[i]);
}

void	pathfinding_dist_check(t_data *data, size_t min)
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	while (data->map->map[i])
	{
		if (data->map->size_arr[i] > (int)min + 1)
		{
			check++;
			break ;
		}
		++i;
	}
	if (data->map->size.y > (int)min + 1)
		check++;
	if (check == 0)
		data->enemy.disable_ai = 1;
}

t_vec2	pathfinding_pos_dist(t_data *data, t_vec2 start, t_vec2 end, size_t min)
{
	int		tries;
	double	dist;
	t_vec	tmp;
	t_vec2	new;

	tries = 1500;
	dist = -1;
	while (dist == -1 || dist < min)
	{
		tmp = pathfinding_get_pos(data);
		new = (t_vec2){tmp.x + 0.5, tmp.y + 0.5};
		dist = ft_vect2_distance_calc(new, end);
		if (new.x == start.x && new.y == start.y)
			dist = -1;
		tries--;
		if (tries <= 0)
			return ((t_vec2){-1, -1});
	}
	return (new);
}
