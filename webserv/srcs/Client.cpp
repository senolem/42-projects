/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:56:02 by melones           #+#    #+#             */
/*   Updated: 2023/03/27 03:09:26 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(Server *server, RequestHandler *request_handler) : _server(server), _request_time(0), _request_handler(request_handler), _open(false)
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
	_content_length = -1;
	_is_chunked = false;
	_request_size = 0;
	_body_size = 0;
	_check_size = false;
	resetTimeout();
	std::cout << BLUE << INFO << GREEN << SERV << NONE << " Connection successfully established to " << _resolved << "\n";
}

Client::Client(const Client &src) : _server(src._server), _socket(src._socket), _requests(src._requests), _host(src._host), _port(src._port), _resolved(src._resolved), _request_time(src._request_time), _request_handler(src._request_handler), _open(src._open)
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
		this->_requests = src._requests;
		this->_host = src._host;
		this->_port = src._port;
		this->_resolved = src._resolved;
		this->_request_time = src._request_time;
		this->_request_handler = src._request_handler;
		this->_open = src._open;
		this->_response = src._response;
		this->_sent = src._sent;
		this->_is_chunked = src._is_chunked;
		this->_content_length = src._content_length;
		this->_request_size = src._request_size;
		this->_body_size = src._body_size;
		this->_check_size = src._check_size;
	}
	return (*this);
}

int	Client::getRequest(void)
{
	char		buffer[BUFFER_SIZE];
	int			buffer_size = sizeof(buffer);
	int			rd = 0;
	int			client_max_body_size = _server->getVirtualHosts().begin()->second.client_max_body_size;
	size_t		i = 0;
	std::string					tmp;
	std::vector<std::string>	vect;
	size_t	pos = std::string::npos;
	size_t	pos2 = std::string::npos;
	bool	do_split = false;

	memset(&buffer, 0, buffer_size);
	resetTimeout();
	rd = recv(_socket.fd, buffer, buffer_size, 0);
	if (rd == -1)
	{
		_open = false;
		return (-1);
	}
	else if (rd == 0)
		return (2);
	else if (rd > 0)
	{
		_request_buffer.append(buffer, rd);
		pos = _request_buffer.find("\r\n\r\n");
		if (!_check_size && pos != std::string::npos)
			_check_size = true;
		if (!_is_chunked && _content_length == -1)
		{
			while (_request_buffer.find("\r\n\r\n", i) != std::string::npos || _request_buffer.find("\r\n", i) == i)
			{
				std::string	tmp = _request_buffer.substr(i, _request_buffer.find("\r\n", i) - i);
				if (tmp.length() > 16 && toLowerStringCompare("Content-length: ", tmp.substr(0, 16)))
				{
					int	tmp_length = std::atoi(tmp.substr(16, tmp.size()).c_str());
					if (tmp_length >= 0)
						_content_length = tmp_length;
					else
						_content_length = 0;	
				}
				else if (tmp.length() > 19 && toLowerStringCompare("Transfer-encoding: ", tmp.substr(0, 19)))
				{
					if (toLowerStringCompare("chunked", tmp.substr(19, tmp.size())))
						_is_chunked = true;		
				}
				i += tmp.size() + 2;
			}
			tmp.clear();
		}
		if (_is_chunked)
		{
			if (_check_size)
			{
				pos2 = _request_buffer.find("0\r\n", pos);
				if (pos2 != std::string::npos)
				{
					pos2 += 3;
					do_split = true;
				}
			}
		}
		else if (_content_length >= 0)
		{
			if (_check_size && _content_length >= 0 && (size_t)_content_length <= _request_buffer.length() - pos + 4)
			{
				pos2 = (pos + 4) + _content_length;
				do_split = true;
			}
		}
		if (_check_size)
		{
			if (_is_chunked)
				_body_size = pos2;
			else if (_content_length >= 0)
				_body_size = _request_buffer.length() - pos + 4;
			_request_size = _request_buffer.length() - _body_size;
		}
		if (rd < buffer_size && _check_size && _content_length == -1 && !_is_chunked && !do_split)
		{
			do_split = true;
			pos2 = rd;
		}
		if ((client_max_body_size != 0 && _body_size > client_max_body_size) ||
			(_request_size > MAX_REQUEST_SIZE_PROTECTION && MAX_REQUEST_SIZE_PROTECTION != 0))
			return (-2);
		if (do_split)
		{
			std::cout << BLUE << INFO << GREEN << SERV << NONE << " Request received from " << _resolved << " (length " << _request_buffer.length() << ") :\n";
			tmp = _request_buffer.substr(pos2);
			_request_buffer.erase(pos2);
			std::cout << _request_buffer << "\n";
			t_request	parsed_request = _request_handler->parseRequest(_request_buffer);
			parsed_request.remote_addr = _host;
			_requests.push_back(parsed_request);
			_request_buffer.clear();
			if (!tmp.empty())
				_request_buffer = tmp;
			_content_length = -1;
			_is_chunked = false;
			_request_size = 0;
			_body_size = 0;
			_check_size = false;
			if (_request_buffer.empty())
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

std::vector<t_request>	&Client::getParsedRequests(void)
{
	return (_requests);
}

t_socket	Client::getSocket(void)
{
	return (_socket);
}

std::string	Client::getResolved(void)
{
	return (_resolved);
}

size_t	Client::getSent(void)
{
	return (_sent);
}

bool	Client::getDone(void)
{
	return (_done);
}

void	Client::setSent(size_t sent)
{
	_sent = sent;
}


void	Client::setDone(bool done)
{
	_done = done;
}

bool	Client::isOpen(void)
{
	return (_open);
}

bool	Client::isResponseEmpty(void)
{
	return (_response.empty());
}

bool	Client::isRequestBufferEmpty(void)
{
	return (_request_buffer.empty());
}

void	Client::setResponse(std::string response)
{
	_response = response;
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
			return (0);
		else
			return (1);
	}
}

void	Client::checkTimeout(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	if (tv.tv_usec - _request_time > 120000000)
		_open = false;
}

void	Client::resetTimeout(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	_request_time = tv.tv_usec;
}
