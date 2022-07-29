/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacktab_clear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:39:54 by faventur          #+#    #+#             */
/*   Updated: 2022/07/18 18:44:17 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_stacktab_clear(t_stack **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		ft_stack_freer(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
