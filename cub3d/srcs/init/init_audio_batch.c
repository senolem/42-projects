/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_audio_batch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:25:05 by albaur            #+#    #+#             */
/*   Updated: 2022/11/16 14:26:28 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_audio_doors(t_data *data, ma_result *result)
{
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/door_close.flac", 64, NULL, NULL, &data->audio.door[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/door_move.flac", 64, NULL, NULL, &data->audio.door[1]);
}

void	init_audio_behind_you(t_data *data, ma_result *result)
{
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/behindyou1.flac", 64, NULL, NULL,
			&data->audio.behind_you[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/behindyou2.flac", 64, NULL, NULL,
			&data->audio.behind_you[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/behindyou3.flac", 64, NULL, NULL,
			&data->audio.behind_you[2]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/behindyou4.flac", 64, NULL, NULL,
			&data->audio.behind_you[3]);
}

void	init_audio_player(t_data *data, ma_result *result)
{
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/footstep1.flac", 64, NULL, NULL, &data->audio.footstep[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/footstep2.flac", 64, NULL, NULL, &data->audio.footstep[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/footstep3.flac", 64, NULL, NULL, &data->audio.footstep[2]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/footstep4.flac", 64, NULL, NULL, &data->audio.footstep[3]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/footstep5.flac", 64, NULL, NULL, &data->audio.footstep[4]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/pickup.flac", 64, NULL, NULL, &data->audio.pickup);
}

void	init_audio_ambiance(t_data *data, ma_result *result)
{
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/ambiance.flac", 64, NULL, NULL, &data->audio.ambiance);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/dead1.flac", 64, NULL, NULL, &data->audio.dead[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/dead2.flac", 64, NULL, NULL, &data->audio.dead[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/scare.flac", 64, NULL, NULL, &data->audio.scare);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/death1.flac", 64, NULL, NULL, &data->audio.death[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/death2.flac", 64, NULL, NULL, &data->audio.death[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/smiler1.flac", 64, NULL, NULL, &data->audio.smiler[0]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/smiler2.flac", 64, NULL, NULL, &data->audio.smiler[1]);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/geiger.flac", 64, NULL, NULL, &data->audio.geiger);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/unraveled.flac", 64, NULL, NULL, &data->audio.unraveled);
	result += ma_sound_init_from_file(data->audio.audio_engine,
			"audio/creeping_down.flac", 64, NULL, NULL,
			&data->audio.creeping_down);
}

void	init_audio_suspense(t_data *data, ma_result *result)
{
	ssize_t		i;
	char		base[15];
	char		*str;
	char		*itoa;

	i = -1;
	ft_strcpy(base, "audio/suspense");
	while (++i < 14)
	{
		itoa = ft_itoa(i + 1);
		str = ft_strjoin(base, itoa);
		str = ft_concat(str, ".flac");
		result += ma_sound_init_from_file(data->audio.audio_engine,
				str, 64, NULL, NULL, &data->audio.suspense[i]);
		free(str);
		free(itoa);
	}
}
