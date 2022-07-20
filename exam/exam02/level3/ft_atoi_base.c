/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:01:49 by albaur            #+#    #+#             */
/*   Updated: 2022/05/19 14:30:14 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int i;
	int nb;
	int sign;

	i = 0;
	nb = 0;
	sign = -1;
	while (str[i])
	{
		nb = str[i] - '0' + (nb * 10);
		++i;
	}
	return (nb);
}

int	check_base(const char *str)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (str[i])
	{
		j = i + 1;
		if (str[i] == '-' || str[i] == '+' || str[i] < 32 || str[i] > 126)
			return (-1);
		while (str[j])
		{
			if (str[i] == str[j])
				return (-1);
			++j;
		}
		++i;
	}
	if (i < 2 || i > 16)
		return (-1);
	return (1);
}

int	ft_find_base(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		++i;
	}
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int i;
	int len;
	int sign;
	int nb;

	i = 0;
	len = 0;
	sign = 1;
	nb = 0;
	if (!check_base(str))
		return (0);
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
	}
	while (str[len])
		++len;
	while (str[i])
	{
		nb *= len;
		if (!ft_find_base(str, str_base))
			return (0);
		nb += (ft_find_base(str, str_base));
		++i;
	}
	return (nb * sign);
}