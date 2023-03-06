/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:14:19 by albaur            #+#    #+#             */
/*   Updated: 2023/03/06 16:20:27 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	set_time(t_data *data, bool mode)
{
	if (!mode)
		data->now = std::chrono::high_resolution_clock::now();
	else
		data->after = std::chrono::high_resolution_clock::now();
}

void	print_time(t_data *data)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
}
