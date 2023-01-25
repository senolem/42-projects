/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:12:23 by albaur            #+#    #+#             */
/*   Updated: 2023/01/25 22:42:46 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "test.hpp"

void	test_ft_vector_constructor(void)
{
	ft::vector<int>	vect;
	ft::vector<int>	vect2(10);
	print_ft_vector(vect);
	print_ft_vector(vect2);
	vect.push_back(1);
	print_ft_vector(vect);
	vect2.push_back(1);
	vect2.push_back(2);
	print_ft_vector(vect2);
	ft::vector<int>	vect3(vect2.begin(), vect2.end());
	print_ft_vector(vect3);
	for (size_t i = 0; i < 100; i++)
		vect3.push_back(100);
	print_ft_vector(vect3);
	ft::vector<int>	vect4(vect3);
	print_ft_vector(vect4);
	ft::vector<int>	vect5 = vect4;
	print_ft_vector(vect5);
	std::cout << vect.size() << std::endl;
	std::cout << vect2.size() << std::endl;
	std::cout << vect3.size() << std::endl;
	std::cout << vect4.size() << std::endl;
	std::cout << vect5.size() << std::endl;
}

void	test_std_vector_constructor(void)
{
	std::vector<int>	vect;
	std::vector<int>	vect2(10);
	print_std_vector(vect);
	print_std_vector(vect2);
	vect.push_back(1);
	print_std_vector(vect);
	vect2.push_back(1);
	vect2.push_back(2);
	print_std_vector(vect2);
	std::vector<int>	vect3(vect2.begin(), vect2.end());
	print_std_vector(vect3);
	for (size_t i = 0; i < 100; i++)
		vect3.push_back(100);
	print_std_vector(vect3);
	std::vector<int>	vect4(vect3);
	print_std_vector(vect4);
	std::vector<int>	vect5 = vect4;
	print_std_vector(vect5);
	std::cout << vect.size() << std::endl;
	std::cout << vect2.size() << std::endl;
	std::cout << vect3.size() << std::endl;
	std::cout << vect4.size() << std::endl;
	std::cout << vect5.size() << std::endl;
}