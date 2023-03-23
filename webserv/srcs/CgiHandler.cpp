/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:42:02 by albaur            #+#    #+#             */
/*   Updated: 2023/03/23 20:44:45 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"

CgiHandler::CgiHandler(std::string &cgi_path, RequestHandler &request_handler, t_request &request, t_response &response) : _cgi_path(cgi_path), _request_handler(request_handler), _request(request), _response(response)
{
	size_t		i = 0;
	char		cwd[256];

	getcwd(cwd, sizeof(cwd));
	_script_path = cwd;
	_script_path.append("/" + _request.path);
	_env["REDIRECT_STATUS"] = "200";
	_env["SERVER_PROTOCOL"] = _request.version;
	_env["SERVER_PORT"] = _request.matched_subserver->second.listen;
	_env["REQUEST_METHOD"] = _request.method;
	i = _request.path.find_last_of("." + _request_handler.getFiletype() + "/");
	if (i != std::string::npos)
		_env["PATH_INFO"] = _request.path.substr(i + 1, _request.path.length() - i + 1);
	_env["PATH_TRANSLATED"] = _script_path;
	i = _request.path.find_last_of("." + _request_handler.getFiletype());
	if (i != std::string::npos)
		_env["SCRIPT_NAME"] = _request.path.substr(0, i + 1);
	_env["QUERY_STRING"] = _request.query;
	_env["CONTENT_LENGTH"] = _request.content_length;
	_env["CONTENT_TYPE"] = _request.content_type;
	_env["HTTP_COOKIE"] = parseCookie(request.cookie);
	_env["REMOTE_ADDR"] = _request.remote_addr;
	_env["SERVER_NAME"] = _request.matched_subserver->second.server_name;
	_env["SERVER_SOFTWARE"] = "Webserv/1.0";
	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
}

CgiHandler::CgiHandler(const CgiHandler &src) : _cgi_path(src._cgi_path), _request_handler(src._request_handler), _request(src._request), _response(src._response)
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
		this->_request_handler = src._request_handler;
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
	bool		readingDone = false;
	std::string	body;
	char		**env = map_split(_env);
	int			status;

	if (!file_in || !file_out || !env)
	{
		if (!env)
			std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to allocate env for cgi (" << errno << ")\n";
		else
			std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to create temporary file for cgi (" << errno << ")\n";
		return ("Status: 502\r\n\r\n");
	}
	write(fd_in, _request.body.c_str(), _request.body.length());
	lseek(fd_in, 0, SEEK_SET);
	pid = fork();
	if (pid == -1)
	{
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to fork process (" << errno << ")\n";
		return ("Status: 502\r\n\r\n");
	}
	else if (pid == 0)
	{
		char	**argv = new char*[2];

		argv[0] = new char[_script_path.size() + 1];
		argv[1] = new char;
		std::strcpy(argv[0], _script_path.c_str());
		argv[1] = 0;
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve(_cgi_path.c_str(), argv, env);
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to execute cgi (" << errno << ")\n";
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 16);
		exit(1);
	}
	else
	{
		char	buffer[1024];

		if (waitpid(pid, &status, 0) == -1)
		{
			std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to wait for child (" << errno << ")\n";
			return ("Status: 500\r\n\r\n");
		}
		if (WEXITSTATUS(status) && WIFEXITED((status)))
		{
			std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to execute cgi script (" << errno << ")\n";
			return ("Status: 502\r\n\r\n");
		}
		lseek(fd_out, 0, SEEK_SET);
		while (!readingDone)
		{
			memset(buffer, 0, sizeof(buffer));
			if (read(fd_out, buffer, sizeof(buffer) - 1) <= 0)
				readingDone = true;
			body.append(buffer);
		}
	}
	dup2(stdin_bak, STDIN_FILENO);
	dup2(stdout_bak, STDOUT_FILENO);
	std::fclose(file_in);
	std::fclose(file_out);
	close(fd_in);
	close(fd_out);
	for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;
	return (body);
}

std::string	CgiHandler::parseCookie(const std::map<std::string, std::string> &cookies)
{
	std::map<std::string, std::string>::const_iterator	iter = cookies.begin();
	std::map<std::string, std::string>::const_iterator	iter2 = cookies.end();
	std::string											parsedCookies;

	while (iter != iter2)
	{
		parsedCookies.append("HTTP_" + iter->first + "=" + iter->second);
		if (++iter != iter2)
			parsedCookies.append("&");
	}
	return (parsedCookies);
}
