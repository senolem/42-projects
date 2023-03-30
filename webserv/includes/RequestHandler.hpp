/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:05:25 by albaur            #+#    #+#             */
/*   Updated: 2023/03/22 19:39:43 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHANDLER_HPP
# define REQUESTHANDLER_HPP
# include "webserv.hpp"
# include "CgiHandler.hpp"
# include "DirectoryListing.hpp"

class webserv;
class cgiHandler;
class RequestHandler
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
		RequestHandler(webserv &webserv_, std::multimap<std::string, t_route> &vhosts);
		RequestHandler(const RequestHandler &src);
		~RequestHandler(void);
		RequestHandler	&operator=(const RequestHandler &src);
		
		t_request							parseRequest(std::string buffer);
		std::multimap<float, std::string>	parseAcceptHeader(const std::string &header);
		std::string							parseTransferEncodingHeader(const std::string &header);
		void								parseChunkedBody(t_request &request);
		std::map<std::string, std::string>	parseCookieHeader(const std::string &header);
		std::string							parseHostHeader(const std::string &header);
		void								parseCgiBodyHeaders(t_request &request, t_response &response, std::string &body, int &skip, size_t &i);
		std::string							getResponse(t_request request);
		std::string							getPath(vectorIterator vectIter, std::string path, mapIterator *subserver, std::string method);
		std::string							getFiletype(void);
		std::string							getHeader(std::vector<std::string> header, std::string field);
		void								setContentType(t_request &request, t_response *header, std::string path);
		void								setStatusErrorPage(t_response *header, const t_request &request);
		void								handleCgi(t_request &request, t_response &response, std::stringstream &file_stream, std::map<std::string, t_cgi>::iterator cgi_iter);
		int									handleCgiPathInfo(t_request &request);
		void								handleUpload(t_request &request, t_response &response);
		void								handleGetResponse(t_request &request, t_response &response);
		void								handlePostResponse(t_request &request, t_response &response);
		void								handleDeleteResponse(t_request &request, t_response &response);
		void								handleRedirection(t_request &request, t_response &response);
		t_request							returnStatusCode(t_request &request, int status);
		void								returnStatusCodeVoid(t_request &request, int status);
		int									isAccepted(t_request header, const std::string &type);
		void								initErrors(void);
		void								initTypes(void);
};

#endif
