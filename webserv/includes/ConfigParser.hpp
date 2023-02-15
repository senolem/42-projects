/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:22:13 by albaur            #+#    #+#             */
/*   Updated: 2023/02/15 17:22:13 by albaur           ###   ########.fr       */
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
			if (sanityCheck(path))
				throw Exception("Config parsing failed. Check your config file syntax and try again.");
		}

	private:
		int	sanityCheck(std::string path)
		{
			struct stat			sb;
			std::ifstream		conf(path.c_str());
			std::stringstream	confstream;
			std::string			confstr;

			if (path.empty() || path.length() == 0)
			{
				printf("ConfigParser error: Empty path given.\n");
				return (1);
			}
			if (!stat(path.c_str(), &sb))
			{
				if (!(sb.st_mode & S_IFREG))
				{
					printf("ConfigParser error: Given path is not a file.\n");
					return (1);
				}
			}
			else
			{
				printf("ConfigParser error: Cannot access given path.\n");
				return (1);
			}
			if (access(path.c_str(), R_OK) != 0)
			{
				printf("ConfigParser error: Cannot access given path. Check whether if file exists and that correct permissions are set.\n");
				return (1);
			}
			if (conf)
			{
				confstream << conf.rdbuf();
				confstr = confstream.str();
				if (confstr.empty())
				{
					printf("ConfigParser error: Config file is empty.\n");
					return (1);
				}
			}
			return (0);
		}
};

#endif