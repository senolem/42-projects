/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryListing.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:09:32 by melones           #+#    #+#             */
/*   Updated: 2023/03/17 19:54:02 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTORY_LISTING_HPP
# define DIRECTORY_LISTING_HPP
# include "webserv.hpp"

class DirectoryListing
{
	public:
		DirectoryListing(void);
		DirectoryListing(const DirectoryListing &src);
		~DirectoryListing(void);
		DirectoryListing	&operator=(const DirectoryListing &src);

		std::string	getPage(void);
		void		generate(t_response_header &response, t_request_header &request);
		std::string	getSize(struct stat &st);
		std::string	getModifiedDate(struct stat &st);
};

#endif
