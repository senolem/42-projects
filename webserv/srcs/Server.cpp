/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:53:16 by melones           #+#    #+#             */
/*   Updated: 2023/03/03 20:55:17 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(webserv &webserv_, std::multimap<std::string, t_route> &vhosts, t_socket socket_) : _webserv(webserv_), _vhosts(vhosts), _socket(socket_), _serv_tag("\033[33m[Server]\033[0m"), _error_tag("\033[31m[ERROR]\033[0m"), _header(new Header(webserv_, vhosts))
{
	
}

Server::Server(const Server &src) : _webserv(src._webserv), _vhosts(src._vhosts), _socket(src._socket),  _serv_tag("\033[33m[Server]\033[0m"), _error_tag("\033[31m[ERROR]\033[0m"), _header(new Header(src._webserv, src._vhosts))
{
	*this = src;
}

Server::~Server(void)
{

}

Server	&Server::operator=(const Server &src)
{
	if (this != &src)
	{
		this->_vhosts = src._vhosts;
		this->_nb_vhost = src._nb_vhost;
		this->_socket = src._socket;
		this->_header = src._header;
	}
	return (*this);
}

void	Server::acceptConnection(void)
{
    int					addrlen = sizeof(_socket.sockaddr_);
	std::string			request;
	std::string			response;
	char				buffer[1024];
	int					bufferSize = sizeof(buffer);
	int					fd = 0;
	int					rd = 0;
	int					flags = 0;
	bool				readingDone = false;

	fd = accept(_socket.fd, (sockaddr *)&_socket.sockaddr_, (socklen_t*)&addrlen);
	if (fd < 0)
	{
		std::cout << _serv_tag << _error_tag << " Failed to accept connection (" << errno << ")" << std::endl;
		exit(1);
	}
	std::cout << _serv_tag << " Connection successfully established to client" << std::endl;
	flags = fcntl(fd, F_GETFL);
	if (flags < 0)
	{
		std::cout << _serv_tag << _error_tag << " Failed to get socket flags (" << errno << ")" << std::endl;
		exit(1);
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
	{
		std::cout << _serv_tag << _error_tag << " Failed to set socket to non-blocking mode (" << errno << ")" << std::endl;
		exit(1);
	}
	while (!readingDone)
	{
		rd = recv(fd, buffer, bufferSize, 0);
		if (rd < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				continue ;
			else
			{
				std::cout << _serv_tag << _error_tag << " Failed to read buffer (" << errno << ")" << std::endl;
				exit(1);
			}
		}
		else if (rd == 0)
			readingDone = true;
		else
		{
			request.append(buffer, rd);
			if (rd < bufferSize)
				readingDone = true;
		}
	}
	std::cout << _serv_tag << " Request received : " << std::endl;
	std::cout << request << std::endl;
	response = _header->getResponse(_header->parseRequest(request));
	std::cout << _serv_tag << " Response sent" << std::endl;
	write(fd, response.c_str(), response.length());
	close(fd);
}
