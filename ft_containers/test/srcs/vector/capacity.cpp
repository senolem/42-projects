/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:54:22 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 00:10:23 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_vector_capacity(void)
{
	std::vector<std::string>	vect;

	std::cout << vect.empty() << std::endl;
	std::cout << vect.size() << std::endl;
	std::cout << vect.max_size() << std::endl;
	std::cout << vect.capacity() << std::endl;
	for (size_t i = 0; i < 26; i++)
		vect.push_back("test");
	std::cout << vect.empty() << std::endl;
	std::cout << vect.size() << std::endl;
	std::cout << vect.max_size() << std::endl;
	std::cout << vect.capacity() << std::endl;
	vect.reserve(100);
	std::cout << vect.empty() << std::endl;
	std::cout << vect.size() << std::endl;
	std::cout << vect.max_size() << std::endl;
	std::cout << vect.capacity() << std::endl;
	vect.reserve(100);
	vect.clear();
	std::cout << vect.empty() << std::endl;
	std::cout << vect.size() << std::endl;
	std::cout << vect.max_size() << std::endl;
	std::cout << vect.capacity() << std::endl;
}

void	test_std_vector_capacity(void)
{
	std::vector<std::string>	vect;
	
	std::cout << vect.empty() << std::endl;
	std::cout << vect.size() << std::endl;
	std::cout << vect.max_size() << std::endl;
	std::cout << vect.capacity() << std::endl;
	for (size_t i = 0; i < 26; i++)
		vect.push_back("test");
	std::cout << vect.empty() << std::endl;
	std::cout << vect.size() << std::endl;
	std::cout << vect.max_size() << std::endl;
	std::cout << vect.capacity() << std::endl;
	vect.reserve(100);
	std::cout << vect.empty() << std::endl;
	std::cout << vect.size() << std::endl;
	std::cout << vect.max_size() << std::endl;
	std::cout << vect.capacity() << std::endl;
	vect.reserve(100);
	vect.clear();
	std::cout << vect.empty() << std::endl;
	std::cout << vect.size() << std::endl;
	std::cout << vect.max_size() << std::endl;
	std::cout << vect.capacity() << std::endl;
}
