/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/10/06 17:24:36 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_hook(void* param)
{
	const mlx_t* mlx;

	mlx = param;
//	ft_printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void	init_struct_child(t_program *data)
{
	data->screen->width = WIDTH;
	data->screen->height = HEIGHT;
	data->render->delay = 30;
	data->rc->precision = 64.0f;
	data->player->fov = 60.0f;
	data->player->x = 6.0f;
	data->player->y = 2.0f;
	data->player->angle = 90.0f;
	data->screen->half_width = data->screen->width / 2;
	data->screen->half_height = data->screen->height / 2;
	data->rc->increment_angle = (float)data->player->angle / (float)data->screen->width;
	data->player->half_fov = (float)data->player->fov / 2.0f;
}

void	init_struct(t_program *data)
{
	data->screen = malloc(sizeof(*data->screen));
	data->render = malloc(sizeof(*data->render));
	data->rc = malloc(sizeof(*data->rc));
	data->player = malloc(sizeof(*data->player));
	data->map = malloc(sizeof(*data->map));
	if (!data->screen || !data->render || !data->rc || !data->player
		|| !data->map)
	{
		if (data->screen)
			free(data->screen);
		if (data->render)
			free(data->render);
		if (data->rc)
			free(data->rc);
		if (data->player)
			free(data->player);
		if (data->map)
			free(data->map);
		exit(1);
	}
	init_struct_child(data);
}

void	calculate_map_size(t_program *data)
{
	data->map->height = 0;
	while (data->map->map[data->map->height])
	{
		data->map->width = 0;
		while (data->map->map[data->map->height][data->map->width])
		{
			data->map->width++;
		}
		data->map->height++;
	}
}

int	main(int argc, char *argv[])
{
	t_program	program;
	int			i;

	i = 0;
	check(argc, argv);
//	if (!program.map->map || !ft_map_parser(program.map->map))
//		ft_puterror("Error!");
	init_struct(&program);
	program.map->map = ft_map_reader(argv[1]);
	if (!program.map->map)
		ft_puterror("Error!");
	program.frame = 0;
	program.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	program.img.img = mlx_new_image(program.mlx, WIDTH, HEIGHT);
	if (!program.img.img) //|| (mlx_image_to_window(program.mlx,
			//	program.img.img, 0, 0) < 0))
		ft_puterror("Error!");
//	program.pixies = ft_put_sprite(&program);
//	ft_display_map(&program, program.pixies);
	mlx_image_to_window(program.mlx, program.img.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_update, &program);
//	mlx_loop_hook(program.mlx, ft_hook, program.mlx);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
