/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Structures.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:57:36 by melones           #+#    #+#             */
/*   Updated: 2023/02/20 17:15:04 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_HPP
# define STRUCTURES_HPP
# include "webserv.hpp"

namespace ft {
	typedef struct s_field_traits
	{
		size_t	minimum_arguments;
		size_t	maximum_arguments;
		bool	optional;
		bool	available_location;
	}	t_field_traits;
	
	enum routes_type
	{
		SERVER = 0,
		LOCATION
	};
	
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
	
	typedef struct s_route
	{	
		bool							type;
		std::vector<std::string>		listen;
		std::vector<std::string>		server_name;
		std::string						access_log;
		size_t							client_max_body_size;
		std::map<int, std::string>		error_page;
		std::string						root;
		std::vector<std::string>		index;
		t_methods						methods_allowed;
		bool							autoindex;
		std::map<std::string, t_cgi>    cgi_pass;
		bool							upload;
		std::string						upload_path;

		s_route(void) : type(false), access_log(""), client_max_body_size(0), root(""), methods_allowed(), autoindex(false), upload(false), upload_path("")
		{
			
		}
	}	t_route;
}

#endif