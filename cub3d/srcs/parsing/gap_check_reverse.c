/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gap_check_reverse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:04:27 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 11:41:44 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	gap_check_reverse_ret2(char **map, ssize_t i, ssize_t k)
{
	if (map[i - 1][k] == '1')
		return (0);
	else if (i < ft_arrlen(map) - 1 && (map[i + 1][k] == '1'
		|| map[i + 1][k] == '8'))
		return (0);
	else
		return (-1);
}

static int	gap_check_reverse_ret(char **map, ssize_t i, ssize_t k)
{
	if (map[i + 1][k] == '1' || map[i + 1][k] == '8')
		return (0);
	else
		return (-1);
}

int	gap_check_reverse(char **map, ssize_t i, ssize_t j)
{
	ssize_t	k;

	k = j;
	while (k >= 0)
	{
		if (map[i][k] == '1' || map[i][k] == 8)
		{
			if (i == 0)
				return (gap_check_reverse_ret(map, i, k));
			else
				return (gap_check_reverse_ret2(map, i, k));
		}
		--k;
	}
	return (0);
}
