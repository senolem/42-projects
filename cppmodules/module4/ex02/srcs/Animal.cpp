/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:42:37 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 13:18:06 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void) : type("Cow")
{
	std::cout << this->type << " was created!" << std::endl;
}

Animal::Animal(std::string type) : type(type)
{
	std::cout << this->type << " was created!" << std::endl;
}

Animal::Animal(Animal const &src)
{
	*this = src;
	std::cout << this->type << " was created!" << std::endl;
}

Animal::~Animal(void)
{
	std::cout << this->type << " died!" << std::endl;
}

Animal	&Animal::operator=(Animal const &src)
{
	if (this != &src)
		this->type = src.type;
	return (*this);
}

void	Animal::makeSound(void) const
{
	std::cout << "Mooooooow 🐮" << std::endl;
}

std::string Animal::getType(void) const
{
	return (this->type);
}
