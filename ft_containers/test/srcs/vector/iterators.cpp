/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:17:20 by albaur            #+#    #+#             */
/*   Updated: 2023/01/30 16:00:31 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "test.hpp"

void	test_ft_vector_iterators(void)
{
	ft::vector<char>							vect;
	ft::vector<char>::const_iterator			iter1;
	ft::vector<char>::const_iterator			iter2;
	ft::vector<char>::const_reverse_iterator	iter3;
	ft::vector<char>::const_reverse_iterator	iter4;
	
	for (size_t i = 0; i < 26; i++)
		vect.push_back('A' + i);
	print_ft_vector(vect);
	std::cout << *vect.begin() << std::endl;
	std::cout << *(--vect.end()) << std::endl;
	std::cout << *vect.rbegin() << std::endl;
	std::cout << *(--vect.rend()) << std::endl;
	iter1 = vect.begin();
	iter2 = vect.end();
	iter3 = vect.rbegin();
	iter4 = vect.rend();
	while (iter1 != iter2)
		std::cout << *iter1++ << std::endl;
	while (iter3 != iter4)
		std::cout << *iter3++ << std::endl;
}

void	test_std_vector_iterators(void)
{
	std::vector<char>							vect;
	std::vector<char>::const_iterator			iter1;
	std::vector<char>::const_iterator			iter2;
	std::vector<char>::const_reverse_iterator	iter3;
	std::vector<char>::const_reverse_iterator	iter4;

	for (size_t i = 0; i < 26; i++)
		vect.push_back('A' + i);
	print_std_vector(vect);
	std::cout << *vect.begin() << std::endl;
	std::cout << *(--vect.end()) << std::endl;
	std::cout << *vect.rbegin() << std::endl;
	std::cout << *(--vect.rend()) << std::endl;
	iter1 = vect.begin();
	iter2 = vect.end();
	iter3 = vect.rbegin();
	iter4 = vect.rend();
	while (iter1 != iter2)
		std::cout << *iter1++ << std::endl;
	while (iter3 != iter4)
		std::cout << *iter3++ << std::endl;
}