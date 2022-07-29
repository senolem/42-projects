/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequeue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:14:52 by faventur          #+#    #+#             */
/*   Updated: 2022/05/03 17:32:41 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queues.h"

/*
** The ft_dequeue() function suppresses the first element of the queue by
** freeing its memory with the del function and free(3).
** It returns 0 if the operation succeeds, -1 if it doesn't.
*/

int	ft_dequeue(t_queue *suite, void (*del)(void *))
{
	t_qelem	*delenda;

	if (suite && suite->length > 0 && del)
	{
		delenda = suite->begin;
		suite->begin = suite->begin->next;
		del(delenda->content);
		free(delenda);
		suite->length--;
		return (0);
	}
	return (-1);
}
