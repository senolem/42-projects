/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:57:46 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 13:43:09 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_vector_comparison(void)
{
	ft::vector<int>	vect(10);
	ft::vector<int>	vect2(100);

	for (size_t i = 0; i < 50; i++)
		vect.push_back(i);
	for (size_t i = 0; i < 100; i++)
		vect2.push_back(i * 10);
	print_ft_vector(vect);
	print_ft_vector(vect2);
	if (vect.begin() == vect.begin())
		std::cout << "equal" << std::endl;
	if (vect.begin() != vect.begin() + 1)
		std::cout << "not equal" << std::endl;
	if (vect.begin() < vect.begin() + 2)
		std::cout << "lower than" << std::endl;
	if (vect.begin() <= vect.begin())
		std::cout << "lower or equal than" << std::endl;
	if (vect.begin() + 2 > vect.begin())
		std::cout << "greater than" << std::endl;
	if (vect.begin() + 2 >= vect.begin())
		std::cout << "greater or equal than" << std::endl;
	if (vect.begin() == vect.begin() + 1)
		std::cout << "equal" << std::endl;
	if (vect.begin() != vect.begin())
		std::cout << "not equal" << std::endl;
	if (vect.begin() < vect.begin())
		std::cout << "lower than" << std::endl;
	if (vect.begin() <= vect.begin())
		std::cout << "lower or equal than" << std::endl;
	if (vect.begin() > vect.begin())
		std::cout << "greater than" << std::endl;
	if (vect.begin() + 1 >= vect.begin())
		std::cout << "greater or equal than" << std::endl;
	if (vect.at(0) == vect2.at(0))
		std::cout << "equal" << std::endl;
	if (vect == vect2)
		std::cout << "equal" << std::endl;
	if (vect != vect2)
		std::cout << "not equal" << std::endl;
	if (vect < vect2)
		std::cout << "lower than" << std::endl;
	if (vect <= vect2)
		std::cout << "lower or equal than" << std::endl;
	if (vect > vect2)
		std::cout << "greater than" << std::endl;
	if (vect >= vect2)
		std::cout << "greater or equal than" << std::endl;
}

void	test_std_vector_comparison(void)
{
	std::vector<int>	vect(10);
	std::vector<int>	vect2(100);

	for (size_t i = 0; i < 50; i++)
		vect.push_back(i);
	for (size_t i = 0; i < 100; i++)
		vect2.push_back(i * 10);
	print_std_vector(vect);
	print_std_vector(vect2);
	if (vect.begin() == vect.begin())
		std::cout << "equal" << std::endl;
	if (vect.begin() != vect.begin() + 1)
		std::cout << "not equal" << std::endl;
	if (vect.begin() < vect.begin() + 2)
		std::cout << "lower than" << std::endl;
	if (vect.begin() <= vect.begin())
		std::cout << "lower or equal than" << std::endl;
	if (vect.begin() + 2 > vect.begin())
		std::cout << "greater than" << std::endl;
	if (vect.begin() + 2 >= vect.begin())
		std::cout << "greater or equal than" << std::endl;
	if (vect.begin() == vect.begin() + 1)
		std::cout << "equal" << std::endl;
	if (vect.begin() != vect.begin())
		std::cout << "not equal" << std::endl;
	if (vect.begin() < vect.begin())
		std::cout << "lower than" << std::endl;
	if (vect.begin() <= vect.begin())
		std::cout << "lower or equal than" << std::endl;
	if (vect.begin() > vect.begin())
		std::cout << "greater than" << std::endl;
	if (vect.begin() + 1 >= vect.begin())
		std::cout << "greater or equal than" << std::endl;
	if (vect.at(0) == vect2.at(0))
		std::cout << "equal" << std::endl;
	if (vect == vect2)
		std::cout << "equal" << std::endl;
	if (vect != vect2)
		std::cout << "not equal" << std::endl;
	if (vect < vect2)
		std::cout << "lower than" << std::endl;
	if (vect <= vect2)
		std::cout << "lower or equal than" << std::endl;
	if (vect > vect2)
		std::cout << "greater than" << std::endl;
	if (vect >= vect2)
		std::cout << "greater or equal than" << std::endl;
}