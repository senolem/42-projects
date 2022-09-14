/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:52:18 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 18:17:33 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(void) : name("Default Form name"), requiredSignGrade(150), requiredExecGrade(150)
{
	this->isSigned = false;
}

Form::Form(Form const &src) : name(src.getName()), requiredSignGrade(src.getRequiredSignGrade()), requiredExecGrade(src.getRequiredExecGrade())
{
	this->isSigned = src.isSigned;
}

Form::~Form(void)
{
	std::cout << "The recycle bin ate your form." << std::endl;
}

Form	&Form::operator=(const Form &src)
{
	if (this == &src)
		return (*this);
	else
	{
		std::cout << "Error : cannot assign values from a form to another because of const variables. You must instantiate a new form." << std::endl;
		return (*this);
	}	
}

std::ostream	&operator<<(std::ostream &stream, const Form &form)
{
	return (stream << "Form [" << form.getName() << "] : isSigned : " << form.getIsSigned() << " | requiredSignGrade : " << form.getRequiredSignGrade() << " | requiredExecGrade : " << form.getRequiredExecGrade());
}

Form::Form(std::string name, unsigned int requiredSignGrade, unsigned int requiredExecGrade) : name(name), requiredSignGrade(requiredSignGrade), requiredExecGrade(requiredExecGrade)
{
	this->isSigned = false;
	try
	{
		if (requiredSignGrade > 150 || requiredExecGrade > 150)
			throw Exception("Form::GradeTooLowException");
		else if (requiredSignGrade < 1 || requiredExecGrade < 1)
			throw Exception("Form::GradeTooHighException");
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::string	Form::getName(void) const
{
	return (this->name);
}

bool	Form::getIsSigned(void) const
{
	return (this->isSigned);
}

unsigned int	Form::getRequiredSignGrade(void) const
{
	return (this->requiredSignGrade);
}

unsigned int	Form::getRequiredExecGrade(void) const
{
	return (this->requiredExecGrade);
}

void	Form::beSigned(Bureaucrat const &slave)
{
	try
	{
		if (slave.getGrade() > this->getRequiredSignGrade())
			throw Exception("Form::GradeTooLowException");
		else
			this->setSignedTrue();
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	Form::setSignedTrue(void)
{
	this->isSigned = true;
}

bool	Form::execute(Bureaucrat const &executor) const
{
	if (this->checkPrerequisites(executor, "Form"))
		return (true);
	else
		return (false);
}

bool	Form::checkPrerequisites(Bureaucrat const &executor, std::string formType) const
{
	try
	{
		if (!this->getIsSigned())
			throw Exception(formType + "::FormNotSignedException");
		else
		{
			try
			{
				if (executor.getGrade() > this->getRequiredExecGrade())
					throw Exception(formType + "::GradeTooLowException");
				else
					return (true);
			}
			catch (std::exception & e)
			{
				std::cerr << e.what() << std::endl;
				return (false);
			}
		}
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return (false);
	}
	return (false);
}
