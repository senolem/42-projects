/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:27:38 by albaur            #+#    #+#             */
/*   Updated: 2022/10/06 17:44:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	wall_check(char **map, size_t i)
{
	size_t	j;
	int		mode;

	j = 0;
	if (i == 0)
		mode = 0;
	else if (i > 0)
		mode = 1;
	else if (i == last_row)
	while (map[i][j])
	{
		
	}
}

int	check_map_components(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		if (wall_check(map, i) == -1)
			return (-1);
		rows = map->map[i];
		j = 0;
		while (j < map->columns)
		{
			if (rows[j] == 'P')
				map->p_nb++;
			else if (rows[j] == 'C')
				map->c_nb++;
			else if (rows[j] == 'E')
				map->e_nb++;
			j++;
		}
		i++;
	}
	min_check(map);
}
