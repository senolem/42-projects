/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacktablen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:59:42 by albaur            #+#    #+#             */
/*   Updated: 2022/07/20 15:00:43 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

int	ft_stacktablen(t_stack **stack)
{
	size_t	len;

	len = 0;
	while (stack[len])
		++len;
	return (len);
}
