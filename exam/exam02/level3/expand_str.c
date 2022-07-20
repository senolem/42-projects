/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:26:59 by albaur            #+#    #+#             */
/*   Updated: 2022/05/19 10:28:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	int j;
	int k;
	int len;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	if (argc == 2)
	{
		while (argv[1][len])
			++len;
		while (argv[1][i])
		{
			if (argv[1][i] > 32 && argv[1][i] <= 127)
			{
				while (argv[1][i] > 32 && argv[1][i] <= 127 && i < len)
				{
					write(1, &argv[1][i], 1);
					++i;
				}
				j = i;
				while (argv[1][j])
				{
					if (argv[1][j] > 32 && argv[1][j] <= 127)
						++k;
					++j;
				}
				if (k != 0)
					write(1, "   ", 3);
				k = 0;
			}
			++i;
		}
	}
	write(1, "\n", 1);
}