/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:36:36 by albaur            #+#    #+#             */
/*   Updated: 2022/05/10 15:49:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	init_data(int argc, char **argv, t_philo *philo)
{
	philo->data = malloc(sizeof(t_data));
	if (!philo->data)
		return (0);
	memset(philo->data, 0, sizeof(t_data));
	philo->data->nb = ft_atoi(argv[1]);
	philo->data->alive = philo->data->nb;
	philo->data->id = 1;
	philo->data->t_die = ft_atoi(argv[2]);
	philo->data->t_eat = ft_atoi(argv[3]);
	philo->data->t_sleep = ft_atoi(argv[4]);
	philo->data->n_eat = 1;
	if (argc == 6)
	{
		philo->data->eatmode = 1;
		philo->data->n_eat = ft_atoi(argv[5]);
	}
	philo->data->phis = malloc(sizeof(int) * philo->data->nb);
	philo->data->meal = malloc(sizeof(long long) * philo->data->nb);
	if (!philo->data->phis || !philo->data->meal)
		return (0);
	memset(philo->data->phis, 0, sizeof(int) * philo->data->nb);
	memset(philo->data->meal, 0, sizeof(long long) * philo->data->nb);
	return (1);
}

static int	init_mutex(t_philo *philo, int nb)
{
	int	i;

	i = 0;
	philo->data->forks = malloc(sizeof(pthread_mutex_t) * philo->data->nb);
	if (!philo->data->forks)
		return (0);
	pthread_mutex_init(&philo->data->check, NULL);
	pthread_mutex_init(&philo->data->dead, NULL);
	pthread_mutex_lock(&philo->data->dead);
	while (i < nb)
	{
		pthread_mutex_init(&philo->data->forks[i], NULL);
		++i;
	}
	return (1);
}

static int	init_threads(t_philo *philo, int nb)
{
	int	i;

	i = 0;
	philo->data->threads = malloc(sizeof(pthread_t) * philo->data->nb);
	if (!philo->data->threads)
		return (0);
	while (i < nb)
	{
		pthread_create(&philo->data->threads[i], 0, philosopher_manage, philo);
		pthread_detach(philo->data->threads[i]);
		if (i % 2 == 0)
			usleep(500);
		++i;
	}
	return (1);
}

int	philosopher_init(int argc, char **argv, t_philo *philo)
{
	int	nb;

	if (!(init_data(argc, argv, philo)))
		return (0);
	nb = philo->data->nb;
	philo->data->runtime = get_time(philo);
	if (!(init_mutex(philo, nb) && init_threads(philo, nb)))
		return (0);
	return (1);
}

void	*philosopher_manage(void *philo)
{
	t_philo		*ptr;
	int			id;
	int			n;

	ptr = philo;
	id = ptr->data->id++;
	ptr->data->meal[id - 1] = get_time(ptr);
	n = ptr->data->n_eat;
	while (ptr->data->alive == ptr->data->nb)
	{
		philosopher_routine(ptr, id);
		if (ptr->data->eatmode == 1)
		{
			--n;
			if (n == 0)
			{
				++ptr->data->c_eat;
				if (ptr->data->c_eat == ptr->data->nb)
					pthread_mutex_unlock(&ptr->data->dead);
				break ;
			}
		}
	}
	return (0);
}
