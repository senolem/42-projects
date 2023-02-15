/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:44:55 by albaur            #+#    #+#             */
/*   Updated: 2023/02/15 17:44:55 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP
# include <iostream>

class Exception : public std::exception
{
	private:
	std::string	msg;

	public:
	explicit Exception(const std::string &msg);
	virtual ~Exception() throw();
	virtual const char* what() const throw();
};

#endif
