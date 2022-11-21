/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_spawn_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:43:33 by faventur          #+#    #+#             */
/*   Updated: 2022/10/19 15:56:41 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	get_spawn_position(t_map *m)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (m->map[++i])
	{
		j = -1;
		while (m->map[i][++j])
		{
			if (m->map[i][j] == 'N' || m->map[i][j] == 'S'
				|| m->map[i][j] == 'E' || m->map[i][j] == 'W')
			{
				m->dir = m->map[i][j];
				m->spawn_pos.y = i;
				m->spawn_pos.x = j;
				return (0);
			}
		}
	}
	return (-1);
}
