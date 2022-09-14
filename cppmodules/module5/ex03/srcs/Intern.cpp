/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:31:54 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 19:01:55 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern(void)
{

}

Intern::Intern(Intern const &src)
{
	(void)src;
}

Intern::~Intern(void)
{

}

Intern	&Intern::operator=(Intern const &src)
{
	(void)src;
	return (*this);
}

Form *Intern::makeForm(std::string name, std::string target)
{
	unsigned int	index = -1;
	Form			*ptr = NULL;
	std::string		typeMap[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	for (int i = 0; i < 3; i++)
	{
		if (!typeMap[i].compare(name))
		{
			index = i;
			break ;
		}
	}
	switch (index)
	{
		case 0:
			ptr = new ShrubberyCreationForm(target);
			std::cout << "Intern successfully created " << ptr->getName() << " form." << std::endl;
			return (ptr);
		case 1:
			ptr = new RobotomyRequestForm(target);
			std::cout << "Intern successfully created " << ptr->getName() << " form." << std::endl;
			return (ptr);
		case 2:
			ptr = new PresidentialPardonForm(target);
			std::cout << "Intern successfully created " << ptr->getName() << " form." << std::endl;
			return (ptr);
		default:
			std::cout << "Error : Unknown form type name. Please enter a valid input between : shrubbery creation|robotomy request|presidential pardon" << std::endl;
			return (ptr);
	}
}