/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:22:13 by albaur            #+#    #+#             */
/*   Updated: 2023/03/23 16:51:27 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP
# include "webserv.hpp"
# include "Server.hpp"
# include "Structures.hpp"
# include "Exception.hpp"

class ConfigParser
{
	private:
		std::string											_path;
		std::vector<std::string>							_configs;
		std::string											_config_string;
		std::map<std::string, t_field_traits>				_field_list;
		size_t												_nb_vhost;
		std::vector<size_t>									_pos;
		std::vector<std::multimap<std::string, t_route> >	*_vhosts;

		struct is_whitespace
		{
			bool	operator()(char c)
			{
				return (std::isspace(static_cast<unsigned char>(c)));
			}
		};
	
	public:
		ConfigParser(void);
		ConfigParser(const ConfigParser &src);
		~ConfigParser(void);
		ConfigParser	&operator=(const ConfigParser &src);

		std::vector<std::multimap<std::string, t_route> >	*init(std::string path);
	private:
		int													sanityCheck(void);
		int													prepareParsing(void);
		int													syntaxCheck(void);
		int													parseConfig(void);
		void												initFieldList(void);
		int													parseField(std::string field, t_route *route);
		void												insertField(std::vector<char *> config, t_route *route);
		t_route												*parseRoute(std::string config);
		void												fillDefault(t_route *route);
};

#endif