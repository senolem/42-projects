/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:42:02 by albaur            #+#    #+#             */
/*   Updated: 2023/03/16 01:12:59 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"

CgiHandler::CgiHandler(std::string &cgi_path, RequestParser &request_parser, t_request_header &request, t_response_header &response) : _cgi_path(cgi_path), _request_parser(request_parser), _request(request), _response(response)
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
	i = _request.path.find_last_of("." + _request_parser.getFiletype() + "/");
	if (i != std::string::npos)
		_env["PATH_INFO"] = _request.path.substr(i + 1, _request.path.length() - i + 1);
	_env["PATH_TRANSLATED"] = _script_path;
	i = _request.path.find_last_of("." + _request_parser.getFiletype());
	if (i != std::string::npos)
		_env["SCRIPT_NAME"] = _request.path.substr(0, i + 1);
	_env["QUERY_STRING"] = _request.query;
	_env["CONTENT_LENGTH"] = _request.content_length;
	_env["CONTENT_TYPE"] = _request.content_type;

	std::cout << "ENV VAR : \n";
	for (std::map<std::string, std::string>::iterator iter = _env.begin(); iter != _env.end(); iter++)
	{
		std::cout << iter->first << " = " << iter->second << "\n";
	}
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
	bool		readingDone = false;
	std::string	body;
	char		**env = map_split(_env);

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
		char	**argv = new char*[3];

		argv[0] = new char[_cgi_path.size() + 1];
		argv[1] = new char[_script_path.size() + 1];
		argv[2] = new char;
		std::strcpy(argv[0], _cgi_path.c_str());
		std::strcpy(argv[1], _script_path.c_str());
		argv[2] = 0;
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve(_cgi_path.c_str(), argv, env);
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to execute cgi (" << errno << ")\n";
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 4);
		exit(1);
	}
	else
	{
		char	buffer[1024];

		waitpid(pid, NULL, 0);
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