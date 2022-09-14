/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:02:31 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 15:47:52 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) : name("Slave")
{
	this->grade = 150;
}

Bureaucrat::Bureaucrat(Bureaucrat const &src) : name(src.name)
{
	*this = src;
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << this->name << ", you're fired!" << std::endl;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &src)
{
	if (this != &src)
		this->grade = src.grade;
	return (*this);
}

Bureaucrat::Bureaucrat(std::string name, unsigned int grade) : name(name)
{
	try
	{
		if (grade > 150)
			throw Exception("Bureaucrat::GradeTooLowException");
		else if (grade < 1)
			throw Exception("Bureaucrat::GradeTooHighException");
		else
			this->grade = grade;
	}
	catch (std::exception & e)
	{
		this->grade = 150;
		std::cerr << e.what() << std::endl;
	}
}

std::string	Bureaucrat::getName(void) const
{
	return (this->name);
}

unsigned int	Bureaucrat::getGrade(void) const
{
	return (this->grade);
}

void	Bureaucrat::incrementGrade(void)
{
	try
	{
		if (this->grade == 1)
			throw Exception("Bureaucrat::GradeTooHighException");
		else
			this->grade -= 1;
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	Bureaucrat::decrementGrade(void)
{
	try
	{
		if (this->grade == 150)
			throw Exception("Bureaucrat::GradeTooLowException");
		else
			this->grade += 1;
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	Bureaucrat::setGrade(unsigned int grade)
{
	try
	{
		if (grade > 150)
			throw Exception("Bureaucrat::GradeTooLowException");
		else if (grade < 1)
			throw Exception("Bureaucrat::GradeTooHighException");
		else
			this->grade = grade;
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::ostream	&operator<<(std::ostream &stream, const Bureaucrat &slave)
{
	return (stream << slave.getName() << ", bureaucrat grade [" << slave.getGrade() << "]");
}

void	Bureaucrat::signForm(Form &boringform)
{
	if (boringform.getIsSigned())
		std::cout << this->name << " couldn't sign " << boringform.getName() << " because it is already signed." << std::endl;
	else
	{
		boringform.beSigned(*this);
		if (boringform.getIsSigned())
			std::cout << this->name << " signed " << boringform.getName() << std::endl;
		else
			std::cout << this->name << " couldn't sign " << boringform.getName() << " because the its grade is too low." << std::endl;
	}
}

void	Bureaucrat::executeForm(Form const &form)
{
	if (!form.getIsSigned())
	{
		std::cout << this->name << " couldn't execute " << form.getName() << " because the form is not signed." << std::endl;
		return ;
	}
	if (form.execute(*this))
		std::cout << this->name << " executed " << form.getName() << std::endl;
	else
		std::cout << this->name << " couldn't execute " << form.getName() << " because the its grade is too low." << std::endl;

}
