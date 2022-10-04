/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:23:51 by albaur            #+#    #+#             */
/*   Updated: 2022/10/04 16:14:04 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"

Exception::Exception(const std::string &msg)
{
	this->msg = msg;
}

Exception::~Exception() throw()
{

}

const char *Exception::what() const throw()
{
	return (msg.c_str());
}
