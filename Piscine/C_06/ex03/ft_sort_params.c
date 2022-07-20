/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:56:55 by albaur            #+#    #+#             */
/*   Updated: 2021/11/22 20:57:48 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	result;

	result = 0;
	while ((s1[result] == s2[result])
		&& (s1[result] != '\0')
		&& (s2[result] != '\0'))
		result++;
	return (s1[result] - s2[result]);
}

void	ft_str_sort(char **arr, int size, int offset)
{
	int	index;
	int	swapped;

	index = offset;
	while (1)
	{
		index = offset;
		swapped = 0;
		while (index < size)
		{
			if (ft_strcmp(arr[index], arr[index + 1]) > 0)
			{
				ft_swap(&arr[index], &arr[index + 1]);
				swapped = 1;
			}
			index++;
		}
		if (!swapped)
			break ;
	}
}

int	main(int argc, char **argv)
{
	int	index;

	if (argc > 2)
		ft_str_sort(argv, argc - 1, 1);
	index = 0;
	while (++index < argc)
	{
		ft_putstr(argv[index]);
		ft_putstr("\n");
	}
}
