/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 09:16:15 by albaur            #+#    #+#             */
/*   Updated: 2021/11/19 09:24:45 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_atoi_base(char *str, char *base);

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_check_base(char *base)
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

int		ft_find_base(char ch, char *base)
{
	int count;

	count = 0;
	while (base[count] != '\0')
	{
		if (ch == base[count])
			return (count);
		count++;
	}
	return (-1);
}

int		ft_atoi_base(char *str, char *base)
{
  int number;
	int baselength;
	int sign;
  int i;

  i = 0;
	sign = 1;
	if (!ft_check_base(base))
		return (0);
    while (str[i] == '+' || str[i] == '-')
  	{
  		if (str[i] == '-')
  			sign *= -1;
  		i++;
  	}
	baselength = ft_strlen(base);
	number = 0;
	while (*str != '\0')
	{
		number *= baselength;
		if (ft_find_base(*str, base) == -1)
			return (0);
		number += (ft_find_base(*str, base));
		str++;
	}
	return (number * sign);
}
