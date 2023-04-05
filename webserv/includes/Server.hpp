/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:35 by albaur            #+#    #+#             */
/*   Updated: 2023/04/05 22:41:59 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "webserv.hpp"
# include "Structures.hpp"
# include "RequestHandler.hpp"
# include "Client.hpp"

class webserv;
class RequestHandler;
class Client;
class Server
{
	private:
		webserv								&_webserv;
		std::multimap<std::string, t_route>	&_vhosts;
		size_t								_nb_vhost;
		t_socket							_socket;
		RequestHandler						*_request_handler;
		std::vector<Client*>				_clients;

	public:
		Server(webserv &webserv, std::multimap<std::string, t_route> &vhosts, t_socket socket_);
		Server(const Server &src);
		~Server(void);
		Server  &operator=(const Server &src);

		std::ofstream								_log_file;

		int											newConnection(void);
		t_socket									getSocket(void);
		std::vector<Client*>						*getClients(void);
		std::string									getResponse(t_request &request);
		const std::multimap<std::string, t_route>	&getVirtualHosts(void);
		void										writeAccessLog(const std::string &str);
};

#endif
