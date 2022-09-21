/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:12:23 by albaur            #+#    #+#             */
/*   Updated: 2022/09/21 10:37:09 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

std::string	Contact::fields[5] = {
	"First name",
	"Last name",
	"Nickname",
	"Phone number",
	"Darkest secret"
};

std::string	Contact::getInfo(size_t i) const
{
	return (this->infos[i]);
}

void	Contact::setInfo(std::string str, size_t i)
{
	this->infos[i] = str;
}