/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:31:50 by albaur            #+#    #+#             */
/*   Updated: 2022/05/10 14:48:33 by albaur           ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->check);
	philo->data->phis[id - 1] = action;
	if (action == TOOKFORK)
		printf("\x1B[35m%lli %i has taken a fork\x1B[0m\n", get_time(philo), id);
	else if (action == EATING)
		printf("\x1B[32m%lli %i is eating\x1B[0m\n", get_time(philo), id);
	else if (action == SLEEPING)
		printf("\x1B[36m%lli %i is sleeping\x1B[0m\n", get_time(philo), id);
	else if (action == THINKING)
		printf("\x1B[33m%lli %i is thinking\x1B[0m\n", get_time(philo), id);
	pthread_mutex_unlock(&philo->data->check);
}

int	philosopher_dead(t_philo *philo, int id)
{
	if ((philo->data->phis[id - 1] != EATING && get_time_meal(philo, id))
		|| philo->data->nb == 1)
	{
		pthread_mutex_lock(&philo->data->check);
		printf("\x1B[31m%lli %i died.\x1B[0m\n", get_time(philo), id);
		philo->data->alive--;
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	return (0);
}

void	philosopher_eat(t_philo *philo, int id)
{
	if (id == 1 || id == philo->data->nb)
		pthread_mutex_lock(&philo->data->forks[philo->data->nb - 1]);
	else
		pthread_mutex_lock(&philo->data->forks[id - 2]);
	philosopher_status(philo, id, TOOKFORK);
	if (id == 1 || id == philo->data->nb)
		pthread_mutex_lock(&philo->data->forks[0]);
	else
		pthread_mutex_lock(&philo->data->forks[id - 1]);
	philosopher_status(philo, id, TOOKFORK);
	philosopher_status(philo, id, EATING);
	philo->data->meal[id - 1] = get_time(philo);
	usleep(philo->data->t_eat * 1000);
	if (id == 1 || id == philo->data->nb)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->data->nb - 1]);
		pthread_mutex_unlock(&philo->data->forks[0]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[id - 2]);
		pthread_mutex_unlock(&philo->data->forks[id - 1]);
	}
}
