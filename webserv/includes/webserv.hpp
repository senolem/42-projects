/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:21:31 by albaur            #+#    #+#             */
/*   Updated: 2023/03/17 11:48:17 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# define BUFFER_SIZE 65536
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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <dirent.h>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <map>
# include "Structures.hpp"
# include "Server.hpp"
# include "utils.hpp"
# include "Output.hpp"

class Server;
class webserv
{
	private:
		std::vector<Server>									_subservers;
		std::vector<std::multimap<std::string, t_route> >	*_vhosts;
		size_t												_nb_vhost;
		std::map<int, t_socket>								_sockets;
		fd_set												_read_fds;
		fd_set												_write_fds;
		fd_set												_read_fds_bak;
		fd_set												_write_fds_bak;
		std::map<int, int>									_activeConnections;
	
	public:
		typedef std::map<std::string, t_route>::iterator					mapIterator;
		typedef std::vector<std::multimap<std::string, t_route> >::iterator	vectorIterator;

		webserv(std::vector<std::multimap<std::string, t_route> > *src);
		webserv(const webserv &src);
		~webserv(void);
		webserv	&operator=(const webserv &src);

		void													startServer(void);
		t_socket												createSocket(int port);
		vectorIterator											getHost(std::string host);
		std::string												resolveHost(std::string host);
		void													printConfig(void);
		std::vector<std::multimap<std::string, t_route> >		&getVirtualHosts(void);
		int														getMaxFd(void);
};

#endif