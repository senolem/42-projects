/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:33:09 by faventur          #+#    #+#             */
/*   Updated: 2022/05/03 19:29:10 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_enqueue() function adds an element at the end of the queue.
** It returns 0 if the operation succeeds, -1 if it doesn't.
*/

#include "queues.h"

int	ft_enqueue(t_queue *suite, t_qelem *elem)
{
	if (suite && elem)
	{
		if (suite->length == 0)
			suite->begin = elem;
		else
			suite->end->next = elem;
		suite->end = elem;
		suite->length++;
		return (0);
	}
	return (-1);
}
