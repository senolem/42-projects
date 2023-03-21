/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:30:45 by albaur            #+#    #+#             */
/*   Updated: 2023/03/21 15:25:10 by albaur           ###   ########.fr       */
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
		CgiHandler(std::string &cgi_path, RequestParser &request_parser, t_request &request, t_response &response);
		CgiHandler(const CgiHandler &src);
		~CgiHandler(void);
		CgiHandler	&operator=(const CgiHandler &src);

		std::string	executeCgi(void);
	
	private:
		std::map<std::string, std::string>	_env;
		std::string							&_cgi_path;
		std::string							_script_path;
		RequestParser						&_request_parser;
		t_request					&_request;
		t_response					&_response;
};

#endif
