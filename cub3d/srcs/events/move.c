/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:11:35 by albaur            #+#    #+#             */
/*   Updated: 2022/11/14 14:57:47 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_move(t_data *data)
{
	size_t	i;

	i = rand() % 5;
	if (data->hud.pos > 19)
		data->hud.pos = 0;
	if (data->hud.pos > 0)
		data->hud.sprites[data->hud.pos - 1].img->enabled = 0;
	else if (data->hud.pos == 0)
		data->hud.sprites[19].img->enabled = 0;
	data->hud.sprites[data->hud.pos].img->enabled = 1;
	++data->hud.pos;
	if (data->timer >= data->player.footstep_timer + 0.4
		&& data->player.footstep_lock == 0)
	{
		data->player.footstep_timer = data->timer;
		data->player.footstep_lock = 1;
		if (ma_sound_is_playing(&data->audio.footstep[i]))
			ma_sound_seek_to_pcm_frame(&data->audio.footstep[i], 0);
		ma_sound_start(&data->audio.footstep[i]);
	}
	else if (data->timer >= data->player.footstep_timer + 0.4)
		data->player.footstep_lock = 0;
}
