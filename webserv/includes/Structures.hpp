/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Structures.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:57:36 by melones           #+#    #+#             */
/*   Updated: 2023/02/24 17:00:46 by albaur           ###   ########.fr       */
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
		bool	del;
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
		std::string						listen;
		std::string						server_name;
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
		std::string						match;

		s_route(void) : type(false), access_log(""), client_max_body_size(0), root(""), methods_allowed(), autoindex(false), upload(false), upload_path("")
		{
			
		}
	}	t_route;

	typedef struct s_request_header
	{
		std::string	method;
		std::string	path;
		std::string	version;
		std::string	host;

		s_request_header(void) : method(""), path (""), version("HTTP/1.1"), host("")
		{
			
		}
	}	t_request_header;

	typedef struct s_response_header
	{
		std::string	version;
		std::string	status_code;
		std::string	content_type;
		size_t		content_length;
		std::string	content;

		s_response_header(void) : version("HTTP/1.1"), status_code(""), content_type(""), content_length(0), content("")
		{
			
		}
	}	t_response_header;
}

#endif