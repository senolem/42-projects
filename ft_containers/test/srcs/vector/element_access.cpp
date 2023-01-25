/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_access.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:48:57 by albaur            #+#    #+#             */
/*   Updated: 2023/01/25 23:16:31 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_vector_element_access(void)
{
	ft::vector<std::string>	vect;
	vect.push_back("Bonjour");
	vect.push_back("ceci");
	vect.push_back("est");
	vect.push_back("un");
	vect.push_back("test");
	std::cout << vect.at(0) << std::endl;
	std::cout << vect.at(1) << std::endl;
	std::cout << vect.at(2) << std::endl;
	std::cout << vect.at(3) << std::endl;
	std::cout << vect.at(4) << std::endl;
	std::cout << vect[0] << std::endl;
	std::cout << vect[1] << std::endl;
	std::cout << vect[2] << std::endl;
	std::cout << vect[3] << std::endl;
	std::cout << vect[4] << std::endl;
	std::cout << vect.front() << std::endl;
	std::cout << vect.back() << std::endl;
	std::cout << *vect.data() << std::endl;
}

void	test_std_vector_element_access(void)
{
	std::vector<std::string>	vect;
	vect.push_back("Bonjour");
	vect.push_back("ceci");
	vect.push_back("est");
	vect.push_back("un");
	vect.push_back("test");
	std::cout << vect.at(0) << std::endl;
	std::cout << vect.at(1) << std::endl;
	std::cout << vect.at(2) << std::endl;
	std::cout << vect.at(3) << std::endl;
	std::cout << vect.at(4) << std::endl;
	std::cout << vect[0] << std::endl;
	std::cout << vect[1] << std::endl;
	std::cout << vect[2] << std::endl;
	std::cout << vect[3] << std::endl;
	std::cout << vect[4] << std::endl;
	std::cout << vect.front() << std::endl;
	std::cout << vect.back() << std::endl;
	std::cout << *vect.data() << std::endl;
}