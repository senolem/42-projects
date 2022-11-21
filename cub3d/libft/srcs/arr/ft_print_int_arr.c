/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:38:39 by faventur          #+#    #+#             */
/*   Updated: 2022/11/11 11:01:36 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_int_arr(int **arr, size_t height, size_t width)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			ft_printf("%i ", arr[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
}

void	ft_print_double_arr(double **arr, size_t height, size_t width)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			printf("%f ", arr[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}
