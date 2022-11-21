/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gap_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:57:29 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 13:34:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	is_ok(char c)
{
	if (c == '1' || c == '8')
		return (0);
	return (1);
}

static int	gap_check_ret(char **map, ssize_t i, ssize_t j)
{
	if (j < (ssize_t)ft_strlen(map[i + 1]) - 1 && !is_ok(map[i + 1][j + 1]))
	{
		if (!gap_check_reverse(map, i, j))
			return (0);
	}
	return (1);
}

static int	gap_check_ret2(char **map, ssize_t i, ssize_t j)
{
	if (j < (ssize_t)ft_strlen(map[i - 1]) - 1 && !is_ok(map[i - 1][j + 1]))
	{
		if (!gap_check_reverse(map, i, j))
			return (0);
	}
	if (j < (ssize_t)ft_strlen(map[i - 1]) - 1
		&& i < ft_arrlen(map) - 1 && !is_ok(map[i + 1][j + 1]))
	{
		if (!gap_check_reverse(map, i, j))
			return (0);
	}
	return (1);
}

int	gap_check(char **map)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
			{
				if (j < (ssize_t)ft_strlen(map[i]) - 1 && map[i][j + 1] == ' ')
					continue ;
				if (j < (ssize_t)ft_strlen(map[i]) - 1 && !is_ok(map[i][j + 1]))
				{
					if (i == 0 && !gap_check_ret(map, i, j))
						continue ;
					else if (!gap_check_ret2(map, i, j))
						continue ;
				}
				return (-1);
			}
		}
	}
	return (0);
}
