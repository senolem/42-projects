/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:50:40 by albaur            #+#    #+#             */
/*   Updated: 2023/01/27 23:56:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_set_modifiers(void)
{
	ft::set<char>					st;
	ft::set<char>::const_iterator	iter;
	ft::set<char>::reverse_iterator	iter2;

	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
			std::cout << *(st.insert('a')).first << std::endl;
		else
			std::cout << *(st.insert('b')).first << std::endl;
	}
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert(st.begin(), 'c');
	std::cout << *st.begin() << std::endl;
	iter = st.begin();
	st.insert(iter, 'd');
	std::cout << *iter << std::endl;
	std::list<char>	lst;
	for (size_t i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			lst.push_back('a');
		else
			lst.push_back('b');
	}
	st.insert(lst.begin(), lst.end());
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	ft::set<char>	st2 = st;
	st2.clear();
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(st.begin(), st.end());
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.erase(st2.begin());
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.erase('d');
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	iter = st2.begin();
	iter2 = st2.rbegin();
	std::cout << *iter << std::endl;
	std::cout << *iter2 << std::endl;
	st2.swap(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	iter = st2.begin();
	iter2 = st2.rbegin();
	std::cout << *iter << std::endl;
	std::cout << *iter2 << std::endl;
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	iter = st.begin();
	iter2 = st.rbegin();
	std::cout << *iter << std::endl;
	std::cout << *iter2 << std::endl;
}

void	test_std_set_modifiers(void)
{
	std::set<char>					st;
	std::set<char>::const_iterator	iter;
	std::set<char>::reverse_iterator	iter2;

	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
			std::cout << *(st.insert('a')).first << std::endl;
		else
			std::cout << *(st.insert('b')).first << std::endl;
	}
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert(st.begin(), 'c');
	std::cout << *st.begin() << std::endl;
	iter = st.begin();
	st.insert(iter, 'd');
	std::cout << *iter << std::endl;
	std::list<char>	lst;
	for (size_t i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			lst.push_back('a');
		else
			lst.push_back('b');
	}
	st.insert(lst.begin(), lst.end());
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::set<char>	st2 = st;
	st2.clear();
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(st.begin(), st.end());
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.erase(st2.begin());
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.erase('d');
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	iter = st2.begin();
	iter2 = st2.rbegin();
	std::cout << *iter << std::endl;
	std::cout << *iter2 << std::endl;
	st2.swap(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	iter = st2.begin();
	iter2 = st2.rbegin();
	std::cout << *iter << std::endl;
	std::cout << *iter2 << std::endl;
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	iter = st.begin();
	iter2 = st.rbegin();
	std::cout << *iter << std::endl;
	std::cout << *iter2 << std::endl;
}
