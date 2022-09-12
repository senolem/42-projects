/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:15:09 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 15:17:19 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
{
	this->type = "Dog";
	std::cout << this->type << " appeared!" << std::endl;
	this->ideasbox = new Brain();
}

Dog::Dog(Dog const &src)
{
	delete this->ideasbox;
	this->type = src.type;
	this->ideasbox = new Brain(src.getBrain());
	std::cout << this->type << " appeared!" << std::endl;
}

Dog::~Dog(void)
{
	delete this->ideasbox;
	std::cout << this->type << " vanished!" << std::endl;
}

Dog	&Dog::operator=(Dog const &src)
{
	if (this != &src)
	{
		this->type = src.type;
		this->ideasbox = src.ideasbox;
	}
	return (*this);
}

void	Dog::makeSound(void) const
{
	std::cout << "Wouf 🐶" << std::endl;
}

void	Dog::setBrain(Brain const &src)
{
	*this->ideasbox = src;
}

Brain	&Dog::getBrain(void) const
{
	return (*this->ideasbox);
}

void	Dog::displayBrain(void) const
{
	int	i = 0;

	while (i < 100)
	{
		ideasbox->displayIdea(i);
		++i;
	}
}
