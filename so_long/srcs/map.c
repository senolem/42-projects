/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:38:45 by albaur            #+#    #+#             */
/*   Updated: 2022/04/20 11:58:54 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	map_init(t_map *map, char *str)
{
	map->map = (char **)malloc(sizeof(char *));
	map->columns = ft_strlen(str);
	map->rows = 1;
	map->map[0] = str;
	map->p_nb = 0;
	map->c_nb = 0;
	map->e_nb = 0;
}

void	map_read(t_data *data, char *fileName)
{
	int		fd;
	char	*str;
	t_map	*map;

	fd = open(fileName, O_RDONLY);
	if (!fd)
		error_handler("\x1B[31mError : cannot read map.");
	str = gnl_map(fd);
	map = &data->map;
	if (str)
		map_init(map, str);
	else
		error_handler("\x1B[31mError : map file empty.");
	str = gnl_map(fd);
	while (str)
	{
		char_check(str);
		len_check(str, data->map.columns);
		map->rows++;
		data->map.map = (char **)ft_ptr_realloc(data->map.map, map->rows - 1,
				map->rows);
		data->map.map[map->rows - 1] = str;
		str = gnl_map(fd);
	}
}

void	map_parse(t_data *data, char *fileName)
{
	ext_check(fileName);
	map_read(data, fileName);
	count_component(&data->map);
}

char	*gnl_map(int fd)
{
	int		i;
	char	*str;
	char	eol;

	str = get_next_line(fd);
	if (!str)
		return (NULL);
	i = ft_strlen(str);
	eol = str[i - 1];
	if (eol == '\n')
		str[i - 1] = 0;
	return (str);
}
