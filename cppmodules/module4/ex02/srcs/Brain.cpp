/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:39:23 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 14:28:09 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(void)
{
	int	i = 0;
	
	while (i < 100)
	{
		this->ideas[i] = "This is an idea.";
		++i;
	}
	std::cout << "New brain produced..." << std::endl;
}

Brain::Brain(Brain const &src)
{
	int	i = 0;
	
	while (i < 100)
	{
		this->ideas[i] = src.ideas[i];
		++i;
	}
	std::cout << "New brain cloned..." << std::endl;
}

Brain::~Brain(void)
{
	std::cout << "Brain destroyed!" << std::endl;
}

Brain &Brain::operator=(Brain const &src)
{
	if (this != &src)
	{
		int	i = 0;
		
		while (i < 100)
		{
			this->ideas[i] = src.ideas[i];
			++i;
		}
	}
	return (*this);
}

void	Brain::setIdea(std::string const &idea, int i)
{
	if (i < 0 || i >= 100)
	{
		std::cout << "index out of range !" << std::endl;
		return ;
	}
	this->ideas[i] = idea;
}

void	Brain::displayIdea(int const i)
{
	std::cout << this->ideas[i] << std::endl;
}
