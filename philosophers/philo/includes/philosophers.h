/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:51:27 by albaur            #+#    #+#             */
/*   Updated: 2022/05/10 11:10:21 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>

# define TOOKFORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DEAD 5

typedef struct s_data
{
	int				*phis;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check;
	pthread_mutex_t	dead;
	pthread_t		*threads;
	long long		*meal;
	long long		runtime;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				c_eat;
	int				id;
	int				nb;
	int				alive;
	int				eatmode;
}		t_data;

typedef struct s_philo
{
	struct timeval	tv;
	struct s_data	*data;
}		t_philo;

// checks
int			sanity_check(char **argv);

// init
int			philosopher_init(int argc, char **argv, t_philo *philo);

// algo
void		*philosopher_manage(void *philo);
void		philosopher_routine(t_philo *philo, int id);
void		philosopher_status(t_philo *philo, int id, int action);
void		philosopher_eat(t_philo *philo, int id);
int			philosopher_dead(t_philo *philo, int id);

// utils
long long	get_time(t_philo *philo);
long long	get_time_meal(t_philo *philo, int id);
int			ft_atoi(const char *str);
void		philosopher_free(t_philo *philo);

#endif