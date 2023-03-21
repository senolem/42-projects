/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryListing.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:09:32 by melones           #+#    #+#             */
/*   Updated: 2023/03/21 15:25:10 by albaur           ###   ########.fr       */
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
		void		generate(t_response &response, t_request &request);
		std::string	getSize(struct stat &st);
		std::string	getModifiedDate(struct stat &st);
};

#endif
