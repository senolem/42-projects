/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:21:12 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 16:51:50 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	get_delay(1, 16666);
	while (data->delay > 16666)
	{
		key_input(data);
		++data->time;
		data->delay -= 16666;
	}
	key_input(data);
	if (data->exit == 1)
		return (close_hook(data));
	if (update_events(data))
		return ;
	ray_casting(data);
	update_doors(data, &data->ray_data);
	draw_minimap(data);
	data->delay += get_delay(0, 16666);
	++data->time;
	data->timer = get_time();
	if (data->enemy.alive == 0 && data->quest.done != 3)
		show_death(data);
}
