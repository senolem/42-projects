/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_from_uchar_to_rgb_buf.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:00:51 by faventur          #+#    #+#             */
/*   Updated: 2022/11/15 16:37:42 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

uint32_t	*uchar_to_arr(unsigned char *arr, size_t width,
				size_t height)
{
	uint32_t	*hex_arr;
	size_t		i;
	size_t		j;

	if (!arr)
		return (NULL);
	hex_arr = malloc(sizeof(uint32_t) * width * height);
	if (!hex_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < width * height * 4 && j < width * height)
	{
		hex_arr[j] = get_rgba(arr[i], arr[i + 1], arr[i + 2], arr[i + 3]);
		i += 4;
		j++;
	}
	return (hex_arr);
}

uint32_t	**hex_buf_creator(uint32_t *arr, size_t width, size_t height)
{
	uint32_t	**hex_buf;
	size_t		i;
	size_t		j;
	size_t		k;

	if (!arr)
		return (NULL);
	hex_buf = malloc(sizeof(uint32_t *) * height);
	if (!hex_buf)
		return (NULL);
	i = -1;
	k = 0;
	while (++i < height && k < height * width)
	{
		hex_buf[i] = malloc(sizeof(uint32_t) * width);
		if (!hex_buf[i])
			return (NULL);
		j = -1;
		while (++j < width && k < height * width)
		{
			hex_buf[i][j] = arr[k];
			k++;
		}
	}
	return (hex_buf);
}

t_color	**rgb_buf_creator(uint32_t **buf, size_t width, size_t height)
{
	t_color	**rgb_buf;
	size_t	i;
	size_t	j;

	if (!buf)
		return (NULL);
	rgb_buf = (t_color **)malloc(sizeof(t_color *) * height);
	i = 0;
	while (i < height)
	{
		rgb_buf[i] = (t_color *)malloc(sizeof(t_color) * width);
		j = 0;
		while (j < width)
		{
			rgb_buf[i][j] = hex_to_rgb(buf[i][j]);
			j++;
		}
		i++;
	}
	return (rgb_buf);
}

uint32_t	**ft_from_uchar_to_hex_buf(unsigned char *arr, size_t width,
				size_t height)
{
	uint32_t	*hex_arr;
	uint32_t	**hex_buf;

	hex_arr = uchar_to_arr(arr, width, height);
	hex_buf = hex_buf_creator(hex_arr, width, height);
	free(hex_arr);
	return (hex_buf);
}

t_color	**ft_from_uchar_to_rgb_buf(unsigned char *arr, size_t width,
			size_t height)
{
	uint32_t	*hex_arr;
	uint32_t	**hex_buf;
	t_color		**rgb_buf;

	hex_arr = uchar_to_arr(arr, width, height);
	hex_buf = hex_buf_creator(hex_arr, width, height);
	rgb_buf = rgb_buf_creator(hex_buf, width, height);
	free(hex_arr);
	free_uint_arr(hex_buf, height);
	return (rgb_buf);
}
