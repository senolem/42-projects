/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 04:32:56 by albaur            #+#    #+#             */
/*   Updated: 2022/05/11 04:43:46 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	a;
	int	b;
	if (argc != 4)
	{
		write(1, "\n", 1);
		return (0);	
	}
	a = atoi(argv[1]);
	b = atoi(argv[3]);
	if (argv[2][0] == '+')
		printf("%i\n", a + b);
	else if (argv[2][0] == '-')
		printf("%i\n", a - b);
	else if (argv[2][0] == '*')
		printf("%i\n", a * b);
	else if (argv[2][0] == '/')
		printf("%i\n", a / b);
	else if (argv[2][0] == '%')
		printf("%i\n", a % b);
}