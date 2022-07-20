/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:14:11 by albaur            #+#    #+#             */
/*   Updated: 2021/11/19 09:12:42 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_base(char *base)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	len = ft_strlen(base);
	if (len == 0 || len == 1)
		return (0);
	while (base[i])
	{
		j = i + 1;
		if (base[i] == '-' || base[i] == '+' || base[i] < 32 || base[i] > 126)
			return (0);
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	convert_base(long int num, char *base)
{
	long int	len;

	len = ft_strlen(base);
	if (num >= len)
		convert_base(num / len, base);
	ft_putchar(base[num % len]);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long int	nbr2;

	nbr2 = nbr;
	if (check_base(base))
	{
		if (nbr < 0)
		{
			write(1, "-", 1);
			nbr2 = -nbr2;
		}
		convert_base(nbr2, base);
	}
}
