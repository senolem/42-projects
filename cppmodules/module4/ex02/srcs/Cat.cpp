/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:14:18 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 15:17:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
{
	this->type = "Cat";
	std::cout << this->type << " is born!" << std::endl;
	this->ideasbox = new Brain();
}

Cat::Cat(Cat const &src)
{
	delete this->ideasbox;
	this->type = src.type;
	this->ideasbox = new Brain(src.getBrain());
	std::cout << this->type << " is born!" << std::endl;
}

Cat::~Cat(void)
{
	delete this->ideasbox;
	std::cout << this->type << " disappeared!" << std::endl;
}

Cat	&Cat::operator=(Cat const &src)
{
	if (this != &src)
	{
		this->type = src.type;
		this->ideasbox = src.ideasbox;
	}
	return (*this);
}

void	Cat::makeSound(void) const
{
	std::cout << "Meow 🐱" << std::endl;
}

void	Cat::setBrain(Brain const &src)
{
	*this->ideasbox = src;
}

Brain	&Cat::getBrain(void) const
{
	return (*this->ideasbox);
}

void	Cat::displayBrain(void) const
{
	int	i = 0;

	while (i < 100)
	{
		ideasbox->displayIdea(i);
		++i;
	}
}
