/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:35:49 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 18:19:32 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) : Form("PresidentialPardonForm", 25, 5), target("DefaultTarget")
{

}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &src) : Form(src.getName(), src.getRequiredSignGrade(), src.getRequiredExecGrade()), target(src.getTarget())
{
	if (src.getIsSigned())
		this->setSignedTrue();
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{

}

PresidentialPardonForm	&PresidentialPardonForm::operator=(const PresidentialPardonForm &src)
{
	if (this == &src)
		return (*this);
	else
	{
		std::cout << "Error : cannot assign values from a form to another because of const variables. You must instantiate a new form." << std::endl;
		return (*this);
	}	
}

std::ostream	&operator<<(std::ostream &stream, const PresidentialPardonForm &form)
{
	return (stream << "PresidentialPardonForm [" << form.getName() << "] : isSigned : " << form.getIsSigned() << " | requiredSignGrade : " << form.getRequiredSignGrade() << " | requiredExecGrade : " << form.getRequiredExecGrade());
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : Form("PresidentialPardonForm", 25, 5), target(target)
{

}

bool	PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	if (this->checkPrerequisites(executor, "PresidentialPardonForm"))
	{
		this->pardon();
		return (true);
	}
	else
		return (false);
}

std::string	PresidentialPardonForm::getTarget(void) const
{
	return (this->target);
}

void	PresidentialPardonForm::pardon(void) const
{
	std::cout << this->target << " has been forgiven by Zaphod Beeblebrox." << std::endl;
}