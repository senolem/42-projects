/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 04:45:10 by albaur            #+#    #+#             */
/*   Updated: 2022/04/28 12:10:37 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*xpm_to_img(t_data *data, char *path)
{
	char	*apath;
	void	*img;
	int		width;
	int		height;

	apath = ft_strjoin("./sprites/", path);
	img = mlx_xpm_file_to_image(data->mlx_ptr, apath, &width, &height);
	if (!img)
		error_handler("\x1B[31mError : invalid file.");
	return (img);
}

void	img_to_sprite(t_data *data, t_sprite **sprite, char *img, int c)
{
	t_sprite	*tmp;
	char		*filename;
	char		*xpm;
	int			num;
	int			i;

	*sprite = (t_sprite *)malloc(sizeof(t_sprite));
	tmp = *sprite;
	i = 0;
	while (i < c)
	{
		num = '0' + i;
		filename = ft_strjoin(img, (char *)&num);
		xpm = ft_strjoin(filename, ".xpm");
		tmp->img = xpm_to_img(data, xpm);
		free(filename);
		free(xpm);
		if (i != c - 1)
		{
			tmp->next = (t_sprite *)malloc(sizeof(t_sprite));
			tmp = tmp->next;
		}
		i++;
	}
	tmp->next = *sprite;
}

void	count_component(t_map *map)
{
	int		i;
	int		j;
	char	*rows;

	i = 0;
	while (i < map->rows)
	{
		wall_check(map, i);
		rows = map->map[i];
		j = 0;
		while (j < map->columns)
		{
			if (rows[j] == 'P')
				map->p_nb++;
			else if (rows[j] == 'C')
				map->c_nb++;
			else if (rows[j] == 'E')
				map->e_nb++;
			j++;
		}
		i++;
	}
	min_check(map);
}

void	*ft_ptr_realloc(void *buffer, int before_size, int after_size)
{
	int		i;
	char	**src;
	char	**dst;

	src = (char **)buffer;
	dst = (char **)malloc(sizeof(char *) * after_size);
	i = 0;
	while (i < before_size)
	{
		dst[i] = src[i];
		i++;
	}
	free(buffer);
	return ((void *)dst);
}
