/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:26 by faventur          #+#    #+#             */
/*   Updated: 2022/06/26 16:12:22 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	fpf_check(va_list arg_p, t_tools var, const char *format, int i)
{
	if (format[i] == '%')
		fpf_putchar_count('%', var);
	else if (format[i] == 'c')
		fpf_putchar_count(va_arg(arg_p, int), var);
	else if (format[i] == 'd' || format[i] == 'i')
		fpf_putnbr_count(va_arg(arg_p, int), "0123456789", var);
	else if (format[i] == 's')
		fpf_putstr_count(va_arg(arg_p, char *), var);
	else if (format[i] == 'o')
		fpf_putoctals_count(va_arg(arg_p, int), "01234567", var);
	else if (format[i] == 'u')
		fpf_put_unsigned(va_arg(arg_p, int), "0123456789", var);
	else if (format[i] == 'x')
		fpf_puthexa(va_arg(arg_p, unsigned int), "0123456789abcdef", var);
	else if (format[i] == 'X')
		fpf_puthexa(va_arg(arg_p, unsigned int), "0123456789ABCDEF", var);
	else if (format[i] == 'p')
		fpf_putaddr_count(va_arg(arg_p, unsigned long long), var);
	else
		fpf_putchar_count(format[i], var);
	return (*var.n_char);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	arg_p;
	t_tools	var;
	int		i;

	if (fd >= 0)
	{
		var.fd = fd;
		var.n_char[0] = 0;
		i = 0;
		va_start(arg_p, format);
		while (format[i] != '\0')
		{
			if (format[i] == '%')
			{
				i++;
				fpf_check(arg_p, var, format, i);
			}
			else
				fpf_putchar_count(format[i], var);
			i++;
		}
		va_end(arg_p);
		return (var.n_char[0]);
	}
	return (-1);
}
