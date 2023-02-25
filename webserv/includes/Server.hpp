/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:35 by albaur            #+#    #+#             */
/*   Updated: 2023/02/25 20:19:49 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "webserv.hpp"
# include "Structures.hpp"

class webserv;
class Server
{
	private:
		webserv											&_webserv;
		std::multimap<std::string, t_route>				&_vhosts;
		size_t											_nb_vhost;
		std::map<std::string, std::string>				_typesMap;
		t_socket										_socket;

	public:
		typedef std::multimap<std::string, t_route>::iterator	mapIterator;

		Server(webserv &webserv, std::multimap<std::string, t_route> &vhosts, t_socket socket_);
		Server(const Server &src);
		~Server(void);
		Server  &operator=(const Server &src);

		void		acceptConnection(void);
		std::string	getResponse(t_request_header request);
		void		setFiletype(t_response_header *header, std::string path);
		void		initTypes(void);
};

#endif
