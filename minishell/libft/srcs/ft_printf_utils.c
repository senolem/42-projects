/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:56:39 by faventur          #+#    #+#             */
/*   Updated: 2022/03/12 14:25:44 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_count(char c, int *n_char)
{
	write(1, &c, 1);
	(*n_char)++;
	return (*n_char);
}

int	ft_putstr_count(char *str, int *n_char)
{
	if (!str)
	{
		write(1, "(null)", 6);
		*n_char += 6;
		return (*n_char);
	}
	while (*str != '\0')
	{
		ft_putchar_count(*str, n_char);
		str++;
	}
	return (*n_char);
}

int	ft_putnbr_count(int nbr, char *base, int *n_char)
{
	int			i;
	int			ret[100];
	long int	x;

	i = 0;
	x = nbr;
	if (nbr == 0)
		ft_putchar_count(0 + '0', n_char);
	if (x < 0)
	{
		x *= -1;
		ft_putchar_count('-', n_char);
	}
	while (x > 0)
	{
		ret[i] = x % 10;
		x /= 10;
		i++;
	}
	while (--i >= 0)
		ft_putchar_count(base[ret[i]], n_char);
	return (*n_char);
}

int	ft_put_unsigned(int nbr, char *base, int *n_char)
{
	int				i;
	int				ret[100];
	unsigned int	x;

	x = (unsigned int)nbr;
	i = 0;
	if (nbr == 0)
		ft_putchar_count(0 + '0', n_char);
	while (x > 0)
	{
		ret[i] = x % 10;
		x /= 10;
		i++;
	}
	while (--i >= 0)
		ft_putchar_count(base[ret[i]], n_char);
	return (*n_char);
}
