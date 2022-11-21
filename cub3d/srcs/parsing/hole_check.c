/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hole_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:10:21 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 11:32:49 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	hole_check_is(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != '2' && c != '3' && c != '8')
		return (-1);
	else
		return (0);
}

static void	hole_check_batch(char **map, size_t i, size_t j, int *ret)
{
	size_t	al;

	al = ft_arrlen(map) - 1;
	if (j > 0 && !hole_check_is(map[i][j - 1]))
		++*ret;
	if (j < ft_strlen(map[i]) - 1 && !hole_check_is(map[i][j + 1]))
		++*ret;
	if (i > 0 && !hole_check_is(map[i - 1][j]))
		++*ret;
	if (i < al && !hole_check_is(map[i + 1][j]))
		++*ret;
	if (i > 0 && j > 0 && !hole_check_is(map[i - 1][j - 1]))
		++*ret;
	if (i > 0 && j < ft_strlen(map[i]) - 1 && !hole_check_is(map[i - 1][j + 1]))
		++*ret;
	if (i < al && j > 0 && !hole_check_is(map[i + 1][j - 1]))
		++*ret;
	if (i < al && j < ft_strlen(map[i]) - 1
		&& !hole_check_is(map[i + 1][j + 1]))
		++*ret;
}

int	hole_check(char **map)
{
	size_t	i;
	size_t	j;
	int		ret;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			ret = 0;
			if (map[i][j] == '0')
				hole_check_batch(map, i, j, &ret);
			if (map[i][j] == '0' && ret != 8)
				return (-1);
		}
	}
	return (0);
}
