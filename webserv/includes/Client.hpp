/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:48:37 by melones           #+#    #+#             */
/*   Updated: 2023/03/23 19:50:47 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP
# include "webserv.hpp"
# include "Server.hpp"
# include "RequestHandler.hpp"
# include "Exception.hpp"
# include <stdlib.h>

class Server;
class RequestHandler;
class Client
{
	public:
		Client(Server *server, RequestHandler *request_handler);
		Client(const Client &src);
		~Client(void);
		Client  &operator=(const Client &src);

		int							getRequest(void);
		t_request					getParsedRequest(void);
		t_socket					getSocket(void);
		std::string					getResolved(void);
		size_t						getSent(void);
		bool						isOpen(void);
		bool						isResponseEmpty(void);
		void						setResponse(std::string response);
		int							sendResponse(void);
		void						checkTimeout(void);
		void						resetTimeout(void);

	private:
		Server						*_server;
		t_socket					_socket;
		t_request					_request;
		std::string					_host;
		int							_port;
		std::string					_resolved;
		time_t						_request_time;
		RequestHandler				*_request_handler;
		bool						_open;
		std::string					_response;
		size_t						_sent;
};

#endif
