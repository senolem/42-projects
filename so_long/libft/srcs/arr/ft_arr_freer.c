/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_freer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:22:41 by albaur            #+#    #+#             */
/*   Updated: 2022/11/15 18:19:55 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arr_freer(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_uint_arr(uint32_t **arr, size_t size)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}
