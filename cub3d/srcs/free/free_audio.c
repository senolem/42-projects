/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:26:09 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 14:26:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_audio(t_data *data)
{
	free_audio_behind_you(data);
	free_audio_player(data);
	free_audio_ambiance(data);
	free_audio_suspense(data);
	ma_engine_uninit(data->audio.audio_engine);
	free(data->audio.suspense);
	free(data->audio.footstep);
	free(data->audio.death);
	free(data->audio.dead);
	free(data->audio.smiler);
	free(data->audio.behind_you);
	free(data->audio.door);
	free(data->audio.audio_engine);
}
