/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:53:16 by melones           #+#    #+#             */
/*   Updated: 2023/03/22 20:23:09 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(webserv &webserv_, std::multimap<std::string, t_route> &vhosts, t_socket socket_) : _webserv(webserv_), _vhosts(vhosts), _socket(socket_), _request_handler(new RequestHandler(webserv_, vhosts))
{

}

Server::Server(const Server &src) : _webserv(src._webserv), _vhosts(src._vhosts), _socket(src._socket), _request_handler(new RequestHandler(src._webserv, src._vhosts))
{
	*this = src;
}

Server::~Server(void)
{
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
