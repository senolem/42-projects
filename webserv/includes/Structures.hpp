/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Structures.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:57:36 by melones           #+#    #+#             */
/*   Updated: 2023/03/18 04:46:30 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_HPP
# define STRUCTURES_HPP
# include "webserv.hpp"

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
	bool	head;

	s_methods(void) : get(false), post(false), del(false),  head(false)
	{
		
	}
}	t_methods;

typedef struct s_cgi
{
	std::string	filetype;
	std::string	path;
}	t_cgi;

typedef struct s_route
{	
	bool							type;
	std::string						listen;
	std::string						server_name;
	std::string						access_log;
	ssize_t							client_max_body_size;
	std::map<int, std::string>		error_page;
	std::string						root;
	std::vector<std::string>		index;
	t_methods						methods_allowed;
	bool							autoindex;
	std::map<std::string, t_cgi>    cgi_pass;
	bool							upload;
	std::string						upload_path;
	std::string						match;
	s_route(void) : type(false), access_log(""), client_max_body_size(-1), root(""), methods_allowed(), autoindex(false), upload(false), upload_path("")
	{
		
	}
}	t_route;

typedef struct s_request_header
{
	std::string										method;
	std::string										path;
	std::string										version;
	std::string										host;
	std::multimap<float, std::string>				accept;
	std::map<std::string, std::string>				cookie;
	std::string										body;
	std::string										content_type;
	std::string										content_length;
	std::string										query;
	std::multimap<std::string, t_route>::iterator	matched_subserver;
	int												status;
	bool											autoindex;
	s_request_header(void) : method(""), path (""), version("HTTP/1.1"), host(""), status(0), autoindex(false)
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
	std::string	body;
	s_response_header(void) : version("HTTP/1.1"), status_code(""), content_type(""), content_length(0), content("")
	{
		
	}
}	t_response_header;

typedef struct s_socket
{
	int			fd;
	sockaddr_in	sockaddr_;	
}	t_socket;

#endif
