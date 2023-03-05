/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:53:16 by melones           #+#    #+#             */
/*   Updated: 2023/03/05 23:49:51 by melones          ###   ########.fr       */
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

int	Server::newConnection(void)
{
	Client	*client = new Client(this, _header);
	_clients.push_back(client);
	return (client->getSocket().fd);

	//std::cout << _serv_tag << " Request received : " << std::endl;
	//std::cout << request << std::endl;
	//response = _header->getResponse(_header->parseRequest(request));
	//std::cout << _serv_tag << " Response sent" << std::endl;
	//write(fd, response.c_str(), response.length());
	//close(fd);
}

t_socket	Server::getSocket(void)
{
	return (_socket);
}

std::vector<Client*>	*Server::getClients(void)
{
	return (&_clients);
}

std::string	Server::getResponse(t_request_header request)
{
	return (_header->getResponse(request));
}