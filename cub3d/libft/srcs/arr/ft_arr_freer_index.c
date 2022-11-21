/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_freer_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:38:39 by faventur          #+#    #+#             */
/*   Updated: 2022/11/15 16:27:26 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arr_freer_index(char **arr, size_t index)
{
	ssize_t	i;

	if (!arr || !*arr)
		return (NULL);
	i = index - 1;
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
	return (arr);
}

int	**free_int_arr_index(int **arr, size_t index)
{
	ssize_t	i;

	if (!arr || !*arr)
		return (NULL);
	i = index - 1;
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
	return (arr);
}

double	**free_double_arr_index(double **arr, size_t index)
{
	ssize_t	i;

	if (!arr || !*arr)
		return (NULL);
	i = index - 1;
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
	return (arr);
}

void	**free_void_arr_index(void **arr, size_t index)
{
	ssize_t	i;

	if (!arr || !*arr)
		return (NULL);
	i = index - 1;
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
	return (arr);
}
