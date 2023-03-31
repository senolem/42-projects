/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Structures.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:57:36 by melones           #+#    #+#             */
/*   Updated: 2023/03/31 03:54:28 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_HPP
# define STRUCTURES_HPP
# include "webserv.hpp"

typedef struct s_field_traits
{
	size_t	minimum_arguments;
	size_t	maximum_arguments;
	bool	available_location;
	bool	multi;
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
	std::pair<std::string, int>		redirect;
	s_route(void) : type(false), client_max_body_size(0), autoindex(false), upload(false), redirect(std::pair<std::string, int>("", 0))
	{
		
	}
}	t_route;

typedef struct s_route_set
{	
	bool	listen;
	bool	server_name;
	bool	access_log;
	bool	client_max_body_size;
	bool	root;
	bool	index;
	bool	methods_allowed;
	bool	autoindex;
	bool	upload;
	bool	upload_path;
	bool	redirect;
	s_route_set(void) : listen(false), server_name(false), access_log(false), client_max_body_size(false), root(false), index(false), methods_allowed(false), autoindex(false), upload(false), upload_path(false), redirect(false)
	{
		
	}
}	t_route_set;

typedef struct s_request
{
	std::string										method;
	std::string										path;
	std::string										version;
	std::string										host;
	std::multimap<float, std::string>				accept;
	std::map<std::string, std::string>				cookie;
	std::string										body;
	std::string										content_type;
	std::string										boundary;
	std::string										content_length;
	std::string										transfer_encoding;
	std::string										query;
	std::string										remote_addr;
	std::multimap<std::string, t_route>::iterator	matched_subserver;
	int												status;
	bool											autoindex;
	s_request(void) : version("HTTP/1.1"), status(0), autoindex(false)
	{
		
	}
}	t_request;

typedef struct s_response
{
	std::string					version;
	std::string					status_code;
	std::string					content_type;
	size_t						content_length;
	std::string					transfer_encoding;
	std::string					content;
	std::string					body;
	std::string					allow;
	std::vector<std::string>	set_cookie;
	std::string					location;
	s_response(void) : version("HTTP/1.1"), content_length(0), transfer_encoding("identity")
	{
		
	}
}	t_response;

typedef struct s_socket
{
	int			fd;
	sockaddr_in	sockaddr_;	
}	t_socket;

#endif
