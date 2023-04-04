/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:30:45 by albaur            #+#    #+#             */
/*   Updated: 2023/04/04 23:45:10 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
# define CGIHANDLER_HPP
# include "webserv.hpp"
# include "RequestHandler.hpp"

class RequestHandler;
class CgiHandler
{
	public:
		CgiHandler(std::string &cgi_path, RequestHandler &request_handler, t_request &request, t_response &response);
		CgiHandler(const CgiHandler &src);
		~CgiHandler(void);
		CgiHandler	&operator=(const CgiHandler &src);

		std::string	executeCgi(void);
	
	private:
		std::map<std::string, std::string>	_env;
		std::string							&_cgi_path;
		std::string							_script_path;
		RequestHandler						&_request_handler;
		t_request							&_request;
		t_response							&_response;

		void								cleanCgi(t_exec_cgi &cgi);
};

#endif
