/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:13:40 by faventur          #+#    #+#             */
/*   Updated: 2022/03/01 18:18:52 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_putstr_fd() function writes a string on the file descriptor. 
*/

#include "libft.h"

void	ft_putstr_fd(char const *str, int fd)
{
	if (fd >= 0 && str)
	{
		while (*str != '\0')
		{
			ft_putchar_fd(*str, fd);
			str++;
		}
	}
}
