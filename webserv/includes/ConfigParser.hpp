/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:22:13 by albaur            #+#    #+#             */
/*   Updated: 2023/02/17 15:06:17 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP
# include "webserv.hpp"
# include "Server.hpp"

typedef struct s_methods
{
	bool	get;
	bool	post;
}	t_methods;

typedef struct s_cgi
{
	std::string	filetype;
	std::string	path;
	t_methods	methods_allowed;
}	t_cgi;

typedef struct s_field_traits
{
	size_t	minimum_arguments;
	size_t	maximum_arguments;
	bool	optional;
}	t_field_traits;

typedef struct s_location
{
	std::string		path;
	std::string		root;
	bool			autoindex;
	t_methods		methods_allowed;
	t_cgi			cgi_pass;
	bool			upload;
	std::string		upload_path;
}	t_location;

class ConfigParser
{
	private:
		std::string								_path;
		std::vector<std::string>				_configs;
		std::string								_config_string;
		std::map<std::string, t_field_traits>	_field_list;
		size_t									_nb_servers;
		std::vector<size_t>						_pos;
	
	public:
		ConfigParser(void)
		{

		}

		ConfigParser(const ConfigParser &src)
		{
			*this = src;
		}

		~ConfigParser(void)
		{
			
		}

		ConfigParser	&operator=(const ConfigParser &src)
		{
			if (this != &src)
			{
				this->_path = src._path;
				this->_configs = src._configs;
			}
			return (*this);
		}

		void	init(std::string path)
		{
			_path = path;
			initFieldList();
			_nb_servers = 0;
			try
			{
				if (sanityCheck() || prepareParsing() || syntaxCheck())
					throw Exception("Config parsing failed.");
				else
				{
					std::cout << "CONFIG OK" << std::endl;
					parseConfig();
					printConfig();
				}
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}

	private:
		int	sanityCheck(void)
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
			if (access(_path.c_str(), R_OK) != 0)
			{
				std::cout << "ConfigParser error: Cannot access given path. Check whether if file exists and that correct permissions are set." << std::endl;
				return (1);
			}
			std::ifstream	conf(_path.c_str());
			if (conf)
			{
				config_stream << conf.rdbuf();
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

		int	prepareParsing(void)
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
			while (iter != iter2)
			{
				if (isspace(*iter))
				{
					iter3 = iter + 1;
					iter4 = iter - 1;
					if ((iter3 != iter2 && isspace(*iter3)) || *iter == '\n' || iter == _config_string.begin() \
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
				++_nb_servers;
			}
			return (0);
		}

		int	syntaxCheck(void)
		{
			size_t	i = 0;
			size_t	j = 0;
			size_t	k = 0;

			if (!_nb_servers)
			{
				std::cout << "ConfigParser error: 'server' field not found. You must declare a server by using the right field name." << std::endl;
				return (1);
			}
			i = _config_string.find("server{");
			while (i != std::string::npos)
			{
				i += 6;
				if (k < _nb_servers - 1)
				{
					if (_config_string[_pos[k + 1] - 1] != '}')
					{
						std::cout << "ConfigParser error: Unclosed brackets. Check your syntax and try again." << std::endl;
						return (1);
					}
				}
				else if (k == _nb_servers - 1)
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
			
			if (k != _nb_servers)
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

		int	parseConfig(void)
		{
			size_t	j = 0;
			size_t	k = 0;
			size_t	l = 0;

			for (size_t i = 0; i < _nb_servers; i++)
			{
				j = k;
				if (i < _nb_servers - 1)
					k = _pos[i + 1];
				else
					k = _config_string.size();
				_configs.push_back(_config_string.substr(j, k - j));
			}
			// each server is now splitted. need to parse into map now
			j = 0;
			for (size_t i = 0; i < _nb_servers; i++)
			{
				j = _configs[i].find("server{");
				if (j == std::string::npos)
				{
					std::cout << "ConfigParser error: Cannot find server field." << std::endl;
					return (1);
				}
				_configs[i].erase(j, 7);
				if (_configs[i][_configs[i].size() - 1] == '}')
					_configs[i].erase(_configs[i].size() - 1, 1);
				else
				{
					std::cout << "ConfigParser error: Unclosed brackets for server field." << std::endl;
					return (1);
				}
			}
			for (size_t i = 0; i < _nb_servers; i++)
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
								return (1);
							}
						}
						++k;
					}
					j = _configs[i].find("location", j);
				}
				for (size_t m = 0; m < _pos.size(); m++)
				{

				}
			}
			return (0);
		}

		void	printConfig(void)
		{
			std::vector<std::string>::iterator	iter = _configs.begin();
			std::vector<std::string>::iterator	iter2 = _configs.end();

			while (iter != iter2)
			{
				std::cout << *iter << std::endl;
				std::cout << "__________________________________________________" << std::endl;
				++iter;
			}
		}

		void	initFieldList(void)
		{
			_field_list.insert(std::pair<std::string, t_field_traits>("listen", (t_field_traits){1, 1, false}));
			_field_list.insert(std::pair<std::string, t_field_traits>("server_name", (t_field_traits){1, 1, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("access_log", (t_field_traits){1, 1, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("client_max_body_size", (t_field_traits){1, 1, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("error_page", (t_field_traits){2, 2, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("root", (t_field_traits){1, 1, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("index", (t_field_traits){1, 1, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("methods_allowed", (t_field_traits){1, 2, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("autoindex", (t_field_traits){1, 1, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("cgi_pass", (t_field_traits){1, 4, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("upload", (t_field_traits){1, 1, true}));
			_field_list.insert(std::pair<std::string, t_field_traits>("upload_path", (t_field_traits){1, 1, true}));
		}
};

#endif