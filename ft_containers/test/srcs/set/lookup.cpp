/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:50:22 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 17:59:43 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_set_lookup(void)
{
	ft::set<char>	st;
	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
			std::cout << *(st.insert('a')).first << std::endl;
		else
			std::cout << (st.insert('b')).second << std::endl;
	}
	std::cout << st.count('a') << std::endl;
	std::cout << *(st.find('a')) << std::endl;
	std::cout << st.count('b') << std::endl;
	std::cout << *(st.find('a')) << std::endl;
	std::cout << st.count('b') << std::endl;
	std::cout << *(st.insert(st.begin(), 'c')) << std::endl;
	std::cout << *(st.find('c')) << std::endl;
	std::cout << st.count('c') << std::endl;
	ft::set<char>::const_iterator iter = st.find('c');
	std::cout << *(iter) << std::endl;
	ft::set<char>::iterator iter2;
	ft::set<char>::iterator iter3;
	ft::set<char>::const_iterator iter4;
	ft::set<char>::const_iterator iter5;
	ft::pair<ft::set<char>::iterator, ft::set<char>::iterator>	pair;
	ft::pair<ft::set<char>::const_iterator, ft::set<char>::const_iterator>	pair2;
	pair = st.equal_range('c');
	pair2 = st.equal_range('c');
	iter2 = pair.first;
	iter3 = pair.second;
	iter4 = pair2.first;
	iter5 = pair2.second;
	for (; iter2 != iter3; iter2++)
		std::cout << *(iter2) << std::endl;
	for (; iter4 != iter5; iter4++)
		std::cout << *(iter4) << std::endl;
	pair = st.equal_range('a');
	pair2 = st.equal_range('a');
	iter2 = pair.first;
	iter3 = pair.second;
	iter4 = pair2.first;
	iter5 = pair2.second;
	for (; iter2 != iter3; iter2++)
		std::cout << *(iter2) << std::endl;
	for (; iter4 != iter5; iter4++)
		std::cout << *(iter4) << std::endl;
	iter2 = st.lower_bound('c');
	iter4 = st.lower_bound('c');
	std::cout << *(iter2) << std::endl;
	std::cout << *(iter4) << std::endl;
	iter2 = st.upper_bound('b');
	iter4 = st.upper_bound('b');
	std::cout << *(iter2) << std::endl;
	std::cout << *(iter4) << std::endl;
	iter2 = st.begin();
	iter3 = st.end();
	iter4 = st.begin();
	iter5 = st.end();
	for (; iter2 != iter3; iter2++)
	{
		for (; iter4 != iter5; iter4++)
		{
			if (st.value_comp()(*iter2, *iter4))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (st.key_comp()(*iter2, *iter4))
				std::cout << "key equal" << std::endl;
			else
				std::cout << "key not equal" << std::endl;
		}
	}
}

void	test_std_set_lookup(void)
{
	std::set<char>	st;
	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
			std::cout << *(st.insert('a')).first << std::endl;
		else
			std::cout << (st.insert('b')).second << std::endl;
	}
	std::cout << st.count('a') << std::endl;
	std::cout << *(st.find('a')) << std::endl;
	std::cout << st.count('b') << std::endl;
	std::cout << *(st.find('a')) << std::endl;
	std::cout << st.count('b') << std::endl;
	std::cout << *(st.insert(st.begin(), 'c')) << std::endl;
	std::cout << *(st.find('c')) << std::endl;
	std::cout << st.count('c') << std::endl;
	std::set<char>::const_iterator iter = st.find('c');
	std::cout << *(iter) << std::endl;
	std::set<char>::iterator iter2;
	std::set<char>::iterator iter3;
	std::set<char>::const_iterator iter4;
	std::set<char>::const_iterator iter5;
	std::pair<std::set<char>::iterator, std::set<char>::iterator>	pair;
	std::pair<std::set<char>::const_iterator, std::set<char>::const_iterator>	pair2;
	pair = st.equal_range('c');
	pair2 = st.equal_range('c');
	iter2 = pair.first;
	iter3 = pair.second;
	iter4 = pair2.first;
	iter5 = pair2.second;
	for (; iter2 != iter3; iter2++)
		std::cout << *(iter2) << std::endl;
	for (; iter4 != iter5; iter4++)
		std::cout << *(iter4) << std::endl;
	pair = st.equal_range('a');
	pair2 = st.equal_range('a');
	iter2 = pair.first;
	iter3 = pair.second;
	iter4 = pair2.first;
	iter5 = pair2.second;
	for (; iter2 != iter3; iter2++)
		std::cout << *(iter2) << std::endl;
	for (; iter4 != iter5; iter4++)
		std::cout << *(iter4) << std::endl;
	iter2 = st.lower_bound('c');
	iter4 = st.lower_bound('c');
	std::cout << *(iter2) << std::endl;
	std::cout << *(iter4) << std::endl;
	iter2 = st.upper_bound('b');
	iter4 = st.upper_bound('b');
	std::cout << *(iter2) << std::endl;
	std::cout << *(iter4) << std::endl;
	iter2 = st.begin();
	iter3 = st.end();
	iter4 = st.begin();
	iter5 = st.end();
	for (; iter2 != iter3; iter2++)
	{
		for (; iter4 != iter5; iter4++)
		{
			if (st.value_comp()(*iter2, *iter4))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (st.key_comp()(*iter2, *iter4))
				std::cout << "key equal" << std::endl;
			else
				std::cout << "key not equal" << std::endl;
		}
	}
}
