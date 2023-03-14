/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:56:02 by melones           #+#    #+#             */
/*   Updated: 2023/03/14 11:11:18 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(Server *server, RequestParser *request_parser) : _server(server), _socket(), _request(), _host(), _port(), _resolved(), _request_time(0), _request_parser(request_parser), _open(false)
{
	int	flags = 0;
	int	addrlen = sizeof(_socket.sockaddr_);

	memset(&_socket.sockaddr_, 0, sizeof(_socket.sockaddr_));
	_socket.fd = accept(_server->getSocket().fd, (sockaddr *)&_socket.sockaddr_, (socklen_t*)&addrlen);
	if (_socket.fd < 0)
	{
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to accept connection (" << errno << ")\n";
		exit(1);
	}
	flags = fcntl(_socket.fd, F_GETFL);
	if (flags < 0)
	{
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to get socket flags (" << errno << ")\n";
		exit(1);
	}
	if (fcntl(_socket.fd, F_SETFL, flags | O_NONBLOCK) < 0)
	{
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to set socket to non-blocking mode (" << errno << ")\n";
		exit(1);
	}
	int opt = 1;
	if (setsockopt(_socket.fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to set socket options (" << errno << ")\n";
		exit(1);
	}
	_host = inet_ntoa(_socket.sockaddr_.sin_addr);
	_port = htons(_socket.sockaddr_.sin_port);
	_resolved = _host + ":" + ft_itoa(_port);
	_open = true;
	_sent = 0;
	resetTimeout();
	std::cout << GREEN << SERV << NONE << " Connection successfully established to " << _resolved << "\n";
}

Client::Client(const Client &src) : _server(src._server), _socket(src._socket), _request(src._request), _host(src._host), _port(src._port), _resolved(src._resolved), _request_time(src._request_time), _request_parser(src._request_parser), _open(src._open)
{
	*this = src;
}

Client::~Client(void)
{
	close(_socket.fd);
}

Client  &Client::operator=(const Client &src)
{
	if (this != &src)
	{
		this->_server = src._server;
		this->_socket = src._socket;
		this->_request = src._request;
		this->_host = src._host;
		this->_port = src._port;
		this->_resolved = src._resolved;
		this->_request_time = src._request_time;
	}
	return (*this);
}

int	Client::getRequest(void)
{
	char		buffer[1024];
	int			bufferSize = sizeof(buffer);
	bool		readingDone = false;
	int			rd = 0;
	std::string	request;

	memset(&buffer, 0, bufferSize);
	resetTimeout();
	while (!readingDone)
	{
		rd = recv(_socket.fd, buffer, bufferSize, 0);
		if (request.size() > _server->getVirtualHosts().begin()->second.client_max_body_size)
			return (-2);
		if (rd == 0)
			readingDone = true;
		else if (rd > 0)
		{
			request.append(buffer, rd);
			if (rd < bufferSize)
				readingDone = true;
		}
	}
	if (request.length() > 0)
	{
		std::cout << GREEN << SERV << NONE << " Request received (length " << request.length() << ") :\n";
		std::cout << request << "\n";
		_request = _request_parser->parseRequest(request);
	}
	else
		memset(&_request, 0, sizeof(t_request_header));
	if (rd == 0 || !readingDone)
	{
		_open = false;
		return (0);
	}
	return (1);
}

t_request_header	Client::getParsedRequest(void)
{
	return (_request);
}

std::string	Client::getResolved(void)
{
	return (_resolved);
}

size_t	Client::getSent(void)
{
	return (_sent);
}

int	Client::sendResponse(void)
{
	std::string	str = _response.substr(_sent, BUFFER_SIZE);
	int	i = 0;

	i = send(_socket.fd, str.c_str(), str.length(), 0);
	if (i == -1)
	{
		_open = false;
		_sent = 0;
		return (-1);
	}
	else
	{
		_sent += i;
		if (_sent >= _response.size())
		{
			_open = false;
			return (0);
		}
		else
			return (1);
	}
}

bool	Client::isResponseEmpty(void)
{
	return (_response.empty());
}

void	Client::setResponse(std::string response)
{
	_response = response;
}

bool	Client::isOpen(void)
{
	return (_open);
}

t_socket	Client::getSocket(void)
{
	return (_socket);
}

void	Client::checkTimeout(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	if (tv.tv_usec - _request_time > 30000000)
		_open = false;
}

void	Client::resetTimeout(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	_request_time = tv.tv_usec;
}
