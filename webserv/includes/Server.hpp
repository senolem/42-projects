/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:35 by albaur            #+#    #+#             */
/*   Updated: 2023/02/21 17:56:16 by albaur           ###   ########.fr       */
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
			std::vector<std::map<int, t_route> >	*_vhosts;
			size_t									_nb_vhost;
			int										_socket;
			sockaddr_in								_sockaddr;
			int										_addrlen;

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
					this->_vhosts = src._vhosts;
					this->_nb_vhost = _vhosts->size();
				}
				return (*this);
			}

			void	importConfig(std::vector<std::map<int, t_route> > *src)
			{
				_vhosts = src;
				_nb_vhost = _vhosts->size();
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
						std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
						++mapIter;
					}
					++vectIter;
				}
			}

			void	startServer(void)
			{
				int			fd = 0;
				ssize_t		rd = 0;
				
				_addrlen = sizeof(_sockaddr);
				_socket = socket(AF_INET, SOCK_STREAM, 0);
				if (_socket == 0)
				{
					std::cout << "Server error : Failed to create socket (" << errno << ")" << std::endl;
					exit(1);
				}
				_sockaddr.sin_family = AF_INET;
				_sockaddr.sin_addr.s_addr = INADDR_ANY;
				_sockaddr.sin_port = htons(80);
				memset(_sockaddr.sin_zero, 0, sizeof(_sockaddr.sin_addr));
				if (bind(_socket, (sockaddr *)&_sockaddr, sizeof(_sockaddr)) < 0)
				{
					std::cout << "Server error : Failed to bind socket (" << errno << ")" << std::endl;
					exit(1);
				}
				if (listen(_socket, 10) < 0)
				{
					std::cout << "Server error : Failed to listen socket (" << errno << ")" << std::endl;
					exit(1);
				}
				while (1)
				{
					fd = accept(_socket, (sockaddr *)&_sockaddr, (socklen_t *)&_addrlen);
					if (fd < 0)
					{
						std::cout << "Server error : Failed to accept connection (" << errno << ")" << std::endl;
						exit(1);
					}

					char buffer[30000];
					rd = read(fd, buffer, 30000);
					std::string	bufferString(buffer);
					size_t	i = 0;
					size_t	j = 0;
					i = bufferString.find(' ', 5);
					j = bufferString.find('\n', 0);
					std::string	toGet = bufferString.substr(5, j - i);
					std::cout << buffer << std::endl;
					std::cout << "toGet = " << toGet << std::endl;
					std::string toSend = getFile(toGet);
					size_t	k = 0;
					k = toGet.find('.', 0);
					std::string	fileType = toGet.substr(k, toGet.length() - k);
					std::string	header;
					if (fileType == ".png")
						header = "HTTP/1.1 200 OK\nContent-Type: image/png;charset=utf-8\nContent-Length: " + std::to_string(toSend.length());
					else if (fileType == ".html")
						header = "HTTP/1.1 200 OK\nContent-Type: text/html;charset=utf-8\nContent-Length: " + std::to_string(toSend.length());
					else
						header = "HTTP/1.1 200 OK\nContent-Type: text/plain;charset=utf-8\nContent-Length: " + std::to_string(toSend.length());
					std::string	toSend2 = header + " \n\n" + toSend;
					std::cout << "sending : " << toSend2 << std::endl;
					write(fd, toSend2.c_str(), strlen(toSend2.c_str()));
					close(fd);
				}
				close(_socket);
			}

			std::string	getFile(std::string path)
			{
				std::ifstream		fileStream("www/" + path);
				std::stringstream	stringStream;
				std::string			toReturn;

				stringStream << fileStream.rdbuf();
				toReturn = stringStream.str();
				return (toReturn);
			}
	};
}

#endif
