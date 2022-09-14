/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:35:49 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 17:54:51 by albaur           ###   ########.fr       */
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

std::ostream	&operator<<(std::ostream &stream, const PresidentialPardonForm &form)
{
	return (stream << "PresidentialPardonForm [" << form.getName() << "] : isSigned : " << form.getIsSigned() << " | requiredSignGrade : " << form.getRequiredSignGrade() << " | requiredExecGrade : " << form.getRequiredExecGrade());
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : Form("DefaultPresidentialPardonForm", 145, 137), target(target)
{

}

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	if (this->checkPrerequisites(executor, "PresidentialPardonForm"))
		this->pardon();
}

std::string	PresidentialPardonForm::getTarget(void) const
{
	return (this->target);
}

void	PresidentialPardonForm::pardon(void) const
{
	std::cout << this->target << " has been forgiven by Zaphod Beeblebrox." << std::endl;
}