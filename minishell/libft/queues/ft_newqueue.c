/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newqueue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:06:06 by faventur          #+#    #+#             */
/*   Updated: 2022/05/03 18:29:36 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_newqueue() function allocates (with malloc(3)) and returns a
** new "fresh" queue. The "begin" and "end" variables are set to
** NULL.
*/

#include "queues.h"

t_queue	*ft_newqueue(void)
{
	t_queue	*new;

	new = malloc(sizeof(*new));
	if (new != NULL)
	{
		new->length = 0;
		new->begin = NULL;
		new->end = NULL;
	}
	return (new);
}
