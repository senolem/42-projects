/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 00:53:56 by albaur            #+#    #+#             */
/*   Updated: 2022/05/11 00:59:50 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		write (1, "\n", 1);
		return (0);
	}
	while (argv[1][i] != ' ' && argv[1][i] != '\t' && argv[1][i] != '\0')
	{
		write(1, &argv[1][i], 1);
		++i;
	}
	write (1, "\n", 1);
	if (i == 1)
	{
		write (1, "\n", 1);
		return (0);
	}
}