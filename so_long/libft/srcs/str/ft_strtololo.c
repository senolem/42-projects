/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtololo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:13:25 by albaur            #+#    #+#             */
/*   Updated: 2022/03/31 10:16:27 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strtololo(const char *str)
{
	int			i;
	long long	rt;
	int			pm;

	rt = 0;
	i = 0;
	pm = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			pm *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rt = rt * 10 + (str[i] - 48);
		if (rt * pm > 2147483647)
			return (0);
		else if (rt * pm < -2147483648)
			return (0);
		i++;
	}
	return (1);
}
