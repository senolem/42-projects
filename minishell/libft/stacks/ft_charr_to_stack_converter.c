/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charr_to_stack_converter.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:12:30 by faventur          #+#    #+#             */
/*   Updated: 2022/07/20 10:18:20 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

t_stack	*ft_charr_to_stack_converter(char **arr)
{
	t_stack	*new;
	size_t	i;

	if (!arr || !*arr)
		return (NULL);
	i = 0;
	new = ft_stacknew();
	while (arr[i])
	{
		ft_stackadd_bottom(new, ft_newnode(arr[i]));
		i++;
	}
	return (new);
}
