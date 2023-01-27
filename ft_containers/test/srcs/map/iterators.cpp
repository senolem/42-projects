/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:52:07 by albaur            #+#    #+#             */
/*   Updated: 2023/01/27 20:04:13 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_map_iterators(void)
{
	ft::map<std::string, char>							st;
	ft::map<std::string, char>::const_iterator			iter1;
	ft::map<std::string, char>::const_iterator			iter2;
	ft::map<std::string, char>::const_reverse_iterator	iter3;
	ft::map<std::string, char>::const_reverse_iterator	iter4;

	st.insert(ft::pair<std::string, char>("Les", 'a'));
	st.insert(ft::pair<std::string, char>("épinards", 'b'));
	st.insert(ft::pair<std::string, char>("moi", 'c'));
	st.insert(ft::pair<std::string, char>("j'adore", 'd'));
	st.insert(ft::pair<std::string, char>("ça", 'e'));
	st.insert(ft::pair<std::string, char>("!", 'f'));
	std::cout << st.begin()->first << " " << st.begin()->second << std::endl;
	std::cout << (--(st.end()))->first << " " << (--(st.end()))->second << std::endl;
	std::cout << st.rbegin()->first << " " << st.rbegin()->second << std::endl;
	std::cout << (--(st.rend()))->first << " " << (--(st.rend()))->second << std::endl;
	iter1 = st.begin();
	iter2 = st.end();
	iter3 = st.rbegin();
	iter4 = st.rend();
	while (iter1 != iter2)
		std::cout << (iter1)->first << " " << (iter1++)->second << std::endl;
	while (iter3 != iter4)
		std::cout << (iter3)->first << " " << (iter3++)->second << std::endl;
}

void	test_std_map_iterators(void)
{
	std::map<std::string, char>							st;
	std::map<std::string, char>::const_iterator			iter1;
	std::map<std::string, char>::const_iterator			iter2;
	std::map<std::string, char>::const_reverse_iterator	iter3;
	std::map<std::string, char>::const_reverse_iterator	iter4;

	st.insert(std::pair<std::string, char>("Les", 'a'));
	st.insert(std::pair<std::string, char>("épinards", 'b'));
	st.insert(std::pair<std::string, char>("moi", 'c'));
	st.insert(std::pair<std::string, char>("j'adore", 'd'));
	st.insert(std::pair<std::string, char>("ça", 'e'));
	st.insert(std::pair<std::string, char>("!", 'f'));
	std::cout << st.begin()->first << " " << st.begin()->second << std::endl;
	std::cout << (--(st.end()))->first << " " << (--(st.end()))->second << std::endl;
	std::cout << st.rbegin()->first << " " << st.rbegin()->second << std::endl;
	std::cout << (--(st.rend()))->first << " " << (--(st.rend()))->second << std::endl;
	iter1 = st.begin();
	iter2 = st.end();
	iter3 = st.rbegin();
	iter4 = st.rend();
	while (iter1 != iter2)
		std::cout << (iter1)->first << " " << (iter1++)->second << std::endl;
	while (iter3 != iter4)
		std::cout << (iter3)->first << " " << (iter3++)->second << std::endl;
}
