/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ms_launch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 12:28:03 by albaur            #+#    #+#             */
/*   Updated: 2022/07/24 12:24:28 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_ms_launch(t_stack *stack)
{
	size_t	i;
	char	**str;

	i = 0;
	if (!stack)
		return ;
	str = ft_lst_to_arr(stack);
	if (!str)
		return ;
	while (str[i])
	{
		if (!ft_strnstrbool(str[i], "/minishell", ft_strlen(str[i])))
		{
			sig_toggle(2);
			ft_arr_freer(str);
			return ;
		}
		++i;
	}
	sig_toggle(1);
	ft_arr_freer(str);
}
