/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:53:22 by melones           #+#    #+#             */
/*   Updated: 2023/03/01 13:56:32 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

webserv::webserv(void)
{
		
}

webserv::webserv(const webserv &src)
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

void	webserv::importConfig(std::vector<std::multimap<std::string, t_route> > *src)
{
	_vhosts = src;
	_nb_vhost = _vhosts->size();
}

void	webserv::startServer(void)
{
	for (size_t i = 0; i < _nb_vhost; i++)
	{
		std::map<int, t_socket>::iterator	iter;
		int									port = atoi(_vhosts->at(i).begin()->second.listen.c_str());
		
		iter = _sockets.find(port);
		if (iter == _sockets.end())
		{
			_sockets.insert(std::pair<int, t_socket>(port, createSocket(port)));
			iter = _sockets.find(port);
		}
		_subservers.push_back(Server(*this, _vhosts->at(i), iter->second));

		pollfd	pfd;
		pfd.fd = iter->second.fd;
		pfd.events = POLLIN;
		_pollfds.push_back(pfd);
	}
	while (1)
	{
		if (poll(&_pollfds[0], _pollfds.size(), 5000) == -1)
		{
			std::cout << "Server error : Failed to poll (" << errno << ")" << std::endl;
			exit(1);
		}
		for (size_t i = 0; i < _pollfds.size(); i++)
		{
			if (_pollfds[i].revents & POLLIN)
				_subservers[i].acceptConnection();
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
		std::cout << "Server error : Failed to create socket (" << errno << ")" << std::endl;
		exit(1);
	}
	_socket.sockaddr_.sin_family = AF_INET;
	_socket.sockaddr_.sin_addr.s_addr = INADDR_ANY;
	_socket.sockaddr_.sin_port = htons(port);
	memset(_socket.sockaddr_.sin_zero, 0, sizeof(_socket.sockaddr_.sin_addr));
	if (bind(_socket.fd, (sockaddr *)&_socket.sockaddr_, sizeof(_socket.sockaddr_)) < 0)
	{
		std::cout << "Server error : Failed to bind socket (" << errno << ")" << std::endl;
		exit(1);
	}
	if (listen(_socket.fd, 10) < 0)
	{
		std::cout << "Server error : Failed to listen socket (" << errno << ")" << std::endl;
		exit(1);
	}
	std::cout << "[Server] " << "Socket successfully created for port " << port << std::endl;
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
	std::cout << "Server error : Host not found, using first server block" << std::endl;
	return (vectIter);
}

std::string	webserv::resolveHost(std::string host)
{
	int							result = 0;
	struct addrinfo				hints, *res;
	struct sockaddr_in			*addrin;
	std::string					port;
	std::vector<std::string>	vect = ft_split(host, ':');
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
		std::cout << "Server error : Failed to resolve hostname " << host << " " << "(" << errno << ")" << std::endl;
		exit(1);
	}
	addrin = (struct sockaddr_in *)res->ai_addr;
	binaryIP = (unsigned char *)&addrin->sin_addr.s_addr;
	stringStream << (int)binaryIP[0] << "." << (int)binaryIP[1] << "." << (int)binaryIP[2] << "." << (int)binaryIP[3];
	return (stringStream.str());
}

std::string	webserv::getPath(vectorIterator vectIter, std::string path)
{
	std::vector<std::string>	vect;
	std::string					search;
	mapIterator					mapIter = vectIter->begin();
	mapIterator					mapIter2 = vectIter->end();
	std::string					result;
	size_t						i = 0;

	vect = ft_split(path, '/');
	if (vect.at(0)[vect.at(0).length() - 1] == '/')
		search = vect.at(0).substr(0, vect.at(0).length() - 1);
	else
		search = vect.at(0);
	while (mapIter != mapIter2)
	{
		if (mapIter->second.type == LOCATION && mapIter->second.match == "/" + search)
		{
			result = mapIter->second.root + path;
			i = result.find("/" + search, 0);
			if (i != std::string::npos)
				result.erase(i, search.length() + 1);
			if (path.find_last_of('.') == std::string::npos)
			{
				for (size_t j = 0; j < mapIter->second.index.size(); j++)
				{
					if (access((result + mapIter->second.index[j]).c_str(), R_OK) == 0)
						return (result + mapIter->second.index[j]);
				}
			}
			return (result);
		}
		++mapIter;
	}
	if (path.find_last_of('.') == std::string::npos)
	{
		for (size_t j = 0; j < vectIter->begin()->second.index.size(); j++)
		{
			if (access((vectIter->begin()->second.root + "/" + vectIter->begin()->second.index[j]).c_str(), R_OK) == 0)
				return (vectIter->begin()->second.root + "/" + vectIter->begin()->second.index[j]);
		}
	}
	return (vectIter->begin()->second.root + path);
}

t_request_header	webserv::parseRequest(std::string buffer)
{
	t_request_header			header;
	std::vector<std::string>	bufferVect;
	std::vector<std::string>	vect;
	std::vector<std::string>	vect2;
	vectorIterator				vectIter;

	bufferVect = ft_split_string(buffer, "\r\n");
	vect = ft_split(bufferVect.at(0), ' ');
	vect2 = ft_split(bufferVect.at(1), ' ');
	header.host = vect2.at(1);
	header.method = vect.at(0);
	vectIter = getHost(header.host);
	if (vectIter != _vhosts->end())
		header.path = getPath(vectIter, vect.at(1));
	else
		header.path = getPath(_vhosts->begin(), vect.at(1));
	header.version = vect.at(2);
	return (header);
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
