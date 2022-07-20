/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:10:21 by albaur            #+#    #+#             */
/*   Updated: 2022/06/23 11:40:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int ft_putstr(char *str)
{
	int i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		++i;
	}
	return (i);
}

int	ft_hexlen(unsigned int nb)
{
	int len;

	len = 0;
	while (nb != 0)
	{
		nb = nb / 16;
		++len;
	}
	return (len);
}

int	ft_itohex(unsigned int nb, char c)
{
	if (nb >= 16)
	{
		ft_itohex(nb / 16, c);
		ft_itohex(nb % 16, c);
	}
	else
	{
		if (nb <= 9)
			ft_putchar(nb + '0');
		else
		{
			if (c == 'x')
				ft_putchar(nb - 10 + 'a');
			if (c == 'X')
				ft_putchar(nb - 10 + 'A');
		}
	}
	return (1);
}

int	ft_puthex(unsigned int nb, char c)
{
	if (nb == 0)
		ft_putchar('0');
	else
		ft_itohex(nb, c);
	return (ft_hexlen(nb));
}

int	ft_intlen(int nb)
{
	int len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		++len;
		nb = nb * 1;
	}
	while (nb)
	{
		nb = nb / 10;
		++len;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*str;

	nb = n;
	i = ft_intlen(nb);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i--] = 0;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb)
	{
		str[i] = '0' + (nb % 10);
		nb = nb / 10;
		--i;
	}
	return (str);
}

int	ft_putnbr(int nb)
{
	int		i;
	char	*str;
	
	i = 0;
	str = ft_itoa(nb);
	i = ft_putstr(str);
	return (i);
}

int	ft_format(char c, va_list list)
{
	int len;

	len = 0;
	if (c == 's')
		len += ft_putstr(va_arg(list, char *));
	else if (c == 'd')
		len += ft_putnbr(va_arg(list, int));
	else if (c == 'x')
		len += ft_puthex(va_arg(list, unsigned int), c);
	return (len);
}

int	ft_printf(char	*str, ...)
{
	int		i;
	int		len;
	va_list list;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_format(str[i + 1], list);
			++i;
		}
		else
		{
			ft_putchar(str[i]);
		}
		++i;
	}
	va_end(list);
	return (len);
}

int	main(void)
{
	ft_printf("salut %s %d %x\n", "bonjouuuur", -448684, 0);
}