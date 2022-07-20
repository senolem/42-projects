/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_mirror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 04:21:16 by albaur            #+#    #+#             */
/*   Updated: 2022/05/11 04:29:56 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int		i;
	char	c;
	char	d;

	i = 0;
	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (argv[1][i])
	{
		c = 'Z' - argv[1][i] + 'A';
		d = 'z' - argv[1][i] + 'a';
		if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
			write(1, &c, 1);
		else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
			write(1, &d, 1);
		else
			write(1, &argv[1][i], 1);
		++i;
	}
	write(1, "\n", 1);
}