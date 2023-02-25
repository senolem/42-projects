/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:53:22 by melones           #+#    #+#             */
/*   Updated: 2023/02/25 20:19:49 by melones          ###   ########.fr       */
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
	return (_socket);
}

webserv::vectorIterator	webserv::getHost(std::string host)
{
	std::vector<std::string>	vect;
	vectorIterator				vectIter = _vhosts->begin();
	vectorIterator				vectIter2 = _vhosts->end();
	
	while (vectIter != vectIter2)
	{
		if (vectIter->find(host) != vectIter->end())
			return (vectIter);
		++vectIter;
	}
	return (vectIter);
}

std::string	webserv::getRoot(vectorIterator vectIter, std::string path)
{
	std::vector<std::string>	vect;
	mapIterator					mapIter = vectIter->begin();
	mapIterator					mapIter2 = vectIter->end();
	vect = ft_split(path, '/');
	if (vect.size() == 1)
		return (mapIter->second.root);
	else
	{
		while (mapIter != mapIter2)
		{
			if (mapIter->second.type == LOCATION && mapIter->second.match == "/" + vect.at(0))
				return (mapIter->second.root);
			++mapIter;
		}
	}
	return (vectIter->begin()->second.root);
}

t_request_header	webserv::parseRequest(char *buffer)
{
	t_request_header			header;
	std::string					bufferString(buffer);
	std::vector<std::string>	bufferVect;
	std::vector<std::string>	vect;
	std::vector<std::string>	vect2;
	vectorIterator				vectIter;

	bufferVect = ft_split(bufferString, '\n');
	vect = ft_split(bufferVect.at(0), ' ');
	vect2 = ft_split(bufferVect.at(1), ' ');
	header.host = vect2.at(1);
	header.method = vect.at(0);
	vectIter = getHost(header.host);
	if (vectIter != _vhosts->end())
		header.path = getRoot(vectIter, vect.at(1)) + vect.at(1);
	else
		header.path = getRoot(_vhosts->begin(), vect.at(1)) + vect.at(1); 
	std::cout << "path = " << header.path << std::endl;
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
