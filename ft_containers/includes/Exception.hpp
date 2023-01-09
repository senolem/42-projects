/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:12:21 by albaur            #+#    #+#             */
/*   Updated: 2023/01/09 16:12:23 by albaur           ###   ########.fr       */
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