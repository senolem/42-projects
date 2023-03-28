/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:22:13 by albaur            #+#    #+#             */
/*   Updated: 2023/03/28 18:13:52 by melones          ###   ########.fr       */
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
		std::string											_exception;
		std::string											_server_id;
		std::string											_route_id;
		std::vector<int>									_ports;

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
		int		sanityCheck(void);
		int		prepareParsing(void);
		int		syntaxCheck(void);
		int		duplicatePortCheck(void);
		int		parseConfig(void);
		int		parseField(std::string field, t_route *route, t_route_set *route_set, int type);
		t_route	*parseRoute(std::string config, int type);
		void	initFieldList(void);
		int		insertField(std::vector<char *> config, t_route *route, t_route_set *route_set);
		void	fillDefault(t_route *route);
		int		checkRouteSet(std::vector<char *> config, t_route_set route_set);
		int		checkRouteUnset(t_route_set route_set, int type);
};

#endif