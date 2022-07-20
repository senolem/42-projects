/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:04:53 by albaur            #+#    #+#             */
/*   Updated: 2022/05/12 13:28:30 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_isprime(int nb)
{
	int i;

	i = 2;
	while (i <= nb / 2)
	{
		if (nb % i == 0)
			return (0);
		++i;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = str[i] - '0' + (nb * 10);
		++i;
	}
	return (nb);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

int	main(int argc, char **argv)
{
	int i;
	int nb;
	int result;

	if (argc != 2 || argv[1][0] == '-')
	{
		write(1, "0\n", 2);
		return (0);
	}
	i = 0;
	nb = ft_atoi(argv[1]);
	result = 0;
	while (nb > 1)
	{
		if (ft_isprime(nb))
			result += nb;
		nb--;
	}
	ft_putnbr(result);
	write(1, "\n", 1);
}