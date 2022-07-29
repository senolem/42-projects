/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:35:34 by faventur          #+#    #+#             */
/*   Updated: 2022/03/01 18:17:54 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_putnbr_fd() function writes an integer on the file descriptor.
*/

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (fd >= 0)
	{
		if (nb == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			if (nb < 0)
			{
				nb = -nb;
				write(fd, "-", 1);
			}
			if (nb >= 10)
			{
				ft_putnbr_fd(nb / 10, fd);
				ft_putnbr_fd(nb % 10, fd);
			}
			else
				ft_putchar_fd(nb + '0', fd);
		}
	}
}
