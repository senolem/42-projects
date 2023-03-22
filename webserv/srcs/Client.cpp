/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:56:02 by melones           #+#    #+#             */
/*   Updated: 2023/03/23 00:18:43 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(Server *server, RequestHandler *request_handler) : _server(server), _socket(), _request(), _host(), _port(), _resolved(), _request_time(0), _request_handler(request_handler), _open(false)
{
	int	flags = 0;
	int	addrlen = sizeof(_socket.sockaddr_);

	memset(&_socket.sockaddr_, 0, sizeof(_socket.sockaddr_));
	_socket.fd = accept(_server->getSocket().fd, (sockaddr *)&_socket.sockaddr_, (socklen_t*)&addrlen);
	if (_socket.fd < 0)
		throw Exception(RED + ERROR + GREEN + SERV + NONE + " Failed to accept connection");
	flags = fcntl(_socket.fd, F_GETFL);
	if (flags < 0)
		throw Exception(RED + ERROR + GREEN + SERV + NONE + " Failed to get socket flags");
	if (fcntl(_socket.fd, F_SETFL, flags | O_NONBLOCK) < 0)
		throw Exception(RED + ERROR + GREEN + SERV + NONE + " Failed to set socket to non-blocking mode");
	int opt = 1;
	if (setsockopt(_socket.fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw Exception(RED + ERROR + GREEN + SERV + NONE + " Failed to set socket options");
	_host = inet_ntoa(_socket.sockaddr_.sin_addr);
	_port = htons(_socket.sockaddr_.sin_port);
	_resolved = _host + ":" + itostr(_port);
	_open = true;
	_sent = 0;
	resetTimeout();
	std::cout << BLUE << INFO << GREEN << SERV << NONE << " Connection successfully established to " << _resolved << "\n";
}

Client::Client(const Client &src) : _server(src._server), _socket(src._socket), _request(src._request), _host(src._host), _port(src._port), _resolved(src._resolved), _request_time(src._request_time), _request_handler(src._request_handler), _open(src._open)
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
	char		buffer[BUFFER_SIZE];
	int			buffer_size = sizeof(buffer);
	bool		reading_done = false;
	int			rd = 0;
	std::string	request;
	bool		check_size = false;
	int			body_size = 0;
	int			request_size = 0;
	int			client_max_body_size = _server->getVirtualHosts().begin()->second.client_max_body_size;

	memset(&buffer, 0, buffer_size);
	resetTimeout();
	while (!reading_done)
	{
		rd = recv(_socket.fd, buffer, buffer_size, 0);
		if (rd == -1)
		{
			_open = false;
			return (-1);
		}
		request_size += rd;
		if (check_size)
			body_size += rd;
		if ((client_max_body_size != 0 && body_size > client_max_body_size) ||
			(request_size > MAX_REQUEST_SIZE_PROTECTION && MAX_REQUEST_SIZE_PROTECTION != 0))
			return (-2);
		if (rd == 0)
			reading_done = true;
		else if (rd > 0)
		{
			request.append(buffer, rd);
			if (request.find("\r\n\r\n") != std::string::npos)
				check_size = true;
			if (rd < buffer_size)
				reading_done = true;
		}
	}
	if (request.length() > 0)
	{
		std::cout << BLUE << INFO << GREEN << SERV << NONE << " Request received from " << _resolved << " (length " << request.length() << ") :\n";
		std::cout << request << "\n";
		_server->writeAccessLog("Request received from " + _resolved + " " + get_date() + " :" + "\n" + request + "\n");
		_request = _request_handler->parseRequest(request);
	}
	if (rd == 0 || !reading_done)
	{
		_open = false;
		return (0);
	}
	return (1);
}

t_request	Client::getParsedRequest(void)
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
	int			i = 0;
	std::string	str;

	if (_sent <= _response.size())
		str = _response.substr(_sent, BUFFER_SIZE);
	else
	{
		_open = false;
		_sent = 0;
		return (-1);
	}
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
