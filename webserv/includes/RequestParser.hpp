/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:05:25 by albaur            #+#    #+#             */
/*   Updated: 2023/03/14 13:21:45 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP
# include "webserv.hpp"

class webserv;
class RequestParser
{
	public:
		typedef std::map<std::string, t_route>::iterator					mapIterator;
		typedef std::vector<std::multimap<std::string, t_route> >::iterator	vectorIterator;

	private:
		webserv									&_webserv;
		std::multimap<std::string, t_route>		&_vhosts;
		std::map<std::string, std::string>		_typesMap;
		std::map<int, std::string>				_errorsMap;
		std::string								_currentRoot;
		mapIterator								_currentLocationBlock;
		
	public:
		RequestParser(webserv &webserv_, std::multimap<std::string, t_route> &vhosts);
		RequestParser(const RequestParser &src);
		~RequestParser(void);
		RequestParser	&operator=(const RequestParser &src);
		
		t_request_header					parseRequest(std::string buffer);
		std::multimap<float, std::string>	parseAcceptHeader(const std::string &header);
		std::map<std::string, std::string>	parseCookieHeader(const std::string &header);
		std::string							parseHostHeader(const std::string &header);
		std::vector<std::string>			parseBodyForm(const std::string &body);
		std::string							getResponse(t_request_header request);
		std::string							getPath(vectorIterator vectIter, std::string path, mapIterator *subserver);
		void								setContentType(t_request_header &request, t_response_header *header, std::string path);
		int									isAccepted(t_request_header header, const std::string &type);
		std::string							getHeader(std::vector<std::string> header, std::string field);
		int									executeCgi(std::string path, std::vector<std::string> env);
		void								initErrors(void);
		void								initTypes(void);
};

#endif