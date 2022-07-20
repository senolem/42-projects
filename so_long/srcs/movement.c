/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:35:43 by albaur            #+#    #+#             */
/*   Updated: 2022/04/28 13:59:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move(int key, t_data *data)
{
	if (key == 13)
	{
		data->is_moving = 1;
		data->offset = data->player.y;
		set_player_sprite(data);
	}
	if (key == 0)
	{
		data->is_moving = 2;
		data->offset = data->player.x;
		set_player_sprite(data);
	}
	if (key == 1)
	{
		data->is_moving = 4;
		data->offset = data->player.y;
		set_player_sprite(data);
	}
	if (key == 2)
	{
		data->is_moving = 3;
		data->offset = data->player.x;
		set_player_sprite(data);
	}
}

void	collision_wall(t_data *data, int x, int y)
{
	char		**map;
	int			columns;
	int			rows;
	static int	i = 0;

	map = data->map.map;
	columns = (data->player.x + x) / T_S;
	rows = (data->player.y + y) / T_S;
	if (x > 0)
		columns += 1;
	else if (y > 0)
		rows += 1;
	if (map[rows][columns] != '1' ||
		(!((data->player.x + x) % T_S) && !((data->player.y + y) % T_S)))
	{
		data->player.x += x;
		data->player.y += y;
		++i;
	}
	if (i == 9)
	{
		++(data->steps);
		i = 0;
	}
}

void	collision_item(t_data *data, int x, int y)
{
	char	**map;
	int		columns;
	int		rows;

	map = data->map.map;
	columns = data->player.x + x;
	rows = data->player.y + y;
	if (!(rows % T_S) && !(columns % T_S)
		&& map[rows / T_S][columns / T_S] == 'C')
	{
		ft_lstc_delete(&data->storage.storage, data->player.x + x,
			data->player.y + y);
		put_mlx(data, data->tiles.floor, data->player.x + x,
			data->player.y + y);
	}
}

void	collision_exit(t_data *data, int x, int y)
{
	char	**map;
	int		columns;
	int		rows;

	map = data->map.map;
	columns = data->player.x + x;
	rows = data->player.y + y;
	if (!(rows % T_S) && !(columns % T_S)
		&& map[rows / T_S][columns / T_S] == 'E')
	{
		if (!data->storage.storage)
		{
			ft_printf("\x1B[33mYOU WON ! 👑\n");
			exit(EXIT_SUCCESS);
		}
	}
}

void	collision_manage(t_data *data, int x, int y)
{
	collision_wall(data, x, y);
	collision_item(data, x, y);
	collision_exit(data, x, y);
	collision_enemy(data, x, y);
}
