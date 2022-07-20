/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:34:06 by albaur            #+#    #+#             */
/*   Updated: 2022/05/10 15:55:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// utils

long long	get_time(t_philo *philo)
{
	long long	ms;

	gettimeofday(&philo->tv, NULL);
	ms = philo->tv.tv_sec * (uint64_t)1000 + (philo->tv.tv_usec / 1000);
	return ((ms - philo->data->runtime));
}

long long	get_time_meal(t_philo *philo, int id)
{
	if (get_time(philo) - philo->data->meal[id - 1] > philo->data->t_die)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	toreturn;

	i = 0;
	sign = 1;
	toreturn = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		if (toreturn * sign > 2147483647)
			return (-1);
		else if (toreturn * sign < -2147483648)
			return (0);
		toreturn = (str[i] - '0') + (toreturn * 10);
		i++;
	}
	return (toreturn * sign);
}

void	philosopher_free(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->data->check);
	pthread_mutex_destroy(&philo->data->dead);
	while (i < philo->data->nb)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		++i;
	}
	free(philo->data->threads);
	free(philo->data->forks);
	free(philo->data->phis);
	free(philo->data->meal);
	free(philo->data);
}

// main

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
	{
		printf("\x1B[31mError : Incorrect arguments count.\n");
		return (0);
	}
	if (!(sanity_check(argv)))
		return (0);
	if (!(philosopher_init(argc, argv, &philo)))
	{
		write(2, "\x1B[31mMalloc error\n", 18);
		return (0);
	}
	pthread_mutex_lock(&philo.data->dead);
	pthread_mutex_unlock(&philo.data->dead);
	philosopher_free(&philo);
	return (0);
}
