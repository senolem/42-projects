/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:42:02 by albaur            #+#    #+#             */
/*   Updated: 2023/04/07 00:41:04 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"

CgiHandler::CgiHandler(std::string &cgi_path, RequestHandler &request_handler, t_request &request, t_response &response) : _cgi_path(cgi_path), _request_handler(request_handler), _request(request), _response(response)
{
	char		cwd[256];

	getcwd(cwd, sizeof(cwd));
	_script_path = cwd;
	_script_path.append("/" + _request.path);
	if (_script_path.find(".php") != std::string::npos)
		_env["REDIRECT_STATUS"] = "200";
	_env["SERVER_PROTOCOL"] = _request.version;
	_env["SERVER_PORT"] = _request.matched_subserver->second.listen;
	_env["REQUEST_METHOD"] = _request.method;
	_env["REQUEST_URI"] = _script_path;
	_env["PATH_TRANSLATED"] = _script_path;
	_env["SCRIPT_NAME"] = _cgi_path;
	_env["PATH_INFO"] = _script_path;
	_env["QUERY_STRING"] = _request.query;
	if (_request.method == "POST")
	{
		_env["CONTENT_LENGTH"] = _request.content_length;
		_env["CONTENT_TYPE"] = _request.content_type;
	}
	_env["HTTP_COOKIE"] = request.cookie;
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

void	CgiHandler::buildArgv(char **argv)
{
	if (_script_path.find(".py") != std::string::npos) // subject asks for script path as first argument but we instead need the interpreter for python
	{
		argv = new char*[3];
		argv[0] = new char[strlen(_cgi_path.c_str()) + 1];
		argv[1] = new char[strlen(_script_path.c_str()) + 1];
		std::strcpy(argv[0], _cgi_path.c_str());
		std::strcpy(argv[1], _script_path.c_str());
		argv[2] = 0;
	}
	else
	{
		argv = new char*[2];
		argv[0] = new char[_script_path.size() + 1];
		std::strcpy(argv[0], _script_path.c_str());
		argv[1] = 0;
	}
}

std::string	CgiHandler::executeCgi(void)
{
	pid_t		pid;
	t_exec_cgi	cgi;
	bool		readingDone = false;
	std::string	body;	
	int			status;

	cgi.stdin_bak = dup(STDIN_FILENO);
	cgi.stdout_bak = dup(STDOUT_FILENO);
	cgi.file_in = std::tmpfile();
	cgi.file_out = std::tmpfile();
	cgi.fd_in = fileno(cgi.file_in);
	cgi.fd_out = fileno(cgi.file_out);
	cgi.env = map_split(_env);
	if (!cgi.file_in || !cgi.file_out || !cgi.env)
	{
		if (!cgi.env)
			std::cerr << RED << ERROR << GREEN << SERV << NONE << " Failed to allocate env for cgi\n";
		else
			std::cerr << RED << ERROR << GREEN << SERV << NONE << " Failed to create temporary file for cgi\n";
		cleanCgi(cgi);
		return ("Status: 502\r\n\r\n");
	}
	if (write(cgi.fd_in, _request.body.c_str(), _request.body.length()) < 0)
	{
		cleanCgi(cgi);
		return ("Status: 502\r\n\r\n");
	}
	else
	{
		lseek(cgi.fd_in, 0, SEEK_SET);
		pid = fork();
		if (pid == -1)
		{
			std::cerr << RED << ERROR << GREEN << SERV << NONE << " Failed to fork process\n";
			cleanCgi(cgi);
			return ("Status: 502\r\n\r\n");
		}
		else if (pid == 0)
		{
			char	**argv = NULL;

			buildArgv(argv);
			dup2(cgi.fd_in, STDIN_FILENO);
			dup2(cgi.fd_out, STDOUT_FILENO);
			execve(_cgi_path.c_str(), argv, cgi.env);
			std::cerr << RED << ERROR << GREEN << SERV << NONE << " Failed to execute cgi\n";
			write(STDOUT_FILENO, "Status: 500\r\n\r\n", 16);
			cleanCgi(cgi);
			exit(1);
		}
		else
		{
			char	buffer[1024];
			if (waitpid(pid, &status, 0) == -1)
			{
				std::cerr << RED << ERROR << GREEN << SERV << NONE << " Failed to wait for child\n";
				cleanCgi(cgi);
				return ("Status: 500\r\n\r\n");
			}
			if (WEXITSTATUS(status) && WIFEXITED((status)))
			{
				std::cerr << RED << ERROR << GREEN << SERV << NONE << " Failed to execute cgi script\n";
				cleanCgi(cgi);
				return ("Status: 502\r\n\r\n");
			}
			lseek(cgi.fd_out, 0, SEEK_SET);
			while (!readingDone)
			{
				int	ret;
				memset(buffer, 0, sizeof(buffer));
				ret = read(cgi.fd_out, buffer, sizeof(buffer) - 1);
				if (ret == 0)
					readingDone = true;
				else if (ret > 0)
					body.append(buffer);
				else
				{
					cleanCgi(cgi);
					return ("Status: 502\r\n\r\n");
				}
			}
		}
	}
	cleanCgi(cgi);
	return (body);
}

void	CgiHandler::cleanCgi(t_exec_cgi &cgi)
{
	dup2(cgi.stdin_bak, STDIN_FILENO);
	dup2(cgi.stdout_bak, STDOUT_FILENO);
	std::fclose(cgi.file_in);
	std::fclose(cgi.file_out);
	close(cgi.fd_in);
	close(cgi.fd_out);
	for (size_t i = 0; cgi.env[i]; i++)
		delete[] cgi.env[i];
	delete[] cgi.env;
}
