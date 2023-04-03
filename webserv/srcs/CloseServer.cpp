/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CloseServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:47:00 by melones           #+#    #+#             */
/*   Updated: 2023/04/03 11:20:08 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void	close_server(int sig, siginfo_t *info, void *context)
{
	extern t_close_server	close_server_;
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		for (std::map<int, int>::iterator iter = close_server_.active_connections->begin(); iter != close_server_.active_connections->end(); iter++)
			close(iter->first);
		delete close_server_.vhosts;
		std::cout << "\rClosing Webserv...\n";
		exit(0);
	}
}