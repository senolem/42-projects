/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:16:31 by albaur            #+#    #+#             */
/*   Updated: 2023/02/15 15:16:31 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(int argc, char **argv)
{
	if (argc == 1 || argc == 2)
	{
		ConfigParser	config;

		if (argc == 1)
			config.init("conf/default.conf");
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