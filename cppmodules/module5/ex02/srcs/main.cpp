/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:02:34 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 18:20:26 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main(void)
{
	Bureaucrat				bureaucrat1("Pierre", 150);
	Bureaucrat				bureaucrat2("Paul", 44);
	Bureaucrat				bureaucrat3("Jacques", 25);
	Bureaucrat				bureaucrat4("Robert", 1);
	ShrubberyCreationForm	form1("target1");
	RobotomyRequestForm		form2;
	PresidentialPardonForm	form3("target3");

	bureaucrat1.signForm(form1);
	bureaucrat2.signForm(form2);
	bureaucrat3.signForm(form3);
	bureaucrat4.signForm(form3);

	std::cout << form1 << std::endl;
	std::cout << form2 << std::endl;
	std::cout << form3 << std::endl;

	bureaucrat1.executeForm(form1);
	bureaucrat2.executeForm(form2);
	bureaucrat3.executeForm(form3);
	bureaucrat4.executeForm(form3);
}
