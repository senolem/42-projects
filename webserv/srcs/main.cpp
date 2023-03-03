/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:16:31 by albaur            #+#    #+#             */
/*   Updated: 2023/03/03 12:04:39 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "ConfigParser.hpp"

int	main(int argc, char **argv)
{
	if (argc == 1 || argc == 2)
	{
		ft::ConfigParser									config;
		std::vector<std::multimap<std::string, t_route> >	*vhosts;

		if (argc == 1)
		{
			std::cout << "No config file provided. Using default: conf/default.conf" << std::endl;
			vhosts = config.init("conf/default.conf");
			if (vhosts)
			{
				webserv	webserv(vhosts);
				webserv.startServer();
			}
		}
		else
		{
			vhosts = config.init(argv[1]);
			if (vhosts)
			{
				webserv	webserv(vhosts);
				webserv.startServer();
			}
		}
	}
	else
	{
		std::cerr << "Invalid arguments. Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}
	return (0);
}