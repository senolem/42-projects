/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:22:13 by albaur            #+#    #+#             */
/*   Updated: 2023/02/15 18:55:59 by melones          ###   ########.fr       */
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
			try
			{
				if (sanityCheck(path))
					throw Exception("Config parsing failed.");
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
			}
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
				std::cout << "ConfigParser error: Empty path given." << std::endl;
				return (1);
			}
			if (!stat(path.c_str(), &sb))
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
			if (access(path.c_str(), R_OK) != 0)
			{
				std::cout << "ConfigParser error: Cannot access given path. Check whether if file exists and that correct permissions are set." << std::endl;
				return (1);
			}
			if (conf)
			{
				confstream << conf.rdbuf();
				confstr = confstream.str();
				if (confstr.empty())
				{
					std::cout << "ConfigParser error: Config file is empty." << std::endl;
					return (1);
				}
			}
			return (0);
		}
};

#endif