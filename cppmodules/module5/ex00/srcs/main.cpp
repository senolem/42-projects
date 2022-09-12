/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:02:34 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 17:51:05 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	Bureaucrat	slave1;
	Bureaucrat	slave2("Billy", 150);
	Bureaucrat	slave3("Bob", 150);

	std::cout << slave1 << std::endl;
	std::cout << slave2 << std::endl;
	std::cout << slave3 << std::endl;

	slave1.decrementGrade();
	slave2.incrementGrade();
	slave3.incrementGrade();
	slave3.incrementGrade();

	std::cout << slave1 << std::endl;
	std::cout << slave2 << std::endl;
	std::cout << slave3 << std::endl;

	slave1.setGrade(1);
	slave2.setGrade(2);
	slave3.setGrade(1);

	std::cout << slave1 << std::endl;
	std::cout << slave2 << std::endl;
	std::cout << slave3 << std::endl;

	slave1.decrementGrade();
	slave2.incrementGrade();
	slave3.incrementGrade();
	slave3.incrementGrade();

	std::cout << slave1 << std::endl;
	std::cout << slave2 << std::endl;
	std::cout << slave3 << std::endl;

	std::cout << "My name is " << slave1.getName() << ", my grade is " << slave1.getGrade() << std::endl;
}
