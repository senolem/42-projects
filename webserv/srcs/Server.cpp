/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:53:16 by melones           #+#    #+#             */
/*   Updated: 2023/03/30 10:49:57 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(webserv &webserv_, std::multimap<std::string, t_route> &vhosts, t_socket socket_) : _webserv(webserv_), _vhosts(vhosts), _socket(socket_)
{
	_request_handler = new RequestHandler(webserv_, vhosts);
	_log_file.open(_vhosts.begin()->second.access_log.c_str(), std::ios::out | std::ios::app);
	if (!_log_file.is_open())
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to open log file (Does the parent folder exists?)\n";
}

Server::Server(const Server &src) : _webserv(src._webserv), _vhosts(src._vhosts), _socket(src._socket)
{
	*this = src;
}

Server::~Server(void)
{
	_log_file.close();
	delete _request_handler;
}

Server	&Server::operator=(const Server &src)
{
	if (this != &src)
	{
		this->_vhosts = src._vhosts;
		this->_nb_vhost = src._nb_vhost;
		this->_socket = src._socket;
		this->_request_handler = new RequestHandler(src._webserv, src._vhosts);
		this->_log_file.open(src._vhosts.begin()->second.access_log.c_str(), std::ios::out | std::ios::app);
		if (!_log_file.is_open())
			std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to open log file (Does the parent folder exists?)\n";
	}
	return (*this);
}

int	Server::newConnection(void)
{
	Client	*client = new Client(this, _request_handler);
	_clients.push_back(client);
	return (client->getSocket().fd);
}

t_socket	Server::getSocket(void)
{
	return (_socket);
}

std::vector<Client*>	*Server::getClients(void)
{
	return (&_clients);
}

std::string	Server::getResponse(t_request request)
{
	return (_request_handler->getResponse(request));
}

const std::multimap<std::string, t_route>	&Server::getVirtualHosts(void)
{
	return (_vhosts);
}

void	Server::writeAccessLog(const std::string &str)
{
	if (!_log_file.is_open())
		std::cout << RED + ERROR + GREEN + SERV + NONE + " Cannot write to log file\n";
	else if (LOG_REQUEST_LENGTH_LIMIT != -1)
	{
		if (LOG_REQUEST_LENGTH_LIMIT == 0)
			_log_file << str << "\n";
		else
			_log_file << str.substr(0, LOG_REQUEST_LENGTH_LIMIT) << "\n";
		_log_file.flush();
	}
}
