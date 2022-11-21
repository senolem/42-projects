/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:09:08 by albaur            #+#    #+#             */
/*   Updated: 2022/11/11 01:54:00 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLFW/glfw3.h>
#include "mlx_utils.h"

double	get_time(void)
{
	return (glfwGetTime());
}

int	get_delay(int startnow, int min)
{
	static struct timeval	start;
	static struct timeval	stop;
	unsigned long			delta;

	if (startnow)
	{
		gettimeofday(&start, NULL);
		return (0);
	}
	else
		gettimeofday(&stop, NULL);
	delta = (stop.tv_sec - start.tv_sec) * 1000000
		+ stop.tv_usec - start.tv_usec;
	if (delta < (unsigned long)min)
		usleep((min - delta) % 1000000);
	return (delta - min);
}

void	update_time(struct timeval *tv, long long *timestamp)
{
	gettimeofday(tv, NULL);
	*timestamp = tv->tv_sec * (uint64_t)1000 + (tv->tv_usec / 1000);
}
