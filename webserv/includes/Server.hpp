/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:35 by albaur            #+#    #+#             */
/*   Updated: 2023/03/14 11:07:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "webserv.hpp"
# include "Structures.hpp"
# include "RequestParser.hpp"
# include "Client.hpp"

class webserv;
class RequestParser;
class Client;
class Server
{
	private:
		webserv								&_webserv;
		std::multimap<std::string, t_route>	&_vhosts;
		size_t								_nb_vhost;
		t_socket							_socket;
		RequestParser						*_request_parser;
		std::vector<Client*>				_clients;

	public:
		Server(webserv &webserv, std::multimap<std::string, t_route> &vhosts, t_socket socket_);
		Server(const Server &src);
		~Server(void);
		Server  &operator=(const Server &src);

		int											newConnection(void);
		t_socket									getSocket(void);
		std::vector<Client*>						*getClients(void);
		std::string									getResponse(t_request_header request);
		const std::multimap<std::string, t_route>	&getVirtualHosts(void);
};

#endif
