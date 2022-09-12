/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:15:09 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 14:39:31 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
{
	this->type = "Dog";
	std::cout << this->type << " appeared!" << std::endl;
}

Dog::Dog(Dog const &src)
{
	this->type = src.type;
	std::cout << this->type << " appeared!" << std::endl;
}

Dog::~Dog(void)
{
	std::cout << this->type << " vanished !" << std::endl;
}

Dog	&Dog::operator=(Dog const &src)
{
	if (this != &src)
		this->type = src.type;
	return (*this);
}

void	Dog::makeSound(void) const
{
	std::cout << "Wouf 🐶" << std::endl;
}
