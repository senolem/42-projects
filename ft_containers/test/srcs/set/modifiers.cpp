/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:50:40 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 17:19:35 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_set_modifiers(void)
{
	ft::set<char>	st;
	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
			std::cout << *(st.insert('a')).first;
		else
			std::cout << (st.insert('b')).second;
	}
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::cout << *(st.insert(st.begin(), 'c')) << std::endl;
	ft::set<char>::const_iterator iter = st.begin();
	std::cout << *(st.insert(++iter, 'd'));
	std::list<char>	lst;
	for (size_t i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			lst.push_back(i * 2);
		else
			lst.push_back(i * 4);
	}
	st.insert(++lst.begin(), lst.end());
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	ft::set<char>	st2 = st;
	st2.clear();
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(++(++(++(++(st.begin())))), --(st.end()));
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.erase(++(++(++(++(st2.begin())))));
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.erase('d');
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	std::cout << *(st2.begin()) << std::endl;
	std::cout << *(st2.rbegin()) << std::endl;
	st2.swap(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	std::cout << *(st2.begin()) << std::endl;
	std::cout << *(st2.rbegin()) << std::endl;
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::cout << *(st.begin()) << std::endl;
	std::cout << *(st.rbegin()) << std::endl;
}

void	test_std_set_modifiers(void)
{
	std::set<char>	st;
	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
			std::cout << *(st.insert('a')).first;
		else
			std::cout << (st.insert('b')).second;
	}
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::cout << *(st.insert(st.begin(), 'c')) << std::endl;
	std::set<char>::const_iterator iter = st.begin();
	std::cout << *(st.insert(++iter, 'd'));
	std::list<char>	lst;
	for (size_t i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			lst.push_back(i * 2);
		else
			lst.push_back(i * 4);
	}
	st.insert(++lst.begin(), lst.end());
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::set<char>	st2 = st;
	st2.clear();
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(++(++(++(++(st.begin())))), --(st.end()));
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.erase(++(++(++(++(st2.begin())))));
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.erase('d');
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	std::cout << *(st2.begin()) << std::endl;
	std::cout << *(st2.rbegin()) << std::endl;
	st2.swap(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	std::cout << *(st2.begin()) << std::endl;
	std::cout << *(st2.rbegin()) << std::endl;
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::cout << *(st.begin()) << std::endl;
	std::cout << *(st.rbegin()) << std::endl;
}
