/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:53:22 by melones           #+#    #+#             */
/*   Updated: 2023/03/29 18:29:30 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

webserv::webserv(std::vector<std::multimap<std::string, t_route> > *src) : _vhosts(src), _nb_vhost(_vhosts->size())
{
	FD_ZERO(&_read_fds);
	FD_ZERO(&_write_fds);
	FD_ZERO(&_read_fds_bak);
	FD_ZERO(&_write_fds_bak);
}

webserv::webserv(const webserv &src) : _subservers(src._subservers), _vhosts(src._vhosts), _nb_vhost(src._nb_vhost), _sockets(src._sockets), _read_fds(src._read_fds), _write_fds(src._write_fds_bak), _read_fds_bak(src._read_fds_bak), _write_fds_bak(src._write_fds_bak), _activeConnections(src._activeConnections)
{
	*this = src;
}

webserv::~webserv(void)
{
	delete _vhosts;
	for (size_t i = 0; _sockets.size(); i++)
		close(_sockets[i].fd);
}

webserv	&webserv::operator=(const webserv &src)
{
	if (this != &src)
	{
		_subservers = src._subservers;
		_vhosts = src._vhosts;
		_nb_vhost = src._nb_vhost;
		_sockets = src._sockets;
		_read_fds = src._read_fds;
		_write_fds = src._write_fds_bak;
		_read_fds_bak = src._read_fds_bak;
		_write_fds_bak = src._write_fds_bak;
		_activeConnections = src._activeConnections;
	}
	return (*this);
}

void	webserv::startServer(void)
{
	int								status = 0; 
	std::vector<Server>::iterator	iter;
	std::vector<Server>::iterator	iter2;
	std::vector<Client*>::iterator	iter3;
	std::vector<Client*>::iterator	iter4;
	int								client_fd;

	for (size_t i = 0; i < _nb_vhost; i++)
	{
		std::map<int, t_socket>::iterator	iter;
		int									port = atoi(_vhosts->at(i).begin()->second.listen.c_str());
		
		iter = _sockets.find(port);
		if (iter == _sockets.end())
		{
			_sockets.insert(std::pair<int, t_socket>(port, createSocket(port)));
			iter = _sockets.find(port);
			FD_SET(iter->second.fd, &_read_fds_bak);
			_activeConnections[iter->second.fd] = 1;
		}
		_subservers.push_back(Server(*this, _vhosts->at(i), iter->second));
	}
	std::cout << BLUE << INFO << CYAN << WEBSERV << NONE << " Waiting for connection...\n";
	while (1)
	{
		_read_fds = _read_fds_bak;
		_write_fds = _write_fds_bak;
		status = select(getMaxFd() + 1, &_read_fds, &_write_fds, NULL, NULL);
		if (status == -1)
			throw Exception(RED + ERROR + CYAN + WEBSERV + NONE + " Failed to select");
		else
		{
			iter = _subservers.begin();
			iter2 = _subservers.end();
			while (iter != iter2)
			{
				if (FD_ISSET(iter->getSocket().fd, &_read_fds))
				{
					client_fd = iter->newConnection();
					_activeConnections[client_fd] = 1;
					FD_SET(client_fd, &_read_fds_bak);
				}
				iter3 = iter->getClients()->begin();
				iter4 = iter->getClients()->end();
				while (iter3 != iter4)
				{
					Client	*client = *iter3;
					if (client->isOpen() && FD_ISSET(client->getSocket().fd, &_read_fds))
					{
						int	ret = client->getRequest();
						if (ret == 0)
							FD_SET(client->getSocket().fd, &_read_fds_bak);
						else if (ret == 1)
							FD_SET(client->getSocket().fd, &_write_fds_bak);
						else if (ret == -1)
							std::cout << RED << ERROR << CYAN << WEBSERV << NONE << " Failed to read request from client " << client->getResolved() << "\n";
						else if (ret == -2)
						{
							t_request	tmp;
							tmp.status = 413;
							client->setResponse(iter->getResponse(tmp));
							FD_SET(client->getSocket().fd, &_write_fds);
						}
					}
					if (client->isOpen() && FD_ISSET(client->getSocket().fd, &_write_fds))
					{
						if (client->isResponseEmpty())
							client->setResponse(iter->getResponse(client->getParsedRequest()));
						int	ret = client->sendResponse();
						if (ret == 0 && !client->isResponseEmpty())
						{
							std::cout << BLUE << INFO <<  CYAN << WEBSERV << NONE << " Response sent to client " << client->getResolved() << " (length " << client->getSent() << ")\n";
							client->setSent(0);
						}
						else if (ret == -1)
							std::cout << RED << ERROR << CYAN << WEBSERV << NONE << " Failed to send response to client " << client->getResolved() << "\n";
					}
					if (!client->isOpen())
					{
						std::cout << BLUE << INFO << CYAN << WEBSERV << NONE << " Closing connection to client " << client->getResolved() << "\n";
						FD_CLR(client->getSocket().fd, &_read_fds_bak);
						FD_CLR(client->getSocket().fd, &_write_fds_bak);
						_activeConnections.erase(client->getSocket().fd);
						delete client;
						iter->getClients()->erase(iter3);
						if (iter->getClients()->empty())
							break ;
						else
						{
							iter3 = iter->getClients()->begin();
							iter4 = iter->getClients()->end();
							continue ;
						}
					}
					++iter3;
				}
				++iter;
			}
		}
	}
}

t_socket	webserv::createSocket(int port)
{
	std::string			response;
	t_socket			_socket;
	
	_socket.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket.fd < 0)
		throw Exception(RED + ERROR + CYAN + WEBSERV + NONE + " Failed to create socket");
	_socket.sockaddr_.sin_family = AF_INET;
	_socket.sockaddr_.sin_addr.s_addr = INADDR_ANY;
	_socket.sockaddr_.sin_port = htons(port);
	memset(_socket.sockaddr_.sin_zero, 0, sizeof(_socket.sockaddr_.sin_addr));
	if (bind(_socket.fd, (sockaddr *)&_socket.sockaddr_, sizeof(_socket.sockaddr_)) < 0)
		throw Exception(RED + ERROR + CYAN + WEBSERV + NONE + " Failed to bind socket for port " + itostr(port));
	if (listen(_socket.fd, 10) < 0)
		throw Exception(RED + ERROR + CYAN + WEBSERV + NONE + " Failed to listen socket for port " + itostr(port));
	std::cout << BLUE << INFO << CYAN << WEBSERV << NONE << " Socket successfully created for port " << port << "\n";
	return (_socket);
}

webserv::vectorIterator	webserv::getHost(std::string host)
{
	vectorIterator				vect_iter = _vhosts->begin();
	vectorIterator				vect_iter2 = _vhosts->end();
	std::string					resolved = resolveHost(host);
	std::string					port;
	std::vector<std::string>	vect = split_string(host, ":");
	mapIterator					iter;
	
	if (vect.size() == 2)
		port = vect.at(1);
	else
		port = "80";
	while (vect_iter != vect_iter2)
	{
		if (resolveHost(vect_iter->begin()->second.server_name + ":" + vect_iter->begin()->second.listen) == resolved\
			&& port == vect_iter->begin()->second.listen)
			return (vect_iter);
		++vect_iter;
	}
	std::cout << RED << ERROR << CYAN << WEBSERV << NONE << " Host \"" << host << "\" did not match any of the server blocks\n";
	return (vect_iter);
}

std::string	webserv::resolveHost(std::string host)
{
	int							result = 0;
	struct addrinfo				hints, *res;
	struct sockaddr_in			*addrin;
	std::string					port;
	std::vector<std::string>	vect = split_string(host, ":");
	std::ostringstream			string_stream;
	unsigned char				*binary_ip;

	if (vect.size() == 2)
		port = vect.at(1);
	else
		port = "80";
	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	result = getaddrinfo(vect.at(0).c_str(), port.c_str(), &hints, &res);
	if (result != 0)
	{
		freeaddrinfo(res);
		throw Exception(RED + ERROR + CYAN + WEBSERV + NONE + " Failed to resolve hostname");
	}
	addrin = (struct sockaddr_in *)res->ai_addr;
	binary_ip = (unsigned char *)&addrin->sin_addr.s_addr;
	string_stream << (int)binary_ip[0] << "." << (int)binary_ip[1] << "." << (int)binary_ip[2] << "." << (int)binary_ip[3];
	freeaddrinfo(res);
	return (string_stream.str());
}

std::vector<std::multimap<std::string, t_route> >	&webserv::getVirtualHosts(void)
{
	return (*_vhosts);
}

int	webserv::getMaxFd(void)
{
	return (_activeConnections.rbegin()->first);
}

void	webserv::printConfig(void)
{
	vectorIterator	vect_iter = _vhosts->begin();
	vectorIterator	vect_iter2 = _vhosts->end();
	mapIterator		mapIter;
	mapIterator		mapIter2;
	
	while (vect_iter != vect_iter2)
	{
		std::cout << "__________________________________________________\n";
		mapIter = vect_iter->begin();
		mapIter2 = vect_iter->end();
		std::cout << "Route [" << mapIter->first << "]\n";
		while (mapIter != mapIter2)
		{
			t_route	&route = mapIter->second;
			std::cout << "type : " << (route.type ? "LOCATION":"SERVER") << "\n";
			std::cout << "listen : " << route.listen << "\n";
			std::cout << "server_name : " << route.server_name << "\n";
			std::cout << "access_log : " << route.access_log << "\n";
			std::cout << "client_max_body_size : " << route.client_max_body_size << "\n";
			std::cout << "error_page :\n";
			printIntStringMap(route.error_page);
			std::cout << "root : " << route.root << "\n";
			std::cout << "index : " << concatStringVector(route.index, " ") << "\n";
			std::cout << "methods_allowed : " << concatMethods(route.methods_allowed) << "\n";
			std::cout << "autoindex : " << (route.autoindex ? "true":"false") << "\n";
			std::cout << "cgi_pass : \n";
			printCgiMap(route.cgi_pass);
			std::cout << "upload : " << (route.upload ? "true":"false") << "\n";
			std::cout << "upload_path : " << route.upload_path << "\n";
			std::cout << "match : " << route.match << "\n";
			std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
			++mapIter;
		}
		++vect_iter;
	}
}
