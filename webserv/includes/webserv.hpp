/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:21:31 by albaur            #+#    #+#             */
/*   Updated: 2023/02/24 17:19:05 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# include <iostream>
# include <string>
# include <cstring>
# include <vector>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <string.h>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <map>
# include "Structures.hpp"
# include "Server.hpp"


// utils
std::string					concatStringVector(const std::vector<std::string> &vct);
void						printIntStringMap(const std::map<int, std::string> map);
std::string					concatMethods(const ft::t_methods methods);
void						printCgiMap(const std::map<std::string, ft::t_cgi> map);
std::vector<std::string>	ft_split(const std::string s, char c);

namespace ft
{
	class webserv
	{
		private:
			std::vector<Server>									_subservers;
			std::vector<std::multimap<std::string, t_route> >	*_vhosts;
			size_t												_nb_vhost;
			std::map<int, int>									_sockets;
		
		public:
			typedef std::map<std::string, t_route>::iterator					mapIterator;
			typedef std::vector<std::multimap<std::string, t_route> >::iterator	vectorIterator;
	
			webserv(void)
			{
			
			}
	
			webserv(const webserv &src)
			{
				*this = src;
			}
	
			~webserv(void)
			{
				
			}
	
			webserv	&operator=(const webserv &src)
			{
				if (this != &src)
				{
					this->_vhosts = src._vhosts;
					this->_nb_vhost = _vhosts->size();
				}
				return (*this);
			}
	
			void	importConfig(std::vector<std::multimap<std::string, t_route> > *src)
			{
				_vhosts = src;
				_nb_vhost = _vhosts->size();
			}

			void	startServer(void)
			{
				for (size_t i = 0; i < _nb_vhost; i++)
				{
					Server							subserver;
					std::map<int, int>::iterator	iter;
					int								port = atoi(_vhosts->at(i).begin()->second.listen.c_str());
					
					subserver.importConfig(&_vhosts->at(i));
					iter = _sockets.find();
					if (iter != _sockets.end())
						subserver.setSocket(iter->second);
					else
						_sockets.insert(port, createSocket(port));
					_subservers.push_back(subserver);
				}
				std::cout << _subservers.size() << std::endl;
			}

			int	createSocket(int port)
			{
				int					addrlen = 0;
				int					_socket = 0;
				int					fd = 0;
				ssize_t				rd = 0;
				std::string			response;
				sockaddr_in			sockaddr;
				
				_socket = socket(AF_INET, SOCK_STREAM, 0);
				if (_socket == 0)
				{
					std::cout << "Server error : Failed to create socket (" << errno << ")" << std::endl;
					exit(1);
				}
				sockaddr.sin_family = AF_INET;
				sockaddr.sin_addr.s_addr = INADDR_ANY;
				sockaddr.sin_port = htons(port);
				memset(sockaddr.sin_zero, 0, sizeof(sockaddr.sin_addr));
				if (bind(_socket, (sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
				{
					std::cout << "Server error : Failed to bind socket (" << errno << ")" << std::endl;
					exit(1);
				}
				if (listen(_socket, 10) < 0)
				{
					std::cout << "Server error : Failed to listen socket (" << errno << ")" << std::endl;
					exit(1);
				}
				return (_socket);
			}

			vectorIterator	getHost(std::string host)
			{
				std::vector<std::string>	vect;
				vectorIterator				vectIter = _vhosts->begin();
				vectorIterator				vectIter2 = _vhosts->end();
				
				while (vectIter != vectIter2)
				{
					if (vectIter->find(host) != vectIter->end())
						return (vectIter);
					++vectIter;
				}
				return (vectIter);
			}

			std::string	getRoot(vectorIterator vectIter, std::string path)
			{
				std::vector<std::string>	vect;
				mapIterator					mapIter = vectIter->begin();
				mapIterator					mapIter2 = vectIter->end();

				vect = ft_split(path, '/');
				if (vect.size() == 1)
					return (mapIter->second.root);
				else
				{
					while (mapIter != mapIter2)
					{
						if (mapIter->second.type == LOCATION && mapIter->second.match == "/" + vect.at(0))
							return (mapIter->second.root);
						++mapIter;
					}
				}
				return (vectIter->begin()->second.root);
			}
	
			t_request_header	parseRequest(char *buffer)
			{
				t_request_header			header;
				std::string					bufferString(buffer);
				std::vector<std::string>	bufferVect;
				std::vector<std::string>	vect;
				std::vector<std::string>	vect2;
				vectorIterator				vectIter;
				bufferVect = ft_split(bufferString, '\n');
				vect = ft_split(bufferVect.at(0), ' ');
				vect2 = ft_split(bufferVect.at(1), ' ');
				header.host = vect2.at(1);
				header.method = vect.at(0);
				vectIter = getHost(header.host);
				if (vectIter != _vhosts->end())
					header.path = getRoot(vectIter, vect.at(1)) + vect.at(1);
				else
					header.path = getRoot(_vhosts->begin(), vect.at(1)) + vect.at(1); 
				std::cout << "path = " << header.path << std::endl;
				header.version = vect.at(2);
				return (header);
			}
	
			void	printConfig(void)
			{
				vectorIterator	vectIter = _vhosts->begin();
				vectorIterator	vectIter2 = _vhosts->end();
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
						std::cout << "listen : " << route.listen << std::endl;
						std::cout << "server_name : " << route.server_name << std::endl;
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
						std::cout << "match : " << route.match << std::endl;
						std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
						++mapIter;
					}
					++vectIter;
				}
			}
	};
}

#endif