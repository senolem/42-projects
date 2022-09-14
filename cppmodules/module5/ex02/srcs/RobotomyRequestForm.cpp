/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:36:00 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 17:54:58 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void) : Form("RobotomyRequestForm", 71, 45), target("DefaultTarget")
{

}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &src) : Form(src.getName(), src.getRequiredSignGrade(), src.getRequiredExecGrade()), target(src.getTarget())
{
	if (src.getIsSigned())
		this->setSignedTrue();
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{

}

std::ostream	&operator<<(std::ostream &stream, const RobotomyRequestForm &form)
{
	return (stream << "RobotomyRequestForm [" << form.getName() << "] : isSigned : " << form.getIsSigned() << " | requiredSignGrade : " << form.getRequiredSignGrade() << " | requiredExecGrade : " << form.getRequiredExecGrade());
}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : Form("DefaultRobotomyRequestForm", 145, 137), target(target)
{

}

void	RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	if (this->checkPrerequisites(executor, "RobotomyRequestForm"))
		this->robotomize();
}

std::string	RobotomyRequestForm::getTarget(void) const
{
	return (this->target);
}

void	RobotomyRequestForm::robotomize(void) const
{
	srand(time(NULL));
	bool	rng = (rand() % 2);

	std::cout << "*mechanical drill noises*" << std::endl;
	if (rng)
		std::cout << this->target << "'s robotomy process completed." << std::endl;
	else
		std::cout << this->target << "'s robotomy process has failed." << std::endl;
}
