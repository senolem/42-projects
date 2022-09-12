/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:48:57 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 13:19:49 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void)
{
	this->type = "WrongCat";
	std::cout << this->type << " is born!" << std::endl;
}

WrongCat::WrongCat(WrongCat const &src)
{
	*this = src;
	std::cout << this->type << " is born!" << std::endl;
}

WrongCat::~WrongCat(void)
{
	std::cout << this->type << " disappeared!" << std::endl;
}

WrongCat	&WrongCat::operator=(WrongCat const &src)
{
	if (this != &src)
		this->type = src.type;
	return (*this);
}

void	WrongCat::makeSound(void) const
{
	std::cout << "Wrong Meow 🐱" << std::endl;
}
