/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/11/17 12:28:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include "miniaudio.h"

static void	batch_init(t_data *data)
{
	init_struct(data);
	data->mlx = mlx_init(data->screen.display.size.x,
			data->screen.display.size.y, "cub3d", false);
	data->screen.display.img = mlx_new_image(data->mlx,
			data->screen.display.size.x, data->screen.display.size.y);
	if (!data->screen.display.img)
		throw_err_ex("Error : Creating new MLX image failed.");
	init_textures(data);
	init_minimap(data);
	init_hud(data);
	init_quest(data);
	init_audio(data);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.map = check(argc, argv);
	if (!data.map->map)
		ft_puterror("Error!");
	batch_init(&data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(data.mlx, data.screen.display.img, 0, 0);
	mlx_loop_hook(data.mlx, update_render, &data);
	mlx_key_hook(data.mlx, update_key, &data);
	mlx_cursor_hook(data.mlx, mouse_input, &data);
	mlx_close_hook(data.mlx, close_hook, &data);
	mlx_loop(data.mlx);
	free_data(&data);
}
