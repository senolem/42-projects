/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:14:51 by albaur            #+#    #+#             */
/*   Updated: 2022/05/18 09:30:17 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	*array;
	int size;

	size = start;
	while (size < end)
	{
		++size;
	}
	array = malloc(sizeof(int) * size);
	printf("%i\n", size);
	size = 0;
	while (size < end)
	{
		array[size] = start + size;
		++size;
	}
	return (array);
}

int	main(void)
{
	int i;
	int *array;
	i = 0;
	array = ft_range(0, 0);
	while (i < 3)
		printf("%i\n", array[i++]);

}