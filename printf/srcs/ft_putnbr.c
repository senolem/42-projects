/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 09:43:41 by albaur            #+#    #+#             */
/*   Updated: 2022/03/16 11:40:37 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putnbr(int nb)
{
	int		i;
	char	*str;

	str = ft_itoa(nb);
	i = ft_putstr(str);
	free(str);
	return (i);
}
