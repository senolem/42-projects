/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 01:28:42 by albaur            #+#    #+#             */
/*   Updated: 2022/05/11 01:50:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	n;

	i = 0;
	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (argv[1][i])
	{
		n = 0;
		if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
		{
			n = argv[1][i] - 65;
			while (n >= 0)
			{
				write(1, &argv[1][i], 1);
				--n;
			}
		}
		else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
		{
			n = argv[1][i] - 97;
			while (n >= 0)
			{
				write(1, &argv[1][i], 1);
				--n;
			}
		}
		else
			write(1, &argv[1][i], 1);
		++i;
	}
	write(1, "\n", 1);
}