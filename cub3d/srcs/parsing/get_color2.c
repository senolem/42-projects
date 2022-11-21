/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:26:03 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 16:23:35 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	get_color_check(char **colors, ssize_t j)
{
	ssize_t	k;

	while (colors[++j])
	{
		k = -1;
		while (colors[j][++k])
		{
			if (ft_isdigit(colors[j][k]) != 1)
				return (1);
		}
	}
	return (0);
}
