/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:22:13 by albaur            #+#    #+#             */
/*   Updated: 2023/02/20 22:29:00 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP
# include "webserv.hpp"
# include "Server.hpp"
# include "Structures.hpp"
# include "Exception.hpp"

namespace ft
{
	class ConfigParser
	{
		private:
			std::string									_path;
			std::vector<std::string>					_configs;
			std::string									_config_string;
			std::map<std::string, t_field_traits>		_field_list;
			size_t										_nb_servers;
			std::vector<size_t>							_pos;
			std::vector<std::map<int, ft::t_route> >	*_servers;
		
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
	
			std::vector<std::map<int, ft::t_route> >	*init(std::string path)
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
						//printConfig();
						return (_servers);
					}
				}
				catch (std::exception &e)
				{
					std::cerr << e.what() << std::endl;
				}
				return (NULL);
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

				std::vector<std::map<int, t_route> >	*servers = new std::vector<std::map<int, t_route> >;
				std::map<int, t_route>					vhosts;
				t_route									server;
				size_t									n = 0;
				std::vector<std::string>				locations;
	
				for (size_t i = 0; i < _nb_servers; i++)
				{
					j = k;
					if (i < _nb_servers - 1)
						k = _pos[i + 1];
					else
						k = _config_string.size();
					_configs.push_back(_config_string.substr(j, k - j));
				}
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
						n = _configs[i].find("}", _pos[m]);
						if (n != std::string::npos)
							locations.push_back(_configs[i].substr(_pos[m], (n + 1) - _pos[m]));
					}
					for (size_t m = 0; m < locations.size(); m++)
					{
						size_t	o = 0;
						o = _configs[i].find(locations[m], 0);
						if (o != std::string::npos)
						{
							_configs[i].erase(o, locations[m].size());
						}
						else
							printf("not found\n");
					}
					locations.clear();
					parseRoute(_configs[i], &server);
					vhosts.insert(std::pair<int, t_route>(0, server));
					// parse location route here
					servers->push_back(vhosts);
				}
				_servers = servers;
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
				_field_list.insert(std::pair<std::string, t_field_traits>("listen", (t_field_traits){1, 1, false, false}));
				_field_list.insert(std::pair<std::string, t_field_traits>("server_name", (t_field_traits){1, 1, true, false}));
				_field_list.insert(std::pair<std::string, t_field_traits>("access_log", (t_field_traits){1, 1, true, false}));
				_field_list.insert(std::pair<std::string, t_field_traits>("client_max_body_size", (t_field_traits){1, 1, true, false}));
				_field_list.insert(std::pair<std::string, t_field_traits>("error_page", (t_field_traits){2, 2, true, false}));
				_field_list.insert(std::pair<std::string, t_field_traits>("root", (t_field_traits){1, 1, true, true}));
				_field_list.insert(std::pair<std::string, t_field_traits>("index", (t_field_traits){1, 0, true, true}));
				_field_list.insert(std::pair<std::string, t_field_traits>("methods_allowed", (t_field_traits){1, 2, true, true}));
				_field_list.insert(std::pair<std::string, t_field_traits>("autoindex", (t_field_traits){1, 1, true, true}));
				_field_list.insert(std::pair<std::string, t_field_traits>("cgi_pass", (t_field_traits){1, 4, true, true}));
				_field_list.insert(std::pair<std::string, t_field_traits>("upload", (t_field_traits){1, 1, true, true}));
				_field_list.insert(std::pair<std::string, t_field_traits>("upload_path", (t_field_traits){1, 1, true, true}));
			}

			int	parseField(std::string field, t_route *route)
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
						return (1);
					}
					traits = iter->second;
					if ((vct.size() - 1 > traits.maximum_arguments && traits.maximum_arguments != 0)|| vct.size() - 1 < traits.minimum_arguments)
					{
						std::cout << "ConfigParser error: Invalid number of arguments for token '" << *vct.begin() << "'" << std::endl;
						return (1);
					}
					insertField(vct, route);
					vct.clear();
				}
				else
				{
					std::cout << "ConfigParser error: empty token." << std::endl;
					return (1);
				}
				delete[] tmp;
				return (0);
			}

			void	insertField(std::vector<char *> config, t_route *route)
			{
				std::vector<std::string>		vct;
				std::vector<char *>::iterator	iter = config.begin() + 1;
				std::vector<char *>::iterator	iter2 = config.end();
				
				std::string	field(*config.begin());
				if (field == "listen")
				{
					while (iter != iter2)
					{
						vct.push_back(*iter);
						++iter;
					}
					route->listen = vct;
					vct.clear();
				}
				else if (field == "server_name")
				{
					while (iter != iter2)
					{
						vct.push_back(*iter);
						++iter;
					}
					route->server_name = vct;
					vct.clear();
				}
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
						++iter;
					}
					route->server_name = vct;
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
				{
					t_methods						methods;
					std::vector<char *>::iterator	iter3 = config.begin() + 2;
					
					while (iter3 != iter2)
					{
						std::string	tmp(*iter3);
						if (tmp == "GET")
							methods.get = true;
						else if (tmp == "POST")
							methods.post = true;
						++iter3;
					}
					route->cgi_pass.insert(std::pair<std::string, t_cgi>(*iter, (t_cgi){*iter, *(iter + 1), methods}));
				}
				else if (field == "upload")
				{
					std::string	tmp(*iter);
					if (tmp == "on")
						route->upload = true;
					else if (tmp == "off")
						route->upload = false;
				}
				else if (field == "upload_path")
					route->upload = *iter;
			}

			void	parseRoute(std::string config, t_route *route)
			{
				char	*token;
				char	*tmp;
				char	*saveptr;
				
				tmp = new char[config.length() + 1];
				std::strcpy(tmp, config.data());
				token = strtok_r(tmp, ";", &saveptr);
				while (token)
				{
					parseField(token, route);
					token = strtok_r(NULL, ";", &saveptr);
				}
				delete[] tmp;
			}
	};
}

#endif