/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wasd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:28:49 by albaur            #+#    #+#             */
/*   Updated: 2022/11/10 15:28:56 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	is_wasd(t_data *data)
{
	if (data->key == (keys_t)MLX_KEY_W || data->key == (keys_t)MLX_KEY_A
		|| data->key == (keys_t)MLX_KEY_S || data->key == (keys_t)MLX_KEY_D)
		return (0);
	return (1);
}
