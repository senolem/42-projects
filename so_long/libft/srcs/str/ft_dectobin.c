/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectobin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:45:25 by albaur            #+#    #+#             */
/*   Updated: 2022/04/08 18:14:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_dectobin(long long nb)
{
	int			i;
	int			rem;
	long long	bin;

	bin = 0;
	rem = 1;
	i = 1;
	while (nb != 0)
	{
		rem = nb % 2;
		nb /= 2;
		bin += rem * i;
		i *= 10;
	}
	return (bin);
}
