/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacktablen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:59:42 by albaur            #+#    #+#             */
/*   Updated: 2022/10/11 16:42:12 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stacktablen(t_stack **stack)
{
	size_t	len;

	len = 0;
	while (stack[len])
		++len;
	return (len);
}
