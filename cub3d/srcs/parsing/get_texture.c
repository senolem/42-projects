/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:56:09 by albaur            #+#    #+#             */
/*   Updated: 2022/11/02 11:07:14 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	get_texture_mode(t_map *mapStruct, int mode, char *path)
{
	if (mode == 0)
		mapStruct->north_texture = path;
	else if (mode == 1)
		mapStruct->south_texture = path;
	else if (mode == 2)
		mapStruct->west_texture = path;
	else if (mode == 3)
		mapStruct->east_texture = path;
	else if (mode == 4)
	{
		mapStruct->mode++;
		mapStruct->ceiling_texture = path;
	}
	else if (mode == 5)
	{
		mapStruct->mode++;
		mapStruct->floor_texture = path;
	}
}

static int	get_texture_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

static int	get_texture_ret(char *path)
{
	free(path);
	return (-1);
}

int	get_texture(char *str, t_map *mapStruct, int mode)
{
	size_t	i;
	char	*path;

	i = 3;
	while (str[i])
	{
		if (str[i] == ' ')
			++i;
		else if (ft_isascii(str[i]))
		{
			path = malloc(sizeof(char) * (ft_strlen(str + i) + 1));
			if (!path)
				return (-1);
			ft_strcpy(path, str + i);
			if (!ft_strstr(path, ".xpm42\0"))
				return (get_texture_ret(path));
			if (get_texture_file(path))
				return (get_texture_ret(path));
			get_texture_mode(mapStruct, mode, path);
			return (0);
		}
	}
	return (-1);
}
