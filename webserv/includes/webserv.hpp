/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:21:31 by albaur            #+#    #+#             */
/*   Updated: 2023/02/25 20:50:44 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# include <iostream>
# include <string>
# include <cstring>
# include <vector>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
# include <unistd.h>
# include <string.h>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <map>
# include "Structures.hpp"
# include "Server.hpp"
# include "utils.hpp"


class Server;
class webserv
{
	private:
		std::vector<Server>									_subservers;
		std::vector<std::multimap<std::string, t_route> >	*_vhosts;
		size_t												_nb_vhost;
		std::map<int, t_socket>								_sockets;
		std::vector<pollfd>									_pollfds;
	
	public:
		typedef std::map<std::string, t_route>::iterator					mapIterator;
		typedef std::vector<std::multimap<std::string, t_route> >::iterator	vectorIterator;

		webserv(void);
		webserv(const webserv &src);
		~webserv(void);
		webserv	&operator=(const webserv &src);

		void				importConfig(std::vector<std::multimap<std::string, t_route> > *src);
		void				startServer(void);
		t_socket			createSocket(int port);
		vectorIterator		getHost(std::string host);
		std::string			getPath(vectorIterator vectIter, std::string path);
		t_request_header	parseRequest(char *buffer);
		void				printConfig(void);
};

#endif