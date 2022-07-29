/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:56:39 by faventur          #+#    #+#             */
/*   Updated: 2022/06/26 16:10:35 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	fpf_putchar_count(char c, t_tools var)
{
	write(var.fd, &c, 1);
	(*var.n_char)++;
	return (*var.n_char);
}

int	fpf_putstr_count(char *str, t_tools var)
{
	if (!str)
	{
		write(var.fd, "(null)", 6);
		*var.n_char += 6;
		return (*var.n_char);
	}
	while (*str != '\0')
	{
		fpf_putchar_count(*str, var);
		str++;
	}
	return (*var.n_char);
}

int	fpf_putnbr_count(int nbr, char *base, t_tools var)
{
	int			i;
	int			ret[100];
	long int	x;

	i = 0;
	x = nbr;
	if (nbr == 0)
		fpf_putchar_count(0 + '0', var);
	if (x < 0)
	{
		x *= -1;
		fpf_putchar_count('-', var);
	}
	while (x > 0)
	{
		ret[i] = x % 10;
		x /= 10;
		i++;
	}
	while (--i >= 0)
		fpf_putchar_count(base[ret[i]], var);
	return (*var.n_char);
}

int	fpf_put_unsigned(int nbr, char *base, t_tools var)
{
	int				i;
	int				ret[100];
	unsigned int	x;

	x = (unsigned int)nbr;
	i = 0;
	if (nbr == 0)
		fpf_putchar_count(0 + '0', var);
	while (x > 0)
	{
		ret[i] = x % 10;
		x /= 10;
		i++;
	}
	while (--i >= 0)
		fpf_putchar_count(base[ret[i]], var);
	return (*var.n_char);
}
