/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queues.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:13:21 by faventur          #+#    #+#             */
/*   Updated: 2022/05/03 18:29:08 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUES_H
# define QUEUES_H

# include "libft.h"

typedef struct s_qelem
{
	void			*content;
	struct s_qelem	*next;
}					t_qelem;

typedef struct s_queue
{
	size_t			length;
	struct s_qelem	*begin;
	struct s_qelem	*end;
}					t_queue;

t_queue	*ft_newqueue(void);
t_qelem	*ft_newqelem(void *content);
void	ft_q_init(t_queue *suite);
int		ft_enqueue(t_queue *suite, t_qelem *elem);
int		ft_dequeue(t_queue *suite, void (*del)(void *));
void	ft_q_iter(t_queue *suite, void (*f)(void *));

#endif