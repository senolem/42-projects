/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:02:34 by albaur            #+#    #+#             */
/*   Updated: 2023/02/17 12:24:58 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int	main(void)
{
	Intern	someRandomIntern;
	Form	*scf = NULL;
	Form	*rrf = NULL;
	Form	*ppf = NULL;
	Form	*nope = NULL;

	scf = someRandomIntern.makeForm("shrubbery creation", "Bender");
	rrf = someRandomIntern.makeForm("robotomy request", "Binder");
	ppf = someRandomIntern.makeForm("presidential pardon", "Bunder");
	nope = someRandomIntern.makeForm("OOPS", "NOPE");

	std::cout << scf << std::endl;
	std::cout << rrf << std::endl;
	std::cout << ppf << std::endl;
	std::cout << nope << std::endl;
	std::cout << *scf << std::endl;
	std::cout << *rrf << std::endl;
	std::cout << *ppf << std::endl;
	delete scf;
	delete rrf;
	delete ppf;
	delete nope;
}
