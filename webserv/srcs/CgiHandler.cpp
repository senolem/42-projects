/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:42:02 by albaur            #+#    #+#             */
/*   Updated: 2023/03/15 16:07:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"

CgiHandler::CgiHandler(std::string &cgi_path, RequestParser &request_parser, t_request_header &request, t_response_header &response) : _cgi_path(cgi_path), _request_parser(request_parser), _request(request), _response(response)
{
	size_t	i = 0;

	_env["SERVER_PROTOCOL"] = _request.version;
	_env["SERVER_PORT"] = _request.matched_subserver->second.listen;
	_env["REQUEST_METHOD"] = _request.method;
	i = _request.path.find_last_of("." + _request_parser.getFiletype() + "/");
	if (i != std::string::npos)
		_env["PATH_INFO"] = _request.path.substr(i, _request.path.length() - i);
	if (_env.find("PATH_INFO") != _env.end())
		_env["PATH_TRANSLATED"] = _env["PATH_INFO"];
	i = _request.path.find_last_of("." + _request_parser.getFiletype());
	if (i != std::string::npos && i > 0)
		_env["SCRIPT_NAME"] = _request.path.substr(0, i - 1);
	i = _request.path.find_last_of("?");
	if (i != std::string::npos && i > 0)
		_env["QUERY_STRING"] = _request.path.substr(i, _request.path.length() - i);
	_env["CONTENT_LENGTH"] = ft_itoa(_request.body.length());
	_env["CONTENT_TYPE"] = _response.content_type;
}

CgiHandler::CgiHandler(const CgiHandler &src) : _cgi_path(src._cgi_path), _request_parser(src._request_parser), _request(src._request), _response(src._response)
{
	
}

CgiHandler::~CgiHandler(void)
{

}

CgiHandler	&CgiHandler::operator=(const CgiHandler &src)
{
	if (this != &src)
	{
		this->_cgi_path = src._cgi_path;
		this->_request_parser = src._request_parser;
		this->_env = src._env;
		this->_request = src._request;
		this->_response = src._response;
	}
	return (*this);
}

std::string	CgiHandler::executeCgi(void)
{
	pid_t		pid;
	int			stdin_bak = dup(STDIN_FILENO);
	int			stdout_bak = dup(STDOUT_FILENO);
	std::FILE	*file_in = std::tmpfile();
	std::FILE	*file_out = std::tmpfile();
	int			fd_in = fileno(file_in);
	int			fd_out = fileno(file_out);

	write(fd_in, _request.body.c_str(), _request.body.length());
	lseek(fd_in, 0, SET);

	pid = fork();

	if (pid == -1)
	{
		std::cout << RED << ERROR << GREEN << SERVER << NONE << " Failed to fork process" << errno << ")\n";
		return ("502");
	}
	else if (pid == 0)
	{
		
	}
}