/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:31:50 by albaur            #+#    #+#             */
/*   Updated: 2022/05/10 15:20:29 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philosopher_routine(t_philo *philo, int id)
{
	if (philosopher_dead(philo, id))
		return ;
	philosopher_eat(philo, id);
	if (philosopher_dead(philo, id))
		return ;
	philosopher_status(philo, id, SLEEPING);
	usleep(philo->data->t_sleep * 1000);
	if (philosopher_dead(philo, id))
		return ;
	philosopher_status(philo, id, THINKING);
}

void	philosopher_status(t_philo *philo, int id, int action)
{
	sem_wait(philo->data->check);
	philo->data->phis[id - 1] = action;
	if (action == TOOKFORK)
		printf("\x1B[35m%lli %i has taken a fork\x1B[0m\n", get_time(philo), id);
	else if (action == EATING)
		printf("\x1B[32m%lli %i is eating\x1B[0m\n", get_time(philo), id);
	else if (action == SLEEPING)
		printf("\x1B[36m%lli %i is sleeping\x1B[0m\n", get_time(philo), id);
	else if (action == THINKING)
		printf("\x1B[33m%lli %i is thinking\x1B[0m\n", get_time(philo), id);
	sem_post(philo->data->check);
}

int	philosopher_dead(t_philo *philo, int id)
{
	if ((philo->data->phis[id - 1] != EATING && get_time_meal(philo, id))
		|| philo->data->nb == 1)
	{
		sem_wait(philo->data->check);
		printf("\x1B[31m%lli %i died.\x1B[0m\n", get_time(philo), id);
		philo->data->alive--;
		sem_post(philo->data->dead);
		return (1);
	}
	return (0);
}

void	philosopher_eat(t_philo *philo, int id)
{
	sem_wait(philo->data->forks);
	philosopher_status(philo, id, TOOKFORK);
	sem_wait(philo->data->forks);
	philosopher_status(philo, id, TOOKFORK);
	philosopher_status(philo, id, EATING);
	philo->data->meal[id - 1] = get_time(philo);
	usleep(philo->data->t_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*wait_pid_end(void *philo)
{
	int		i;
	t_philo	*ptr;

	i = 0;
	ptr = philo;
	while (i < ptr->data->nb)
	{
		waitpid(ptr->data->pid[i], NULL, 0);
		++i;
	}
	exit(0);
}
