/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:42:02 by albaur            #+#    #+#             */
/*   Updated: 2023/03/15 20:22:23 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiHandler.hpp"

CgiHandler::CgiHandler(std::string &cgi_path, RequestParser &request_parser, t_request_header &request, t_response_header &response) : _cgi_path(cgi_path), _request_parser(request_parser), _request(request), _response(response)
{
	size_t	i = 0;
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	std::string	script_path = cwd;
	script_path.append("/" + _request.path);
	_env["REDIRECT_STATUS"] = "200";
	_env["SERVER_PROTOCOL"] = _request.version;
	_env["SERVER_PORT"] = _request.matched_subserver->second.listen;
	_env["REQUEST_METHOD"] = _request.method;
	i = _request.path.find_last_of("." + _request_parser.getFiletype() + "/");
	if (i != std::string::npos)
		_env["PATH_INFO"] = _request.path.substr(i, _request.path.length());
	if (_env.find("PATH_INFO") != _env.end())
		_env["PATH_TRANSLATED"] = script_path;
	i = _request.path.find_last_of("." + _request_parser.getFiletype());
	if (i != std::string::npos)
		_env["SCRIPT_NAME"] = _request.path.substr(0, i);
	i = _request.path.find_last_of("?");
	if (i != std::string::npos)
		_env["QUERY_STRING"] = _request.path.substr(i, _request.path.length());
	_env["CONTENT_LENGTH"] = ft_itoa(_response.content.length());
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
	bool		readingDone = false;
	std::string	body;
	char		**env = map_split(_env);

	if (!file_in || !file_out || !env)
	{
		if (!env)
			std::cout << RED << ERROR << GREEN << SERVER << NONE << " Failed to allocate env for cgi (" << errno << ")\n";
		else
		std::cout << RED << ERROR << GREEN << SERVER << NONE << " Failed to create temporary file for cgi (" << errno << ")\n";
		return ("502");
	}
	//write(fd_in, _response.content.c_str(), _response.content.length()); We should pass POST arguments here :)
	lseek(fd_in, 0, SEEK_SET);

	pid = fork();

	if (pid == -1)
	{
		std::cout << RED << ERROR << GREEN << SERVER << NONE << " Failed to fork process (" << errno << ")\n";
		return ("502");
	}
	else if (pid == 0)
	{
		char	**argv = new char*[3];

		argv[0] = new char[_cgi_path.size() + 1];
		argv[1] = new char[_env["PATH_TRANSLATED"].size() + 1];
		argv[2] = new char;
		std::strcpy(argv[0], _cgi_path.c_str());
		std::strcpy(argv[1], _env["PATH_TRANSLATED"].c_str());
		argv[2] = 0;
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve(_cgi_path.c_str(), argv, env);
		std::cout << RED << ERROR << GREEN << SERVER << NONE << " Failed to execute cgi (" << errno << ")\n";
		write(STDOUT_FILENO, "500", 4);
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