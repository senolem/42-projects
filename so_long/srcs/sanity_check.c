/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanity_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:18:22 by albaur            #+#    #+#             */
/*   Updated: 2022/11/29 10:24:56 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ext_check(char *fileName)
{
	char	*ext;
	int		cmp;

	ext = ft_strrchr(fileName, '.');
	if (!ext)
		error_handler("\x1B[31mError : map file extension is not .ber");
	cmp = ft_strncmp(ext, ".ber", 4);
	if (cmp)
		error_handler("\x1B[31mError : map file extension is not .ber");
}

void	char_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '0' || str[i] == '1' || str[i] == 'C' || str[i] == 'E'
				|| str[i] == 'P' || str[i] == 'F'))
			error_handler("\x1B[31mError : unknown characters in map file.");
		i++;
	}
}

void	len_check(char *str, int len)
{
	if ((int)ft_strlen(str) != len)
		error_handler("\x1B[31mError : map size is invalid.");
}

void	wall_check(t_map *map, int i)
{
	char	*str;
	int		j;

	str = map->map[i];
	if (i == 0 || i == map->rows - 1)
	{
		j = 0;
		while (j < map->columns)
		{
			if (str[j] != '1')
				error_handler("\x1B[31mError : map is not enclosed.");
			j++;
		}
	}
	else
	{
		if (!(str[0] == '1' && str[map->columns - 1] == '1'))
			error_handler("\x1B[31mError : map is not enclosed.");
	}
}

void	min_check(t_map *map)
{
	if (map->p_nb != 1)
		ft_printf("\x1B[31mError : map file must contain one player position.");
	if (map->c_nb < 1)
		ft_printf("\x1B[31mError : map file must contain one collectible.");
	if (map->e_nb < 1)
		ft_printf("\x1B[31mError : map file must contain one exit.");
	if (map->p_nb != 1 || map->c_nb < 1 || map->e_nb < 1)
		exit(EXIT_FAILURE);
}
