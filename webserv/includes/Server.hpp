/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:35 by albaur            #+#    #+#             */
/*   Updated: 2023/02/23 16:01:31 by melones          ###   ########.fr       */
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
				int					fd = 0;
				ssize_t				rd = 0;
				std::string			response;
				
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
					if (rd < 0)
					{
						std::cout << "Server error : Failed to read buffer (" << errno << ")" << std::endl;
						exit(1);
					}
					response = getResponse(parseRequest(buffer));
					write(fd, response.c_str(), response.length());
					close(fd);
				}
				close(_socket);
			}

			t_request_header	parseRequest(char *buffer)
			{
				size_t						i = 0;
				t_request_header			header;
				std::string					bufferString(buffer);
				std::vector<std::string>	vect;

				i = bufferString.find('\n', 0);
				vect = ft_split(bufferString.substr(0, i - 1), ' ');
				header.method = vect.at(0);
				header.path = "www/" + vect.at(1);
				header.version = vect.at(2);
				return (header);
			}

			std::string	getResponse(t_request_header request)
			{
				std::stringstream	fileStream;
				std::stringstream	responseStream;
				t_response_header	header;
				std::string			filetype;
				
				filetype = ft_split(request.path, '.')[1];
				if (filetype == "html" || filetype.empty())
					header.content_type = "text/html";
				else if (filetype == "css")
					header.content_type = "text/css";
				else if (filetype == "png")
					header.content_type = "image/png";
				else if (filetype == "jpg")
					header.content_type = "image/jpeg";
				else if (filetype == "gif")
					header.content_type = "image/gif";
				else
					header.content_type = "text/plain";
				if (access(request.path.c_str(), R_OK) != 0)
				{
					header.status_code = "404 Not Found";
					header.content_length = 0;
				}
				else
				{
					std::ifstream	file(request.path.c_str(), std::ios::binary);
					fileStream << file.rdbuf();
					header.status_code = "200 OK";
					header.content = fileStream.str();
					header.content_length = header.content.size();
				}
				responseStream << header.version << " " << header.status_code << std::endl << "Content-Type: " << header.content_type << std::endl << "Content-Length: " << header.content_length << std::endl << std::endl << header.content;
				return (responseStream.str());
			}
	};
}

#endif
