/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:30:45 by albaur            #+#    #+#             */
/*   Updated: 2023/03/15 20:24:08 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
# define CGIHANDLER_HPP
# include "webserv.hpp"
# include "RequestParser.hpp"

class RequestParser;
class CgiHandler
{
	public:
		CgiHandler(std::string &cgi_path, RequestParser &request_parser, t_request_header &request, t_response_header &response);
		CgiHandler(const CgiHandler &src);
		~CgiHandler(void);
		CgiHandler	&operator=(const CgiHandler &src);

		std::string	executeCgi(void);
	
	private:
		std::map<std::string, std::string>	_env;
		std::string							&_cgi_path;
		std::string							_script_path;
		RequestParser						&_request_parser;
		t_request_header					&_request;
		t_response_header					&_response;
};

#endif
