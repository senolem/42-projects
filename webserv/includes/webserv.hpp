/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:21:31 by albaur            #+#    #+#             */
/*   Updated: 2023/04/07 14:07:45 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# define BUFFER_SIZE 8192
# define MAX_REQUEST_SIZE_PROTECTION 0
# define MAX_CLIENTS_PER_SOCKET 1000
# define CLIENT_TIMEOUT 30
# define PRINT_REQUESTS 1
# define LOG_REQUEST_LENGTH_LIMIT -1
# define PRINT_REQUEST_LENGTH_LIMIT 512
# include <iostream>
# include <string>
# include <cstring>
# include <vector>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <map>
# include <ctime>
# include <set>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <netinet/in.h>
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
# include <signal.h>
# include "Output.hpp"
# include "Structures.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "utils.hpp"
# include "CloseServer.hpp"

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

		void												initSockets(void);
		t_socket											createSocket(int port);
		void												handleSocketsRead(Client *client, std::vector<Server>::iterator iter);
		void												handleSocketsWrite(Client *client, std::vector<Server>::iterator iter);
		void												startServer(void);
		void												checkHangingClients(void);
		int													removeClient(Client *client, std::vector<Server>::iterator	&iter, std::vector<Client*>::iterator &iter3, std::vector<Client*>::iterator &iter4);
		vectorIterator										getHost(const std::string &host);
		std::string											resolveHost(const std::string &host);
		std::vector<std::multimap<std::string, t_route> >	&getVirtualHosts(void);
		int													getMaxFd(void);
		void												printConfig(void);
};

#endif