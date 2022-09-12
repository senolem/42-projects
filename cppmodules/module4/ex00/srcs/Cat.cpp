/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:14:18 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 14:39:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
{
	this->type = "Cat";
	std::cout << this->type << " is born!" << std::endl;
}

Cat::Cat(Cat const &src)
{
	this->type = src.type;
	std::cout << this->type << " is born!" << std::endl;
}

Cat::~Cat(void)
{
	std::cout << this->type << " disappeared!" << std::endl;
}

Cat	&Cat::operator=(Cat const &src)
{
	if (this != &src)
		this->type = src.type;
	return (*this);
}

void	Cat::makeSound(void) const
{
	std::cout << "Meow 🐱" << std::endl;
}
