/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:16:31 by albaur            #+#    #+#             */
/*   Updated: 2023/04/03 10:59:42 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "ConfigParser.hpp"

t_close_server	close_server_;

int	main(int argc, char **argv)
{
	if (argc == 1 || argc == 2)
	{
		ConfigParser										config;
		std::vector<std::multimap<std::string, t_route> >	*vhosts;
		struct sigaction									sa;
		try
		{
			sa.sa_sigaction = close_server;
			sigemptyset(&sa.sa_mask);
			sa.sa_flags = SA_SIGINFO;
			if (sigaction(SIGINT, &sa, NULL) == -1)
				throw Exception(RED + ERROR + CYAN + WEBSERV + NONE + " Failed register signal handler");
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