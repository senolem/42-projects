/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:44:41 by faventur          #+#    #+#             */
/*   Updated: 2022/09/28 12:33:17 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
/*
void	track_ur_move_down(t_program *data, t_nme death)
{
	if (data->map[death.pos.y + 1][death.pos.x] != '1'
			&& data->map[death.pos.y + 1][death.pos.x] != 'C'
			&& data->map[death.pos.y + 1][death.pos.x] != 'E')
	{
		data->map[death.pos.y][death.pos.x] = '0';
		if (data->map[death.pos.y + 1][death.pos.x] == who_is_it(data->map))
			ft_break_the_game(data, "You lose!");
		data->map[death.pos.y + 1][death.pos.x] = 'K';
	}
}

void	track_ur_move_right(t_program *data, t_nme death)
{
	if (data->map[death.pos.y][death.pos.x + 1] != '1'
			&& data->map[death.pos.y][death.pos.x + 1] != 'C'
			&& data->map[death.pos.y][death.pos.x + 1] != 'E')
	{
		data->map[death.pos.y][death.pos.x] = '0';
		if (data->map[death.pos.y][death.pos.x + 1] == who_is_it(data->map))
			ft_break_the_game(data, "You lose!");
		data->map[death.pos.y][death.pos.x + 1] = 'K';
	}
}

void	track_ur_move_up(t_program *data, t_nme death)
{
	if (data->map[death.pos.y - 1][death.pos.x] != '1'
			&& data->map[death.pos.y - 1][death.pos.x] != 'C'
			&& data->map[death.pos.y - 1][death.pos.x] != 'E')
	{
		data->map[death.pos.y][death.pos.x] = '0';
		if (data->map[death.pos.y - 1][death.pos.x] == who_is_it(data->map))
			ft_break_the_game(data, "You lose!");
		data->map[death.pos.y - 1][death.pos.x] = 'K';
	}
}

void	track_ur_move_left(t_program *data, t_nme death)
{
	if (data->map[death.pos.y][death.pos.x - 1] != '1'
			&& data->map[death.pos.y][death.pos.x - 1] != 'C'
			&& data->map[death.pos.y][death.pos.x - 1] != 'E')
	{
		data->map[death.pos.y][death.pos.x] = '0';
		if (data->map[death.pos.y][death.pos.x - 1] == who_is_it(data->map))
			ft_break_the_game(data, "You lose!");
		data->map[death.pos.y][death.pos.x - 1] = 'K';
	}
}

void	move_ur_ass(t_program *data)
{
	t_nme		death;

	death.pos = ft_get_x_and_y(data->map, 'K');
	if (data->map[death.pos.y - 1][death.pos.x] == '1'
		&& data->map[death.pos.y - 1][death.pos.x + 1] == '1')
		track_ur_move_right(data, death);
	if (data->map[death.pos.y][death.pos.x + 1] == '1'
		&& data->map[death.pos.y + 1][death.pos.x + 1] == '1')
		track_ur_move_down(data, death);
	if (data->map[death.pos.y + 1][death.pos.x] == '1'
		&& data->map[death.pos.y + 1][death.pos.x - 1] == '1')
		track_ur_move_left(data, death);
	if (data->map[death.pos.y][death.pos.x - 1] == '1'
		&& data->map[death.pos.y - 1][death.pos.x - 1] == '1')
		track_ur_move_up(data, death);
}
*/