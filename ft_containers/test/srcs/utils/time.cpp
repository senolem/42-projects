/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:14:19 by albaur            #+#    #+#             */
/*   Updated: 2023/01/25 23:53:03 by albaur           ###   ########.fr       */
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
	data->ms = data->after - data->now;
	std::cout.setf(std::ios::fixed);
	std::cout << " (" << std::setprecision(5) << data->ms.count() << "ms)";
}
