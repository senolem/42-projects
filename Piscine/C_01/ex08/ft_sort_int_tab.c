/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 12:16:51 by albaur            #+#    #+#             */
/*   Updated: 2021/11/15 10:29:27 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *tab, int size);

void	ft_sort_int_tab(int *tab, int size)
{
	int		index;
	int		copy;

	index = 0;
	while (index < size - 1)
	{
		if (tab[index] > tab[index + 1])
		{
			copy = tab[index];
			tab[index] = tab[index + 1];
			tab[index + 1] = copy;
			index = -1;
		}
		index++;
	}
}
