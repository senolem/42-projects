/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 03:00:00 by albaur            #+#    #+#             */
/*   Updated: 2022/04/25 16:39:12 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	error_handler(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		error_handler("\x1B[31mError : please provide a valid map.");
	map_parse(&data, argv[1]);
	game_init(&data);
	mlx_hook(data.win_ptr, 17, 0, &close_hook, &data);
	mlx_key_hook(data.win_ptr, &key_hook, &data);
	mlx_loop_hook(data.mlx_ptr, &loop_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
