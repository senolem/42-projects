/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:24:48 by melones           #+#    #+#             */
/*   Updated: 2023/03/28 02:27:37 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(void)
{

}

ConfigParser::ConfigParser(const ConfigParser &src)
{
	*this = src;
}

ConfigParser::~ConfigParser(void)
{

}

ConfigParser	&ConfigParser::operator=(const ConfigParser &src)
{
	if (this != &src)
	{
		this->_path = src._path;
		this->_configs = src._configs;
	}
	return (*this);
}

std::vector<std::multimap<std::string, t_route> >	*ConfigParser::init(std::string path)
{
	_path = path;
	initFieldList();
	_nb_vhost = 0;
	if (sanityCheck() || prepareParsing() || syntaxCheck())
		throw Exception(RED + ERROR + CYAN + WEBSERV + NONE + " Config parsing failed.");
	else
	{
		if (parseConfig())
			throw Exception(RED + ERROR + CYAN + WEBSERV + NONE + " Config parsing failed.");
		return (_vhosts);
	}
}

int	ConfigParser::sanityCheck(void)
{
	struct stat			sb;
	std::stringstream	config_stream;
	std::string			config_string;
	
	if (_path.empty() || _path.length() == 0)
	{
		std::cout << "ConfigParser error: Empty path given." << std::endl;
		return (1);
	}
	if (!stat(_path.c_str(), &sb))
	{
		if (!(sb.st_mode & S_IFREG))
		{
			std::cout << "ConfigParser error: Given path is not a file." << std::endl;
			return (1);
		}
	}
	else
	{
		std::cout << "ConfigParser error: Cannot access given path." << std::endl;
		return (1);
	}
	std::ifstream	file(_path.c_str());
	if (!file.is_open())
	{
		std::cout << "ConfigParser error: Cannot access given path. Check whether if file exists and that correct permissions are set." << std::endl;
		return (1);
	}
	else
	{
		config_stream << file.rdbuf();
		file.close();
		config_string = config_stream.str();
		if (config_string.empty())
		{
			std::cout << "ConfigParser error: Config file is empty." << std::endl;
			return (1);
		}
		_config_string = config_string;
	}
	return (0);
}

int	ConfigParser::prepareParsing(void)
{
	size_t					i = 0;
	size_t					j = 0;
	std::string::iterator	iter = _config_string.begin();
	std::string::iterator	iter2 = _config_string.end();
	std::string::iterator	iter3;
	std::string::iterator	iter4;
	
	i = _config_string.find("#");
	while (i != std::string::npos)
	{
		j = _config_string.find("\n", i);
		_config_string.erase(i, j - i + 1);
		i = _config_string.find("#");
	}
	std::replace_if(_config_string.begin(), _config_string.end(), is_whitespace(), ' ');
	while (iter != iter2)
	{
		if (isspace(*iter))
		{
			iter3 = iter + 1;
			iter4 = iter - 1;
			if ((iter3 != iter2 && std::isspace(*iter3)) || *iter == '\n' || iter == _config_string.begin() \
				|| *iter3 == '{' || *iter3 == '}' || (iter != _config_string.begin() && *iter4 == '{') \
				|| (iter != _config_string.begin() && *iter4 == '}'))
			{
				_config_string.erase(iter);
				iter = _config_string.begin();
				iter2 = _config_string.end();
				continue;
			}
		}
		++iter;
	}
	i = _config_string.find("server{");
	while (i != std::string::npos)
	{
		_pos.push_back(i);
		i += 6;
		i = _config_string.find("server{", i);
		++_nb_vhost;
	}
	return (0);
}

int	ConfigParser::syntaxCheck(void)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	k = 0;
	
	if (!_nb_vhost)
	{
		std::cout << "ConfigParser error: 'server' field not found. You must declare a server by using the right field name." << std::endl;
		return (1);
	}
	i = _config_string.find("server{");
	while (i != std::string::npos)
	{
		i += 6;
		if (k < _nb_vhost - 1)
		{
			if (_config_string[_pos[k + 1] - 1] != '}')
			{
				std::cout << "ConfigParser error: Unclosed brackets. Check your syntax and try again." << std::endl;
				return (1);
			}
		}
		else if (k == _nb_vhost - 1)
		{
			if (_config_string[_config_string.size() - 1] != '}')
			{
				std::cout << "ConfigParser error: Syntax error." << std::endl;
				return (1);
			}
		}
		i = _config_string.find("server{", i);
		++k;
	}
	if (k != _nb_vhost)
	{
		std::cout << "ConfigParser error: Syntax error." << std::endl;
		return (1);
	}
	i = 0;
	k = 0;
	while (_config_string[i])
	{
		if (_config_string[i] == '{')
			++j;
		else if (_config_string[i] == '}')
			++k;
		++i;
	}
	if (j != k)
	{
		std::cout << "ConfigParser error: Unclosed brackets." << std::endl;
		return (1);
	}
	return (0);
}

int	ConfigParser::parseConfig(void)
{
	size_t	j = 0;
	size_t	k = 0;
	size_t	l = 0;
	size_t	n = 0;

	std::vector<std::multimap<std::string, t_route> >	*vhosts = new std::vector<std::multimap<std::string, t_route> >;
	std::multimap<std::string, t_route>					vhost;
	std::vector<std::string>							locations;
	
	for (size_t i = 0; i < _nb_vhost; i++)
	{
		j = k;
		if (i < _nb_vhost - 1)
			k = _pos[i + 1];
		else
			k = _config_string.size();
		_configs.push_back(_config_string.substr(j, k - j));
	}
	j = 0;
	for (size_t i = 0; i < _nb_vhost; i++)
	{
		j = _configs[i].find("server{");
		if (j == std::string::npos)
		{
			std::cout << "ConfigParser error: Cannot find server field." << std::endl;
			delete vhosts;
			return (1);
		}
		_configs[i].erase(j, 7);
		if (_configs[i][_configs[i].size() - 1] == '}')
			_configs[i].erase(_configs[i].size() - 1, 1);
		else
		{
			std::cout << "ConfigParser error: Unclosed brackets for server field." << std::endl;
			delete vhosts;
			return (1);
		}
	}
	for (size_t i = 0; i < _nb_vhost; i++)
	{
		_pos.clear();
		j = _configs[i].find("location", 0);
		while (j != std::string::npos)
		{
			j += 8;
			l = 0;
			k = j;
			while (_configs[i][k])
			{
				if (isalnum(_configs[i][k]) || _configs[i][k] == '/' || _configs[i][k] == '\\' \
					|| _configs[i][k] == '~' || _configs[i][k] == '*')
					++l;
				if (_configs[i][k] == '{')
				{
					if (k > j && l > 0)
					{
						_pos.push_back(j - 8);
						break ;
					}
					else
					{
						std::cout << "ConfigParser error: Invalid path for location field." << std::endl;
						delete vhosts;
						return (1);
					}
				}
				if (!_configs[i][k + 1])
				{
					if (_configs[i][k] == ';')
						break;
					else
					{
						std::cout << "ConfigParser error: Invalid location field syntax." << std::endl;
						delete vhosts;
						return (1);
					}
				}
				++k;
			}
			j = _configs[i].find("location", j);
		}
		for (size_t m = 0; m < _pos.size(); m++)
		{
			n = _configs[i].find("}", _pos[m]);
			if (n != std::string::npos)
				locations.push_back(_configs[i].substr(_pos[m], (n + 1) - _pos[m]));
		}
		for (size_t m = 0; m < locations.size(); m++)
		{
			size_t	o = 0;
			o = _configs[i].find(locations[m], 0);
			if (o != std::string::npos)
				_configs[i].erase(o, locations[m].size());
		}
		t_route	*route = parseRoute(_configs[i]);
		if (!route)
		{
			delete vhosts;
			return (1);
		}
		vhost.insert(std::pair<std::string, t_route>(route->server_name, *route));
		for (size_t m = 0; m < locations.size(); m++)
		{
			size_t		o = 0;
			std::string	match;
			locations[m].erase(0, 9);
			o = locations[m].find('{', 0);
			if (o != std::string::npos)
			{
				match = locations[m].substr(0, o);
				locations[m].erase(0, o + 1);
			}
			o = locations[m].find('}', 0);
			if (o != std::string::npos)
				locations[m].erase(o);
			t_route	*subroute = parseRoute(locations[m]);
			if (!subroute)
			{
				delete route;
				delete vhosts;
				return (1);
			}
			subroute->listen = route->listen;
			subroute->server_name = route->server_name;
			subroute->match = match;
			subroute->type = LOCATION;
			vhost.insert(std::pair<std::string, t_route>(route->server_name, *subroute));
			delete subroute;
		}
		delete route;
		vhosts->push_back(vhost);
		vhost.clear();
		locations.clear();
	}
	_vhosts = vhosts;
	return (0);
}

int	ConfigParser::parseField(std::string field, t_route *route)
{
	std::vector<char *>								vct;
	char											*token;
	char											*tmp;
	std::map<std::string, t_field_traits>::iterator	iter;
	t_field_traits									traits;
	char											*saveptr;

	tmp = new char[field.length() + 1];
	std::strcpy(tmp, field.data());
	token = strtok_r(tmp, " ", &saveptr);
	while (token)
	{
		vct.push_back(token);
		token = strtok_r(NULL, " ", &saveptr);
	}
	if (!vct.empty())
	{
		iter = _field_list.find(*vct.begin());
		if (iter == _field_list.end())
		{
			std::cout << "ConfigParser error: Unknown token '" << *vct.begin() << "'" << std::endl;
			delete[] tmp;
			return (1);
		}
		traits = iter->second;
		if ((vct.size() - 1 > traits.maximum_arguments && traits.maximum_arguments != 0) || vct.size() - 1 < traits.minimum_arguments)
		{
			std::cout << "ConfigParser error: Invalid number of arguments for token '" << *vct.begin() << "'" << std::endl;
			delete[] tmp;
			return (1);
		}
		insertField(vct, route);
		vct.clear();
	}
	delete[] tmp;
	return (0);
}

t_route	*ConfigParser::parseRoute(std::string config)
{
	char	*token;
	char	*tmp;
	char	*saveptr;
	t_route	*route = new t_route;
	
	tmp = new char[config.length() + 1];
	std::strcpy(tmp, config.data());
	token = strtok_r(tmp, ";", &saveptr);
	while (token)
	{
		if (parseField(token, route))
		{
			route->cgi_pass.clear();
			route->error_page.clear();
			route->index.clear();
			delete route;
			delete[] tmp;
			return (NULL);
		}
		token = strtok_r(NULL, ";", &saveptr);
	}
	fillDefault(route);
	delete[] tmp;
	return (route);
}

void	ConfigParser::initFieldList(void)
{
	_field_list["listen"] = (t_field_traits){1, 1, false, false};
	_field_list["server_name"] = (t_field_traits){1, 1, true, false};
	_field_list["access_log"] = (t_field_traits){1, 1, true, false};
	_field_list["client_max_body_size"] = (t_field_traits){1, 1, true, false};
	_field_list["error_page"] = (t_field_traits){2, 2, true, false};
	_field_list["root"] = (t_field_traits){1, 1, true, true};
	_field_list["index"] = (t_field_traits){1, 0, true, true};
	_field_list["methods_allowed"] = (t_field_traits){1, 4, true, true};
	_field_list["autoindex"] = (t_field_traits){1, 1, true, true};
	_field_list["cgi_pass"] = (t_field_traits){2, 2, true, true};
	_field_list["upload"] = (t_field_traits){1, 1, true, true};
	_field_list["upload_path"] = (t_field_traits){1, 1, true, true};
}

void	ConfigParser::insertField(std::vector<char *> config, t_route *route)
{
	std::vector<std::string>		vct;
	std::vector<char *>::iterator	iter = config.begin() + 1;
	std::vector<char *>::iterator	iter2 = config.end();
	
	std::string	field(*config.begin());
	if (field == "listen")
		route->listen = *iter;
	else if (field == "server_name")
		route->server_name = *iter;
	else if (field == "access_log")
		route->access_log = *iter;
	else if (field == "client_max_body_size")
		route->client_max_body_size = atoi(*iter);
	else if (field == "error_page")
		route->error_page.insert(std::pair<int, std::string>(atoi(*iter), *(iter + 1)));
	else if (field == "root")
		route->root = *iter;
	else if (field == "index")
	{
		while (iter != iter2)
		{
			vct.push_back(*iter);
			++iter;
		}
		route->index = vct;
		vct.clear();
	}
	else if (field == "methods_allowed")
	{
		while (iter != iter2)
		{
			std::string	tmp(*iter);
			if (tmp == "GET")
				route->methods_allowed.get = true;
			else if (tmp == "POST")
				route->methods_allowed.post = true;
			else if (tmp == "DELETE")
				route->methods_allowed.del = true;
			else if (tmp == "HEAD")
				route->methods_allowed.head = true;
			++iter;
		}
	}
	else if (field == "autoindex")
	{
		std::string	tmp(*iter);
		if (tmp == "on")
			route->autoindex = true;
		else if (tmp == "off")
			route->autoindex = false;
	}
	else if (field == "cgi_pass")
		route->cgi_pass.insert(std::pair<std::string, t_cgi>(*iter, (t_cgi){*iter, *(iter + 1)}));
	else if (field == "upload")
	{
		std::string	tmp(*iter);
		if (tmp == "on")
			route->upload = true;
		else if (tmp == "off")
			route->upload = false;
	}
	else if (field == "upload_path")
	{
		char	cwd[256];
		getcwd(cwd, sizeof(cwd));
		std::string	cwd_str(cwd);
		route->upload_path = cwd_str + "/" + *iter;
	}
}

void	ConfigParser::fillDefault(t_route *route)
{
	if (route->listen.empty())
		route->listen = "80";
	if (route->access_log.empty())
		route->access_log = "logs/access.log";
	if (route->client_max_body_size == -1)
		route->client_max_body_size = 1000000;
	route->error_page.insert(std::pair<int, std::string>(400, "default_error/400.html"));
	route->error_page.insert(std::pair<int, std::string>(401, "default_error/401.html"));
	route->error_page.insert(std::pair<int, std::string>(403, "default_error/403.html"));
	route->error_page.insert(std::pair<int, std::string>(404, "default_error/404.html"));
	route->error_page.insert(std::pair<int, std::string>(405, "default_error/405.html"));
	route->error_page.insert(std::pair<int, std::string>(406, "default_error/406.html"));
	route->error_page.insert(std::pair<int, std::string>(408, "default_error/408.html"));
	route->error_page.insert(std::pair<int, std::string>(409, "default_error/409.html"));
	route->error_page.insert(std::pair<int, std::string>(410, "default_error/410.html"));
	route->error_page.insert(std::pair<int, std::string>(411, "default_error/411.html"));
	route->error_page.insert(std::pair<int, std::string>(412, "default_error/412.html"));
	route->error_page.insert(std::pair<int, std::string>(413, "default_error/413.html"));
	route->error_page.insert(std::pair<int, std::string>(414, "default_error/414.html"));
	route->error_page.insert(std::pair<int, std::string>(415, "default_error/415.html"));
	route->error_page.insert(std::pair<int, std::string>(416, "default_error/416.html"));
	route->error_page.insert(std::pair<int, std::string>(417, "default_error/417.html"));
	route->error_page.insert(std::pair<int, std::string>(421, "default_error/421.html"));
	route->error_page.insert(std::pair<int, std::string>(428, "default_error/428.html"));
	route->error_page.insert(std::pair<int, std::string>(429, "default_error/429.html"));
	route->error_page.insert(std::pair<int, std::string>(431, "default_error/431.html"));
	route->error_page.insert(std::pair<int, std::string>(500, "default_error/500.html"));
	route->error_page.insert(std::pair<int, std::string>(501, "default_error/501.html"));
	route->error_page.insert(std::pair<int, std::string>(502, "default_error/502.html"));
	route->error_page.insert(std::pair<int, std::string>(503, "default_error/503.html"));
	route->error_page.insert(std::pair<int, std::string>(504, "default_error/504.html"));
	route->error_page.insert(std::pair<int, std::string>(505, "default_error/505.html"));
	route->error_page.insert(std::pair<int, std::string>(511, "default_error/511.html"));
	if (route->index.empty())
	{
		std::vector<std::string>	vct;
		vct.push_back("index.html");
		route->index = vct;
		vct.clear();
	}
}
