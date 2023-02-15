/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:22:13 by albaur            #+#    #+#             */
/*   Updated: 2023/02/16 00:35:46 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP
# include "webserv.hpp"

class ConfigParser
{
	private:
		std::string					_path;
		std::vector<std::string>	_configs;
		std::string					_config_string;
	
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
			try
			{
				if (sanityCheck() || prepareParsing())
					throw Exception("Config parsing failed.");
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
			size_t					i;
			size_t					j;
			std::string::iterator	iter;

			//delete duplicate whitespace
			i = _config_string.find("#");
			while (i != std::string::npos)
			{
				j = _config_string.find("\n", i);
				_config_string.erase(i, j - i + 1);
				i = _config_string.find("#");
			}
			std::cout << _config_string << std::endl;
			return (0);
		}
};

#endif