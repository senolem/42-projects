/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:05:25 by albaur            #+#    #+#             */
/*   Updated: 2023/03/16 00:16:53 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP
# include "webserv.hpp"
# include "CgiHandler.hpp"

class webserv;
class cgiHandler;
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
		std::string								_filetype;
		
	public:
		RequestParser(webserv &webserv_, std::multimap<std::string, t_route> &vhosts);
		RequestParser(const RequestParser &src);
		~RequestParser(void);
		RequestParser	&operator=(const RequestParser &src);
		
		t_request_header					parseRequest(std::string buffer);
		std::multimap<float, std::string>	parseAcceptHeader(const std::string &header);
		std::map<std::string, std::string>	parseCookieHeader(const std::string &header);
		std::string							parseHostHeader(const std::string &header);
		std::string							getResponse(t_request_header request);
		std::string							getPath(vectorIterator vectIter, std::string path, mapIterator *subserver);
		std::string							getFiletype(void);
		std::string							getHeader(std::vector<std::string> header, std::string field);
		void								setContentType(t_request_header &request, t_response_header *header, std::string path);
		void								setStatusErrorPage(t_response_header *header, const t_request_header &request);
		void								handleGetResponse(t_request_header &request, t_response_header &response);
		void								handlePostResponse(t_request_header &request, t_response_header &response);
		void								handleDeleteResponse(t_request_header &request, t_response_header &response);
		int									isAccepted(t_request_header header, const std::string &type);
		void								initErrors(void);
		void								initTypes(void);
};

#endif
