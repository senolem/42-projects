/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:02:15 by albaur            #+#    #+#             */
/*   Updated: 2022/04/25 15:37:17 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	close_hook(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	ft_printf("Exiting...\n");
	exit(EXIT_SUCCESS);
}

int	key_hook(int key, t_data *data)
{
	if (data->is_moving == 0 && (key == 13 || key == 0 || key == 1 || key == 2))
		move(key, data);
	else if (key == 53)
		close_hook(data);
	return (1);
}

int	loop_hook(t_data *data)
{
	static unsigned int	frame;

	if (!(++frame % 500))
	{
		if (data->is_moving != 0)
		{
			render_refresh(data);
		}
		else
			render_item_animate(data);
	}
	return (1);
}
