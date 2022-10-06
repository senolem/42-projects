/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:44:41 by faventur          #+#    #+#             */
/*   Updated: 2022/09/23 09:50:42 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

char	who_is_it(char **map)
{
	t_vector	pos;
	char		who;

	pos = ft_get_x_and_y(map, 'P');
	who = 'P';
	if (pos.x == 3000)
	{
		pos = ft_get_x_and_y(map, 'L');
		who = 'L';
	}
	if (pos.x == 3000)
	{
		pos = ft_get_x_and_y(map, 'F');
		who = 'F';
	}
	if (pos.x == 3000)
	{
		pos = ft_get_x_and_y(map, 'B');
		who = 'B';
	}
	return (who);
}

void	ft_break_the_game(t_program *data, char *end_msg)
{
	(void)end_msg;
//	mlx_clear_window(data->mlx, data->window.reference);
//	mlx_string_put(data->mlx, data->window.reference,
//		data->window.size.x / 2 - 30, data->window.size.y / 2,
//		0xffffffff, end_msg);
//	mlx_hook(data->window.reference, 2, 1L << 0, *ft_close, data);
	mlx_loop(data->mlx);
}
