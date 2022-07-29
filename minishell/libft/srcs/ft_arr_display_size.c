/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_display_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:24:33 by faventur          #+#    #+#             */
/*   Updated: 2022/07/05 13:29:32 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arr_display_size(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}
