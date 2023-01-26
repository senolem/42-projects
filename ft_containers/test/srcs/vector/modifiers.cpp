/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:03:02 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 10:03:50 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_vector_modifiers(void)
{
	std::list<int>	lst;
	ft::vector<int>	vect;

	for (size_t i = 0; i < 100; i++)
		lst.push_front(i);
	vect.insert(vect.begin(), 0);
	print_ft_vector(vect);
	vect.insert(vect.begin(), 100, 0);
	print_ft_vector(vect);
	vect.insert(vect.begin(), lst.begin(), lst.end());
	print_ft_vector(vect);
	vect.erase(vect.begin());
	print_ft_vector(vect);
	vect.erase(vect.begin());
	print_ft_vector(vect);
	vect.resize(50);
	print_ft_vector(vect);
	vect.resize(25);
	print_ft_vector(vect);
	vect.erase(vect.begin() + 1, vect.begin() + 2);
	print_ft_vector(vect);
	vect.pop_back();
	vect.pop_back();
	vect.pop_back();
	print_ft_vector(vect);
	ft::vector<int>	vect2(vect);
	vect.swap(vect2);
	print_ft_vector(vect);
	print_ft_vector(vect2);
}

void	test_std_vector_modifiers(void)
{
	std::list<int>	lst;
	std::vector<int>	vect;

	for (size_t i = 0; i < 100; i++)
		lst.push_front(i);
	vect.insert(vect.begin(), 0);
	print_std_vector(vect);
	vect.insert(vect.begin(), 100, 0);
	print_std_vector(vect);
	vect.insert(vect.begin(), lst.begin(), lst.end());
	print_std_vector(vect);
	vect.erase(vect.begin());
	print_std_vector(vect);
	vect.erase(vect.begin());
	print_std_vector(vect);
	vect.resize(50);
	print_std_vector(vect);
	vect.resize(25);
	print_std_vector(vect);
	vect.erase(vect.begin() + 1, vect.begin() + 2);
	print_std_vector(vect);
	vect.pop_back();
	vect.pop_back();
	vect.pop_back();
	print_std_vector(vect);
	std::vector<int>	vect2(vect);
	vect.swap(vect2);
	print_std_vector(vect);
	print_std_vector(vect2);
}
