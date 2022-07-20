/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:36:36 by albaur            #+#    #+#             */
/*   Updated: 2022/05/10 15:57:35 by albaur           ###   ########.fr       */
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
	philo->data->pid = malloc(sizeof(pid_t) * philo->data->nb);
	if (!philo->data->phis || !philo->data->meal || !philo->data->pid)
		return (0);
	memset(philo->data->phis, 0, sizeof(int) * philo->data->nb);
	memset(philo->data->meal, 0, sizeof(long long) * philo->data->nb);
	memset(philo->data->pid, 0, sizeof(pid_t) * philo->data->nb);
	return (1);
}

static int	init_semaphore(t_philo *philo, int nb)
{
	sem_unlink("forks");
	sem_unlink("check");
	sem_unlink("dead");
	philo->data->forks = sem_open("forks", O_CREAT, 0644, nb);
	philo->data->check = sem_open("check", O_CREAT, 0644, 1);
	philo->data->dead = sem_open("dead", O_CREAT, 0644, 0);
	return (1);
}

static int	init_processes(t_philo *philo, int nb)
{
	int			i;
	pthread_t	tid;

	i = 0;
	while (i < nb)
	{
		philo->data->pid[i] = fork();
		if (!philo->data->pid[i])
		{
			philosopher_manage(philo);
			exit (0);
		}
		if (i % 2 == 0)
			usleep(500);
		++philo->data->id;
		++i;
	}
	pthread_create(&tid, NULL, wait_pid_end, philo);
	pthread_detach(tid);
	return (1);
}

int	philosopher_init(int argc, char **argv, t_philo *philo)
{
	int	nb;

	if (!(init_data(argc, argv, philo)))
		return (0);
	nb = philo->data->nb;
	philo->data->runtime = get_time(philo);
	if (!(init_semaphore(philo, nb) && init_processes(philo, nb)))
		return (0);
	return (1);
}

void	philosopher_manage(t_philo *philo)
{
	int			id;
	int			n;

	id = philo->data->id;
	philo->data->meal[id - 1] = get_time(philo);
	n = philo->data->n_eat;
	while (philo->data->alive == philo->data->nb)
	{
		philosopher_routine(philo, id);
		if (philo->data->eatmode == 1)
		{
			--n;
			if (n == 0)
				exit (0);
		}
	}
}
