/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanity_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:42:44 by albaur            #+#    #+#             */
/*   Updated: 2022/05/06 06:23:50 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	num_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			++j;
		}
		j = 0;
		++i;
	}
	return (1);
}

static int	min_check(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 1)
			return (0);
		++i;
	}
	return (1);
}

int	sanity_check(char **argv)
{
	if (!(num_check(argv)))
	{
		printf("\x1B[31mError : Only numbers are accepted.\n");
		return (0);
	}
	if (!(min_check(argv)))
	{
		printf("\x1B[31mError : Numbers arguments must be greater than 0.\n");
		return (0);
	}
	return (1);
}
