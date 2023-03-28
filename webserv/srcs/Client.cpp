/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:56:02 by melones           #+#    #+#             */
/*   Updated: 2023/03/28 02:41:57 by melones          ###   ########.fr       */
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
	_reading_done = false;
	_check_size = false;
	_body_size = 0;
	_request_size = 0;
	_is_chunked = false;
	_content_length = -1;
	_pos = std::string::npos;
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
	int			rd = 0;
	int			client_max_body_size = _server->getVirtualHosts().begin()->second.client_max_body_size;
	size_t		i = 0;
	std::string	tmp;
	size_t		pos2 = std::string::npos;

	memset(&buffer, 0, buffer_size);
	rd = recv(_socket.fd, buffer, buffer_size, 0);
	if (rd == -1)
	{
		_open = false;
		return (-1);
	}
	_buffer.append(buffer, rd);
	_request_size += rd;
	if (_check_size)
		_body_size = _buffer.length() - _pos;
	if ((client_max_body_size != 0 && _body_size > client_max_body_size) ||
		(_request_size > MAX_REQUEST_SIZE_PROTECTION && MAX_REQUEST_SIZE_PROTECTION != 0))
		return (-2);
	if (rd == 0)
		_reading_done = true;
	else if (rd > 0)
	{
		resetTimeout();
		if (!_check_size)
		{
			_pos = _buffer.find("\r\n\r\n");
			if (_pos != std::string::npos)
				_check_size = true;
		}
		if (!_is_chunked && _content_length == -1)
		{
			while (_buffer.find("\r\n\r\n", i) != std::string::npos || _buffer.find("\r\n", i) == i)
			{
				std::string	tmp = _buffer.substr(i, _buffer.find("\r\n", i) - i);
				if (tmp.length() > 16 && toLowerStringCompare("content-length: ", tmp.substr(0, 16)))
				{
					int	tmp_length = std::atoi(tmp.substr(16, tmp.size()).c_str());
					if (tmp_length >= 0)
						_content_length = tmp_length;
					else
						_content_length = 0;	
				}
				else if (tmp.length() > 19 && toLowerStringCompare("transfer-encoding: ", tmp.substr(0, 19)))
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
				pos2 = _buffer.find("\r\n0\r\n", _pos);
				if (pos2 != std::string::npos)
				{
					pos2 += 3;
					_reading_done = true;
				}
			}
		}
		else if (_content_length >= 0)
		{
			if (_check_size && _content_length >= 0 && (size_t)_content_length <= _buffer.length() - _pos + 4)
			{
				pos2 = (_pos + 4) + _content_length;
				_reading_done = true;
			}
		}
		if (rd < buffer_size && _check_size && _content_length == -1 && !_is_chunked && !_reading_done)
		{
			_reading_done = true;
			pos2 = rd;
		}
	}
	if (_buffer.length() > 0 && _reading_done)
	{
		std::string	colon;
		if (PRINT_REQUESTS)
			colon = " :";
		std::cout << BLUE << INFO << GREEN << SERV << NONE << " Request received from " << _resolved << " (length " << _buffer.length() << ")" << colon << "\n";
		if (PRINT_REQUESTS)
			std::cout << _buffer << "\n";
		_server->writeAccessLog("Request received from " + _resolved + " " + get_date() + " :" + "\n" + _buffer + "\n");
		if (pos2 != std::string::npos)
			_buffer.erase(pos2);
		_request = _request_handler->parseRequest(_buffer);
		_request.remote_addr = _host;
		_buffer.clear();
		_check_size = false;
		_body_size = 0;
		_request_size = 0;
		_is_chunked = false;
		_content_length = -1;
		_pos = std::string::npos;
		return (1);
	}
	return (0);
}

t_request	Client::getParsedRequest(void)
{
	return (_request);
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

void	Client::setSent(size_t sent)
{
	_sent = sent;
}

bool	Client::isOpen(void)
{
	return (_open);
}

bool	Client::isResponseEmpty(void)
{
	return (_response.empty());
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
		{
			_open = false;
			return (0);
		}
		else
			return (1);
	}
}

void	Client::checkTimeout(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	if (tv.tv_usec - _request_time > 5000000)
	{
		_open = false;
		std::cout << "timeout" << "\n";
	}
}

void	Client::resetTimeout(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	_request_time = tv.tv_usec;
}
