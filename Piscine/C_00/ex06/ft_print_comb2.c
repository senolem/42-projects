/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:18:05 by albaur            #+#    #+#             */
/*   Updated: 2021/11/13 11:46:07 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_comb2(void);

void	ft_print_comb2(void)
{
	int		a;
	int		b;
	int		c;
	int		d;

	a = 0;
	b = 1;
	while (a < 99)
	{
		c = (a / 10 + '0');
		write(1, &c, 1);
		c = (a % 10 + '0');
		write(1, &c, 1);
		write(1, " ", 1);
		d = (b / 10 + '0');
		write(1, &d, 1);
		d = (b % 10 + '0');
		write(1, &d, 1);
		if (a < 98)
			write(1, ", ", 2);
		if (++b > 99)
			b = ++a + 1;
	}
}
