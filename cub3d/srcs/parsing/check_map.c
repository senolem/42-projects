/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:48:22 by albaur            #+#    #+#             */
/*   Updated: 2022/10/06 17:32:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void check_map_integrity(char *path)
{
	char	**map;

	map = ft_map_reader(path);
	if (check_map_components(map) == -1)
	{
		ft_freearr(map);
		throw_err_ex("Error : Invalid map file.");
	}
}

void check_map_extension(char *argv[])
{
	int fd;

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