/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacknew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:06:06 by faventur          #+#    #+#             */
/*   Updated: 2022/04/18 17:08:30 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_stacknew() function allocates (with malloc(3)) and returns a
** new "fresh" stack. The "top" and "bottom" variables are set to
** NULL.
*/

#include "stacks.h"

t_stack	*ft_stacknew(void)
{
	t_stack	*new;

	new = malloc(sizeof(*new));
	if (new != NULL)
	{
		new->length = 0;
		new->top = NULL;
		new->bottom = NULL;
	}
	return (new);
}
