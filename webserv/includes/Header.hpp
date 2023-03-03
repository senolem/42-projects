/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:26:20 by melones           #+#    #+#             */
/*   Updated: 2023/03/03 14:06:32 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
# define HEADER_HPP
# include "webserv.hpp"

class webserv;
class Header
{
	private:
		webserv									&_webserv;
		std::multimap<std::string, t_route>		&_vhosts;
		std::map<std::string, std::string>		_typesMap;
		std::map<int, std::string>				_errorsMap;
		
	public:
		typedef std::map<std::string, t_route>::iterator					mapIterator;
		typedef std::vector<std::multimap<std::string, t_route> >::iterator	vectorIterator;

		Header(webserv &webserv_, std::multimap<std::string, t_route> &vhosts);
		Header(const Header &src);
		~Header(void);
		Header	&operator=(const Header &src);
		
		t_request_header	parseRequest(std::string buffer);
		std::string			getResponse(t_request_header request);
		std::string			getPath(vectorIterator vectIter, std::string path);
		void				setFiletype(t_response_header *header, std::string path);
		std::string			getHeader(std::vector<std::string> header, std::string field);
		void				initErrors(void);
		void				initTypes(void);
};

#endif