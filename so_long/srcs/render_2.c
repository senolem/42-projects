/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:01:31 by albaur            #+#    #+#             */
/*   Updated: 2022/04/28 12:07:56 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_hud(t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = ft_intlen(data->steps);
	if (len <= 2)
	{
		if (len == 2)
		{
			while (data->steps / 10 != i++)
				data->hud.num = data->hud.num->next;
			put_mlx(data, data->hud.num->img, 0, 20);
			i = 0;
			--len;
		}
		get_back_to_head(data);
		if (len == 1)
		{
			while (data->steps % 10 != i++)
				data->hud.num = data->hud.num->next;
			put_mlx(data, data->hud.num->img, 20, 20);
		}
		get_back_to_head(data);
	}
	render_hud_health(data);
}

void	render_enemies(t_data *data)
{
	char	*str;
	int		rows;
	int		columns;

	rows = 0;
	while (rows < data->map.rows)
	{
		str = data->map.map[rows];
		columns = 0;
		while (columns < data->map.columns)
		{
			if (str[columns] == 'F')
			{
				put_mlx(data, data->enemy.img, columns * T_S, rows * T_S);
			}
			columns++;
		}
		rows++;
	}
}

void	put_mlx(t_data *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, x, y);
}

void	render_refresh(t_data *data)
{
	render_tiles(data);
	render_item_animate(data);
	render_exit(data);
	render_hud(data);
	render_enemies(data);
	render_player_animate(data);
	if (data->offset % T_S == 0)
		render_init(data);
}

void	render_hud_health(t_data *data)
{
	int	i;

	i = 3;
	while (i > 0)
	{
		if (data->player.health == i)
			put_mlx(data, data->hud.health->img, 0, 0);
		data->hud.health = data->hud.health->next;
		--i;
	}
	while (data->hud.health != data->hud.health->head)
		data->hud.health = data->hud.health->next;
}
