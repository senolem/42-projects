/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 02:59:11 by albaur            #+#    #+#             */
/*   Updated: 2022/05/11 03:08:36 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 4 || ft_strlen(argv[2]) > 1 || ft_strlen(argv[3]) > 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (argv[1][i])
	{
		if (argv[1][i] == argv[2][0])
			write(1, &argv[3][0], 1);
		else
			write(1, &argv[1][i], 1);
		++i;
	}
	write(1, "\n", 1);
}