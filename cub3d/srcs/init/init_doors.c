/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:22:57 by faventur          #+#    #+#             */
/*   Updated: 2022/11/15 16:31:09 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** As concerning the state of the doors, 0 means closed, 1 that's opening, 2
** open and 3 closing.
*/

#include "mlx_utils.h"

static void	init_door_map(t_data *data, t_ray *ray, t_var *var)
{
	t_door_data	**map;

	map = ray->door.door_map;
	var->i = 0;
	while (var->i < var->height)
	{
		map[var->i] = ft_calloc(data->map->size_arr[var->i],
				sizeof(t_door_data));
		if (!map[var->i])
			free_exit(data);
		var->j = 0;
		while (var->j < var->width && data->map->map[var->i][var->j])
		{
			if (data->map->map[var->i][var->j] == '2')
			{
				map[var->i][var->j].map_pos = (t_vec){var->i, var->j};
				map[var->i][var->j].is_door = 1;
				map[var->i][var->j].index = 50;
				++ray->door.nb_doors;
			}
			var->j++;
		}
		var->i++;
	}
}

void	init_doors(t_data *data)
{
	t_ray	*ray;
	t_var	var;

	ft_bzero(&var, sizeof(var));
	ray = &data->ray_data;
	ray->door.door_map = malloc(sizeof(t_door_data *) * data->map->size.y);
	if (data->map->size.y > 0 && !ray->door.door_map)
		free_exit(data);
	ray->door.nb_doors = 0;
	var.width = data->map->size.x;
	var.height = data->map->size.y;
	init_door_map(data, ray, &var);
}
