/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:28:34 by albaur            #+#    #+#             */
/*   Updated: 2022/04/25 16:09:14 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	collision_enemy(t_data *data, int x, int y)
{
	char	**map;
	int		columns;
	int		rows;

	map = data->map.map;
	columns = data->player.x + x;
	rows = data->player.y + y;
	if (!(rows % T_S) && !(columns % T_S)
		&& map[rows / T_S][columns / T_S] == 'F')
	{
		if (--data->player.health <= 0)
		{
			ft_printf("\x1B[33mGAME OVER 💀\n");
			exit(EXIT_SUCCESS);
		}
		else
			ft_printf("Ouch!\n");
	}
}

void	set_player_sprite(t_data *data)
{
	if (data->is_moving == 1)
	{
		data->player.sprite = data->player.u_move;
		data->player.idle = data->player.u_idle;
	}
	else if (data->is_moving == 2)
	{
		data->player.sprite = data->player.l_move;
		data->player.idle = data->player.l_idle;
	}
	else if (data->is_moving == 3)
	{
		data->player.sprite = data->player.r_move;
		data->player.idle = data->player.r_idle;
	}
	else if (data->is_moving == 4)
	{
		data->player.sprite = data->player.d_move;
		data->player.idle = data->player.d_idle;
	}
}
