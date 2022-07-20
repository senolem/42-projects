/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 07:45:37 by albaur            #+#    #+#             */
/*   Updated: 2022/04/28 14:01:28 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_player_animate(t_data *data)
{
	int	step;

	step = T_S % 8;
	if (data->is_moving == 1)
		collision_manage(data, 0, -step);
	else if (data->is_moving == 2)
		collision_manage(data, -step, 0);
	else if (data->is_moving == 3)
		collision_manage(data, step, 0);
	else if (data->is_moving == 4)
		collision_manage(data, 0, step);
	data->offset += step;
	if (data->offset > MAX_OFFSET)
			data->offset = 0;
	put_mlx(data, data->player.sprite->img, data->player.x, data->player.y);
	data->player.sprite = data->player.sprite->next;
}

void	render_item_animate(t_data *data)
{
	t_component	*storage;

	storage = data->storage.storage;
	while (storage)
	{
		put_mlx(data, data->tiles.floor, storage->x, storage->y);
		put_mlx(data, data->storage.sprite->img, storage->x, storage->y);
		storage = storage->next;
	}
	data->storage.sprite = data->storage.sprite->next;
}

void	render_exit(t_data *data)
{
	char	*str;
	int		rows;
	int		columns;

	rows = 0;
	while (rows < data->map.rows)
	{
		str = data->map.map[rows];
		columns = 0;
		while (columns < data->map.columns)
		{
			if (str[columns] == 'E')
			{
				if (data->storage.storage)
					put_mlx(data, data->tiles.exit, columns * T_S, rows * T_S);
				else
					put_mlx(data, data->tiles.open_exit,
						columns * T_S, rows * T_S);
			}
			columns++;
		}
		rows++;
	}
}

void	render_tiles(t_data *data)
{
	t_map	map;
	char	*str;
	int		rows;
	int		columns;

	map = data->map;
	rows = 0;
	while (rows < map.rows)
	{
		str = map.map[rows];
		columns = 0;
		while (columns < map.columns)
		{
			if (str[columns] == '1')
				put_mlx(data, data->tiles.wall, columns * T_S, rows * T_S);
			else
				put_mlx(data, data->tiles.floor, columns * T_S, rows * T_S);
			columns++;
		}
		rows++;
	}
}

void	render_sprites(t_data *data)
{
	char	*str;
	int		row_idx;
	int		col_idx;

	row_idx = 0;
	while (row_idx < data->map.rows)
	{
		str = data->map.map[row_idx];
		col_idx = 0;
		while (col_idx < data->map.columns)
		{
			if (str[col_idx] == 'P')
			{
				data->player.x = col_idx * T_S;
				data->player.y = row_idx * T_S;
				put_mlx(data, data->player.sprite->img,
					data->player.x, data->player.y);
			}
			else if (str[col_idx] == 'C')
				ft_lstc_add(&data->storage.storage,
					col_idx * T_S, row_idx * T_S);
			col_idx++;
		}
		row_idx++;
	}
}
