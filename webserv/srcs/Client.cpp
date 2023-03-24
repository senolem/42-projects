/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:56:02 by melones           #+#    #+#             */
/*   Updated: 2023/03/24 20:08:56 by melones          ###   ########.fr       */
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
	_reading_done = false;
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
		this->_reading_done = src._reading_done;
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
	size_t		j = 0;
	std::string					tmp;
	std::vector<std::string>	vect;
	size_t	pos = 0;

	memset(&buffer, 0, buffer_size);
	resetTimeout();
	rd = recv(_socket.fd, buffer, buffer_size, 0);
	if (rd == -1)
	{
		_open = false;
		return (-1);
	}
	_request_size += rd;
	if (_check_size)
		_body_size += rd;
	if ((client_max_body_size != 0 && _body_size > client_max_body_size) ||
		(_request_size > MAX_REQUEST_SIZE_PROTECTION && MAX_REQUEST_SIZE_PROTECTION != 0))
		return (-2);
	if (rd == 0)
	{
		_reading_done = true;
		return (2);
	}
	else if (rd > 0)
	{
		_request_buffer.append(buffer, rd);
		pos = _request_buffer.find("\r\n\r\n");
		if (pos != std::string::npos)
		{
			_check_size = true;
			if (_content_length == -1 && !_is_chunked)
				_reading_done = true;
		}
		if (!_is_chunked)
		{
			for (size_t i = _request_buffer.find("\r\n", 0, pos); i != std::string::npos; i = _request_buffer.find("\r\n", 0, pos))
			{
				std::cout << "tmp2 = " << tmp;
				if (i > 0 && (j = _request_buffer.find_last_of("\r\n", 0, i - 1) != std::string::npos))
				{
					tmp = _request_buffer.substr(i, j + 2);
					std::cout << "tmp3 = " << tmp;
					if (toLowerStringCompare("Content-length: ", tmp))
					{
						vect = split_string(tmp, " ");
						if (vect.size() == 2)
						{
							long	tmp_length = std::strtol(vect.at(1).c_str(), NULL, 10);
							if (tmp_length >= 0)
								_content_length = tmp_length;
							else
								_content_length = 0;
						}
					}
					else if (toLowerStringCompare("Transfer-encoding: chunked", tmp))
						_is_chunked = true;
					tmp.clear();
				}
			}
		}
		if (_is_chunked && _check_size && _request_buffer.find("0\r\n"))
			_reading_done = true;
		if (_content_length != -1 && rd == buffer_size)
		{
			if (_content_length < buffer_size)
			{
				tmp = _request_buffer.substr(_content_length);
				_request_buffer.erase(_content_length);
			}
			_content_length -= rd;
		}
		else if (_check_size && rd < buffer_size)
		{
			tmp = _request_buffer.substr(pos + 4);
			_request_buffer.erase(pos + 4);
		}
		if (rd < buffer_size)
			_reading_done = true;
	}
	if (_request_buffer.length() > 0 && _reading_done)
	{
		std::cout << BLUE << INFO << GREEN << SERV << NONE << " Request received from " << _resolved << " (length " << _request_buffer.length() << ") :\n";
		std::cout << _request_buffer << "\n";
		_server->writeAccessLog("Request received from " + _resolved + " " + get_date() + " :" + "\n" + _request_buffer + "\n");
		t_request	parsed_request = _request_handler->parseRequest(_request_buffer);
		parsed_request.remote_addr = _host;
		_requests.push_back(parsed_request);
		_request_buffer.clear();
		if (!tmp.empty())
		{
			_request_buffer.append(tmp);
			std::cout << "request_buffer " << _request_buffer << "\n";
		}
		_content_length = -1;
		_is_chunked = false;
		_reading_done = false;
		_request_size = 0;
		_body_size = 0;
		_check_size = false;
		if (_request_buffer.empty())
			return (1);
		else
			return (0);
	}
	return (1);
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
	if (tv.tv_usec - _request_time > 30000000)
		_open = false;
}

void	Client::resetTimeout(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	_request_time = tv.tv_usec;
}
