/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:26 by faventur          #+#    #+#             */
/*   Updated: 2022/03/12 13:34:29 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(va_list arg_p, const char *format, int i, int *n_char)
{
	if (format[i] == '%')
		ft_putchar_count('%', n_char);
	else if (format[i] == 'c')
		ft_putchar_count(va_arg(arg_p, int), n_char);
	else if (format[i] == 'd' || format[i] == 'i')
		ft_putnbr_count(va_arg(arg_p, int), "0123456789", n_char);
	else if (format[i] == 's')
		ft_putstr_count(va_arg(arg_p, char *), n_char);
	else if (format[i] == 'o')
		ft_putoctals_count(va_arg(arg_p, int), "01234567", n_char);
	else if (format[i] == 'u')
		ft_put_unsigned(va_arg(arg_p, int), "0123456789", n_char);
	else if (format[i] == 'x')
		ft_puthexa(va_arg(arg_p, unsigned int), "0123456789abcdef", n_char);
	else if (format[i] == 'X')
		ft_puthexa(va_arg(arg_p, unsigned int), "0123456789ABCDEF", n_char);
	else if (format[i] == 'p')
		ft_putaddr_count(va_arg(arg_p, unsigned long long), n_char);
	else
		ft_putchar_count(format[i], n_char);
	return (*n_char);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_p;
	int		tab[1];
	int		i;

	tab[0] = 0;
	i = 0;
	va_start(arg_p, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			ft_check(arg_p, format, i, &tab[0]);
		}
		else
			ft_putchar_count(format[i], &tab[0]);
		i++;
	}
	va_end(arg_p);
	return (tab[0]);
}
