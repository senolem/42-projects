/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 12:16:51 by albaur            #+#    #+#             */
/*   Updated: 2021/11/14 20:02:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_rev_int_tab(int *tab, int size);

void	ft_rev_int_tab(int *tab, int size)
{
	int		index;
	int		copy;

	index = 0;
	while (index < size / 2)
	{
		copy = tab[index];
		tab[index] = tab[size - 1 - index];
		tab[size - 1 - index] = copy;
		index++;
	}
}
