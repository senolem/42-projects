/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:50:06 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 14:44:48 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_set_iterators(void)
{
	ft::set<std::string>							st;
	ft::set<std::string>::const_iterator			iter1;
	ft::set<std::string>::const_iterator			iter2;
	ft::set<std::string>::const_reverse_iterator	iter3;
	ft::set<std::string>::const_reverse_iterator	iter4;

	st.insert("Les");
	st.insert("épinards");
	st.insert("moi");
	st.insert("j'adore");
	st.insert("ça");
	st.insert("!");
	std::cout << *st.begin() << std::endl;
	std::cout << *(--st.end()) << std::endl;
	std::cout << *st.rbegin() << std::endl;
	std::cout << *(--st.rend()) << std::endl;
	iter1 = st.begin();
	iter2 = st.end();
	iter3 = st.rbegin();
	iter4 = st.rend();
	while (iter1 != iter2)
		std::cout << *iter1++ << std::endl;
	while (iter3 != iter4)
		std::cout << *iter3++ << std::endl;
}

void	test_std_set_iterators(void)
{
	std::set<std::string>							st;
	std::set<std::string>::const_iterator			iter1;
	std::set<std::string>::const_iterator			iter2;
	std::set<std::string>::const_reverse_iterator	iter3;
	std::set<std::string>::const_reverse_iterator	iter4;

	st.insert("Les");
	st.insert("épinards");
	st.insert("moi");
	st.insert("j'adore");
	st.insert("ça");
	st.insert("!");
	std::cout << *st.begin() << std::endl;
	std::cout << *(--st.end()) << std::endl;
	std::cout << *st.rbegin() << std::endl;
	std::cout << *(--st.rend()) << std::endl;
	iter1 = st.begin();
	iter2 = st.end();
	iter3 = st.rbegin();
	iter4 = st.rend();
	while (iter1 != iter2)
		std::cout << *iter1++ << std::endl;
	while (iter3 != iter4)
		std::cout << *iter3++ << std::endl;
}
