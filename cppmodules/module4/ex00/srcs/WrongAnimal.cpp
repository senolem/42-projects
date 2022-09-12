/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:44:51 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 12:51:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : type("Cow")
{
	std::cout << this->type << " was created!" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type) : type(type)
{
	std::cout << this->type << " was created!" << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &src)
{
	*this = src;
	std::cout << this->type << " was created!" << std::endl;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << this->type << " died!" << std::endl;
}

WrongAnimal	&WrongAnimal::operator=(WrongAnimal const &src)
{
	if (this != &src)
		this->type = src.type;
	return (*this);
}

void	WrongAnimal::makeSound(void) const
{
	std::cout << "Wrong Mooooooow 🐮" << std::endl;
}

std::string WrongAnimal::getType(void) const
{
	return (this->type);
}
