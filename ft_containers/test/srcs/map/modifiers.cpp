/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:52:41 by albaur            #+#    #+#             */
/*   Updated: 2023/01/27 23:21:40 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_map_modifiers(void)
{
	ft::map<char, char>		st;
	ft::pair<char, char>	pr;

	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
		{
			pr = *st.insert(st.begin(), ft::pair<char, char>('a', 'a'));
			std::cout << pr.first << " " << pr.second << std::endl;
		}
		else
		{
			pr = *st.insert(st.begin(), ft::pair<char, char>('b', 'b'));
			std::cout << pr.first << " " << pr.second << std::endl;
		}
	}
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	pr = *st.insert(st.begin(), ft::pair<char, char>('c', 'c'));
	std::cout << pr.first << " " << pr.second << std::endl;
	ft::map<char, char>::iterator iter = st.begin();
	pr = *st.insert(iter, ft::pair<char, char>('d', 'd'));
	std::cout << pr.first << " " << pr.second << std::endl;
	ft::map<char, char>	st2(st);
	st2.clear();
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(st.begin(), st.end());
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st2.erase('d');
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	std::cout << st2.begin()->first << " " << st2.begin()->second << std::endl;
	std::cout << st2.rbegin()->first << " " << st2.rbegin()->second << std::endl;
	st2.swap(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	std::cout << st2.begin()->first << " " << st2.begin()->second << std::endl;
	std::cout << st2.rbegin()->first << " " << st2.rbegin()->second << std::endl;
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::cout << st2.begin()->first << " " << st2.begin()->second << std::endl;
	std::cout << st2.rbegin()->first << " " << st2.rbegin()->second << std::endl;
}

void	test_std_map_modifiers(void)
{
	std::map<char, char>	st;
	std::pair<char, char>	pr;

	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
		{
			pr = *st.insert(st.begin(), std::pair<char, char>('a', 'a'));
			std::cout << pr.first << " " << pr.second << std::endl;
		}
		else
		{
			pr = *st.insert(st.begin(), std::pair<char, char>('b', 'b'));
			std::cout << pr.first << " " << pr.second << std::endl;
		}
	}
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	pr = *st.insert(st.begin(), std::pair<char, char>('c', 'c'));
	std::cout << pr.first << " " << pr.second << std::endl;
	std::map<char, char>::iterator iter = st.begin();
	pr = *st.insert(iter, std::pair<char, char>('d', 'd'));
	std::cout << pr.first << " " << pr.second << std::endl;
	std::map<char, char>	st2(st);
	st2.clear();
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(st.begin(), st.end());
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st2.erase('d');
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	std::cout << st2.begin()->first << " " << st2.begin()->second << std::endl;
	std::cout << st2.rbegin()->first << " " << st2.rbegin()->second << std::endl;
	st2.swap(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	std::cout << st2.begin()->first << " " << st2.begin()->second << std::endl;
	std::cout << st2.rbegin()->first << " " << st2.rbegin()->second << std::endl;
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::cout << st2.begin()->first << " " << st2.begin()->second << std::endl;
	std::cout << st2.rbegin()->first << " " << st2.rbegin()->second << std::endl;
}
