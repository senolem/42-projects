/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:35 by albaur            #+#    #+#             */
/*   Updated: 2023/03/03 13:30:53 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "webserv.hpp"
# include "Structures.hpp"
# include "Header.hpp"

class webserv;
class Header;
class Server
{
	private:
		webserv								&_webserv;
		std::multimap<std::string, t_route>	&_vhosts;
		size_t								_nb_vhost;
		t_socket							_socket;
		const std::string					_serv_tag;
		const std::string					_error_tag;
		Header								*_header;

	public:
		Server(webserv &webserv, std::multimap<std::string, t_route> &vhosts, t_socket socket_);
		Server(const Server &src);
		~Server(void);
		Server  &operator=(const Server &src);

		void		acceptConnection(void);
};

#endif
