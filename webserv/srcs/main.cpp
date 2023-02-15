/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:16:31 by albaur            #+#    #+#             */
/*   Updated: 2023/02/15 18:54:06 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(int argc, char **argv)
{
	if (argc == 1 || argc == 2)
	{
		ConfigParser	config;

		if (argc == 1)
		{
			std::cout << "No config file provided. Using default: conf/default.conf" << std::endl;
			config.init("conf/default.conf");
		}
		else
			config.init(argv[1]);
	}
	else
	{
		std::cerr << "Invalid arguments. Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}
	return (0);
}