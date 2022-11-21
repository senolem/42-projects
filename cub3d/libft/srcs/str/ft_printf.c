/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:43:07 by albaur            #+#    #+#             */
/*   Updated: 2022/03/24 15:48:33 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format(const char format, va_list vargs)
{
	int	i;

	i = 0;
	if (format == 'c')
		i += ft_putchar(va_arg(vargs, int));
	else if (format == 's')
		i += ft_putstr(va_arg(vargs, char *));
	else if (format == 'p')
		i += ft_putptr(va_arg(vargs, unsigned long long));
	else if (format == 'i' || format == 'd')
		i += ft_putnbr(va_arg(vargs, int));
	else if (format == 'u')
		i += ft_putint_unsigned(va_arg(vargs, unsigned int));
	else if (format == 'x' || format == 'X')
		i += ft_itohex(va_arg(vargs, unsigned int), format);
	else if (format == '%')
		i += ft_putchar('%');
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		length;
	va_list	vargs;

	i = 0;
	length = 0;
	va_start(vargs, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			length += ft_format(format[i + 1], vargs);
			i++;
		}
		else
			length += ft_putchar(format[i]);
		i++;
	}
	va_end(vargs);
	return (length);
}
