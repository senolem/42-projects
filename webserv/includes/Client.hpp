/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:48:37 by melones           #+#    #+#             */
/*   Updated: 2023/03/06 16:30:03 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP
# include "webserv.hpp"
# include "Server.hpp"
# include "Header.hpp"
# include <stdlib.h>

class Server;
class Header;
class Client
{
	public:
		Client(Server *server, Header *header);
		Client(const Client &src);
		~Client(void);
		Client  &operator=(const Client &src);

		int							getRequest(void);
		t_request_header			getParsedRequest(void);
		t_socket					getSocket(void);
		std::string					getResolved(void);
		bool						isOpen(void);
		void						sendResponse(std::string response);
		void						checkTimeout(void);
		void						resetTimeout(void);

	private:
		Server				*_server;
		t_socket			_socket;
		t_request_header	_request;
		std::string			_host;
		int					_port;
		std::string			_resolved;
		time_t				_request_time;
		Header				*_header;
		bool				_open;
};

#endif
