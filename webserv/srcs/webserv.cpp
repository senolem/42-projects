/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:53:22 by melones           #+#    #+#             */
/*   Updated: 2023/03/05 23:58:41 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

webserv::webserv(std::vector<std::multimap<std::string, t_route> > *src) : _webserv_tag("\033[94m[webserv]\033[0m"), _error_tag("\033[31m[ERROR]\033[0m")
{
	_vhosts = src;
	_nb_vhost = _vhosts->size();
	FD_ZERO(&_read_fds);
	FD_ZERO(&_write_fds);
	FD_ZERO(&_read_fds_bak);
	FD_ZERO(&_write_fds_bak);
}

webserv::webserv(const webserv &src) : _webserv_tag("\033[94m[webserv]\033[0m"), _error_tag("\033[31m[ERROR]\033[0m")
{
	*this = src;
}

webserv::~webserv(void)
{

}

webserv	&webserv::operator=(const webserv &src)
{
	if (this != &src)
	{
		this->_vhosts = src._vhosts;
		this->_nb_vhost = _vhosts->size();
	}
	return (*this);
}

void	webserv::startServer(void)
{
	int								status = 0;  
	//struct timeval					timeout = {5, 0};
	int								max_fd = -1;
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
			FD_SET(iter->second.fd, &_read_fds);
		}
		if (iter->second.fd > max_fd)
			max_fd = iter->second.fd;
		_subservers.push_back(Server(*this, _vhosts->at(i), iter->second));
	}
	while (1)
	{
		std::cout << "Waiting for connection..." << std::endl;
		_read_fds = _read_fds_bak;
		_write_fds = _write_fds_bak;
		status = select(max_fd + 1, &_read_fds, &_write_fds, NULL, 0);
		if (status == -1)
		{
			std::cout << _webserv_tag << _error_tag << " Failed to select (" << errno << ")" << std::endl;
			exit(1);
		}
		if (status > 0)
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
					if (FD_ISSET(client->getSocket().fd, &_read_fds))
					{
						if (client->getRequest())
							FD_SET(client->getSocket().fd, &_write_fds_bak);
					}
					if (FD_ISSET(client->getSocket().fd, &_write_fds))
					{
						client->sendResponse(iter->getResponse(client->getParsedRequest()));
						FD_CLR(client->getSocket().fd, &_write_fds_bak);
					}
					++iter3;
				}
				++iter;
			}
		}
	}
	for (size_t i = 0; _sockets.size(); i++)
		close(_sockets[i].fd);
}

t_socket	webserv::createSocket(int port)
{
	std::string			response;
	t_socket			_socket;
	
	_socket.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket.fd < 0)
	{
		std::cout << _webserv_tag << _error_tag << " Failed to create socket (" << errno << ")" << std::endl;
		exit(1);
	}
	_socket.sockaddr_.sin_family = AF_INET;
	_socket.sockaddr_.sin_addr.s_addr = INADDR_ANY;
	_socket.sockaddr_.sin_port = htons(port);
	memset(_socket.sockaddr_.sin_zero, 0, sizeof(_socket.sockaddr_.sin_addr));
	if (bind(_socket.fd, (sockaddr *)&_socket.sockaddr_, sizeof(_socket.sockaddr_)) < 0)
	{
		std::cout << _webserv_tag << _error_tag << " Failed to bind socket (" << errno << ")" << std::endl;
		exit(1);
	}
	if (listen(_socket.fd, 10) < 0)
	{
		std::cout << _webserv_tag << _error_tag << " Failed to listen socket (" << errno << ")" << std::endl;
		exit(1);
	}
	std::cout << _webserv_tag << " Socket successfully created for port " << port << std::endl;
	return (_socket);
}

webserv::vectorIterator	webserv::getHost(std::string host)
{
	vectorIterator	vectIter = _vhosts->begin();
	vectorIterator	vectIter2 = _vhosts->end();
	std::string		resolved = resolveHost(host);
	mapIterator		iter;
	
	while (vectIter != vectIter2)
	{
		if (vectIter->find(host) != vectIter->end()
			|| resolveHost(vectIter->begin()->second.server_name + ":" + vectIter->begin()->second.listen) == resolved)
			return (vectIter);
		++vectIter;
	}
	std::cout << _webserv_tag << _error_tag << " Host not found, using first server block" << std::endl;
	return (vectIter);
}

std::string	webserv::resolveHost(std::string host)
{
	int							result = 0;
	struct addrinfo				hints, *res;
	struct sockaddr_in			*addrin;
	std::string					port;
	std::vector<std::string>	vect = split_string(host, ":");
	std::ostringstream			stringStream;
	unsigned char				*binaryIP;

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
		std::cout << _webserv_tag << _error_tag << " Failed to resolve hostname " << host << " " << "(" << errno << ")" << std::endl;
		exit(1);
	}
	addrin = (struct sockaddr_in *)res->ai_addr;
	binaryIP = (unsigned char *)&addrin->sin_addr.s_addr;
	stringStream << (int)binaryIP[0] << "." << (int)binaryIP[1] << "." << (int)binaryIP[2] << "." << (int)binaryIP[3];
	return (stringStream.str());
}

std::vector<std::multimap<std::string, t_route> >	&webserv::getVirtualHosts(void)
{
	return (*_vhosts);
}

void	webserv::printConfig(void)
{
	vectorIterator	vectIter = _vhosts->begin();
	vectorIterator	vectIter2 = _vhosts->end();
	mapIterator		mapIter;
	mapIterator		mapIter2;
	
	while (vectIter != vectIter2)
	{
		std::cout << "__________________________________________________" << std::endl;
		mapIter = vectIter->begin();
		mapIter2 = vectIter->end();
		std::cout << "Route [" << mapIter->first << "]" << std::endl;
		while (mapIter != mapIter2)
		{
			t_route	&route = mapIter->second;
			std::cout << "type : " << (route.type ? "LOCATION":"SERVER") << std::endl;
			std::cout << "listen : " << route.listen << std::endl;
			std::cout << "server_name : " << route.server_name << std::endl;
			std::cout << "access_log : " << route.access_log << std::endl;
			std::cout << "client_max_body_size : " << route.client_max_body_size << std::endl;
			std::cout << "error_page :" << std::endl;
			printIntStringMap(route.error_page);
			std::cout << "root : " << route.root << std::endl;
			std::cout << "index : " << concatStringVector(route.index) << std::endl;
			std::cout << "methods_allowed : " << concatMethods(route.methods_allowed) << std::endl;
			std::cout << "autoindex : " << (route.autoindex ? "true":"false") << std::endl;
			std::cout << "cgi_pass : " << std::endl;
			printCgiMap(route.cgi_pass);
			std::cout << "upload : " << (route.upload ? "true":"false") << std::endl;
			std::cout << "upload_path : " << route.upload_path << std::endl;
			std::cout << "match : " << route.match << std::endl;
			std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
			++mapIter;
		}
		++vectIter;
	}
}
