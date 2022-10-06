/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:07:41 by faventur          #+#    #+#             */
/*   Updated: 2022/10/02 16:05:36 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_put_background() function creates a background by the repetition
** of an image. The amount of times the image is repeated is function of
** the size of the window.
*/

#include "mlx_utils.h"

static void	ft_display_moves_pt2(t_program *d, t_vector pos, int key,
		int *counter)
{
	if (key == 1 && d->map->map[pos.y + 1][pos.x] != '1')
	{
		if (d->map->map[pos.y + 1][pos.x] == 'C' || d->map->map[pos.y + 1][pos.x] == '0')
		{
			d->map->map[pos.y][pos.x] = '0';
			d->map->map[pos.y + 1][pos.x] = 'F';
			(*counter)++;
		}
		else if (d->map->map[pos.y + 1][pos.x] == 'E')
			ft_break_the_game(d, "You win!");
	}
	else if (key == 13 && d->map->map[pos.y - 1][pos.x] != '1')
	{
		if (d->map->map[pos.y - 1][pos.x] == 'C' || d->map->map[pos.y - 1][pos.x] == '0')
		{
			d->map->map[pos.y][pos.x] = '0';
			d->map->map[pos.y - 1][pos.x] = 'B';
			(*counter)++;
		}
		else if (d->map->map[pos.y - 1][pos.x] == 'E')
			ft_break_the_game(d, "You win!");
	}
	else if (key == 53)
		exit(0);
}

void	ft_display_moves(t_program *d, int key, t_vector pos, int *counter)
{
	if (key == 0 && d->map->map[pos.y][pos.x - 1] != '1')
	{
		if (d->map->map[pos.y][pos.x - 1] == 'C' || d->map->map[pos.y][pos.x - 1] == '0')
		{
			d->map->map[pos.y][pos.x] = '0';
			d->map->map[pos.y][pos.x - 1] = 'L';
			(*counter)++;
		}
		else if (d->map->map[pos.y][pos.x - 1] == 'E')
			ft_break_the_game(d, "You win!");
	}
	else if (key == 2 && d->map->map[pos.y][pos.x + 1] != '1')
	{
		if (d->map->map[pos.y][pos.x + 1] == 'C' || d->map->map[pos.y][pos.x + 1] == '0')
		{
			d->map->map[pos.y][pos.x] = '0';
			d->map->map[pos.y][pos.x + 1] = 'P';
			(*counter)++;
		}
		else if (d->map->map[pos.y][pos.x + 1] == 'E')
			ft_break_the_game(d, "You win!");
	}
	else
		ft_display_moves_pt2(d, pos, key, counter);
}

void	ft_display_map(t_program *data, t_image *pixie)
{
	uint32_t	i[2];
	char		c;

	i[0] = 0;
	while (i[0] * pixie[0].texture->texture.height < HEIGHT && data->map->map[i[0]])
	{
		i[1] = 0;
		while (i[1] * pixie[0].texture->texture.width < WIDTH
			&& data->map->map[i[0]][i[1]] != '\n')
		{
			c = data->map->map[i[0]][i[1]];
			ft_invoke_pixie(c, i, data, pixie);
			i[1]++;
		}
		i[0]++;
	}
}
