/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:35 by albaur            #+#    #+#             */
/*   Updated: 2023/02/21 11:48:42 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "webserv.hpp"
# include "Structures.hpp"

namespace ft
{
	class Server
	{
		private:
			std::vector<std::map<int, t_route> >	*_servers;
			size_t									_nb_servers;

		public:
			typedef std::map<int, t_route>::iterator				mapIterator;
			typedef std::vector<std::map<int, t_route> >::iterator	vectorIterator;

			Server(void)
			{

			}

			Server(const Server &src)
			{
				*this = src;
			}
	
			~Server(void)
			{
				
			}
	
			Server	&operator=(const Server &src)
			{
				if (this != &src)
				{
					this->_servers = src._servers;
					this->_nb_servers = _servers->size();
				}
				return (*this);
			}

			void	importConfig(std::vector<std::map<int, t_route> > *src)
			{
				_servers = src;
				_nb_servers = _servers->size();
			}

			void	printConfig(void)
			{
				vectorIterator	vectIter = _servers->begin();
				vectorIterator	vectIter2 = _servers->end();
				mapIterator		mapIter;
				mapIterator		mapIter2;
				
				while (vectIter != vectIter2)
				{
					std::cout << "__________________________________________________" << std::endl;
					mapIter = vectIter->begin();
					mapIter2 = vectIter->end();
					std::cout << "Route [" << mapIter->first << "]" << std::endl;
					while (mapIter != mapIter2)
					{
						ft::t_route	&route = mapIter->second;
						std::cout << "type : " << (route.type ? "LOCATION":"SERVER") << std::endl;
						std::cout << "listen : " << concatStringVector(route.listen) << std::endl;
						std::cout << "server_name : " << concatStringVector(route.server_name) << std::endl;
						std::cout << "access_log : " << route.access_log << std::endl;
						std::cout << "client_max_body_size : " << route.client_max_body_size << std::endl;
						std::cout << "error_page :" << std::endl;
						printIntStringMap(route.error_page);
						std::cout << "root : " << route.root << std::endl;
						std::cout << "index : " << concatStringVector(route.index) << std::endl;
						std::cout << "methods_allowed : " << concatMethods(route.methods_allowed) << std::endl;
						std::cout << "autoindex : " << (route.autoindex ? "true":"false") << std::endl;
						std::cout << "cgi_pass : " << std::endl;
						printCgiMap(route.cgi_pass);
						std::cout << "upload : " << (route.upload ? "true":"false") << std::endl;
						std::cout << "upload_path : " << route.upload_path << std::endl;
						std::cout << "--------------------------------------------------" << std::endl;
						++mapIter;
					}
					++vectIter;
				}
			}
	};
}

#endif