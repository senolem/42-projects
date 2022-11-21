/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:48:22 by albaur            #+#    #+#             */
/*   Updated: 2022/11/15 16:35:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	check_texture(t_map *m, char *map, int *count, t_ctexture c)
{
	if (c.str[1] == '\0')
	{
		if (map[0] == c.str[0] && map[1] == ' ')
		{
			if (get_color(map, m, c.index) == -1)
				return (1);
			++*count;
			return (0);
		}
	}
	else
	{
		if (map[0] == c.str[0] && map[1] == c.str[1] && map[2] == ' ')
		{
			if (get_texture(map, m, c.index) == -1)
				return (1);
			++*count;
			return (0);
		}
	}
	return (1);
}

static int	check_map_settings(t_map *m, char **map)
{
	size_t			i;
	int				count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		if (ft_strlen(map[i]) < 3)
			return (-1);
		if (!check_texture_batch(m, map, i, &count))
			continue ;
		else
		{
			if (count == 6 && (m->mode == -1 || m->mode == 1))
				return (0);
			return (-1);
		}
	}
	return (0);
}

static void	check_map_integrity_vol2(t_map *m, char **map)
{
	if (check_map_components(m->map) == -1)
	{
		ft_arr_freer(map);
		throw_err_ex("Error : Invalid map file.");
	}
	ft_arr_freer(map);
}

t_map	*check_map_integrity(char *path)
{
	t_map	*mapstruct;
	char	**map;

	mapstruct = malloc(sizeof(t_map));
	if (!mapstruct)
		return (NULL);
	mapstruct->mode = -1;
	map = ft_map_reader(path);
	if (check_map_settings(mapstruct, map) == -1)
	{
		ft_arr_freer(map);
		throw_err_ex("Error : Invalid map file.");
	}
	mapstruct->map = get_map_description(map);
	if (mapstruct->map == NULL)
	{
		ft_arr_freer(map);
		throw_err_ex("Error : Invalid map file.");
	}
	check_map_integrity_vol2(mapstruct, map);
	get_spawn_position(mapstruct);
	return (mapstruct);
}

void	check_map_extension(char *argv[])
{
	int	fd;

	if (!ft_strstr(argv[1], ".cub\0"))
		throw_err_ex("Error: Invalid file extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		throw_err_ex("Error: Cannot open file.");
	}
	close(fd);
}
