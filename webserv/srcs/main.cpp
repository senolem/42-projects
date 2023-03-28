/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:16:31 by albaur            #+#    #+#             */
/*   Updated: 2023/03/28 16:08:50 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "ConfigParser.hpp"

int	main(int argc, char **argv)
{
	if (argc == 1 || argc == 2)
	{
		ConfigParser										config;
		std::vector<std::multimap<std::string, t_route> >	*vhosts;
		try
		{	
			if (argc == 1)
			{
				std::cout << BLUE + INFO + GREEN + WEBSERV + NONE << " No configuration file provided. Using default: conf/default.conf\n";
				vhosts = config.init("conf/default.conf");
				if (vhosts)
				{
					webserv	webserv(vhosts);
					//webserv.printConfig();
					webserv.startServer();
					delete vhosts;
				}
			}
			else
			{
				vhosts = config.init(argv[1]);
				if (vhosts)
				{
					webserv	webserv(vhosts);
					//webserv.printConfig();
					webserv.startServer();
					delete vhosts;
				}
			}
		}
		catch(const Exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	else
	{
		std::cerr << "Invalid arguments. Usage: ./webserv [configuration file]\n";
		return (1);
	}
	return (0);
}