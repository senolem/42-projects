/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:03:57 by faventur          #+#    #+#             */
/*   Updated: 2022/10/19 13:56:12 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	check_args(char argc)
{
	if (argc != 2)
		throw_err_ex("Error: Invalid number of arguments.");
}

t_map	*check(int argc, char **argv)
{
	check_args(argc);
	check_map_extension(argv);
	return (check_map_integrity(argv[1]));
}
