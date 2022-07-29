/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_q_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:25:57 by faventur          #+#    #+#             */
/*   Updated: 2022/05/03 16:30:46 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queues.h"

void	ft_q_init(t_queue *suite)
{
	if (suite)
	{
		suite->begin = NULL;
		suite->end = NULL;
		suite->length = 0;
	}
}
