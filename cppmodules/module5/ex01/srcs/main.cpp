/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:02:34 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 19:24:30 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main(void)
{
	Bureaucrat	slave1("Bob", 150);
	Bureaucrat	slave2("Billy", 50);
	Bureaucrat	slave3("Billy-bob", 25);
	Bureaucrat	slave4("Bob-billy", 1);
	Form		form1;
	Form		form2("FormTest1", 50, 150);
	Form		form3("FormTest2", 24, 150);
	Form		form4("FormTest3", 1, 150);
	Form		notworkingform1("A boring form", 151, 1);
	Form		notworkingform2("A very boring form", 0, 150);

	slave1.signForm(form1);
	slave1.signForm(form1);
	slave1.signForm(form2);
	slave1.signForm(form3);
	slave1.signForm(form4);

	slave2.signForm(form1);
	slave2.signForm(form2);
	slave2.signForm(form3);
	slave2.signForm(form4);

	slave3.signForm(form1);
	slave3.signForm(form2);
	slave3.signForm(form3);
	slave3.signForm(form4);

	slave4.signForm(form1);
	slave4.signForm(form2);
	slave4.signForm(form3);
	slave4.signForm(form4);
}
