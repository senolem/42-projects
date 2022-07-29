/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_q_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:41:38 by faventur          #+#    #+#             */
/*   Updated: 2022/05/03 17:52:48 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queues.h"

void	ft_q_iter(t_queue *suite, void (*f)(void *))
{
	t_qelem	*current;

	if (!suite || !f)
		return ;
	current = suite->begin;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
}
