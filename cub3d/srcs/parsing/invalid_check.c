/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:54:26 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 14:49:44 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	invalid_check_char(char c, size_t *count)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '0'
		&& c != '1' && c != ' ' && c != '2' && c != '3' && c != '8')
		++*count;
}

int	invalid_check(char **map)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			invalid_check_char(map[i][j], &count);
	}
	if (count != 0)
	{
		printf("Invalid character in map description.\n");
		return (-1);
	}
	else
		return (0);
}
