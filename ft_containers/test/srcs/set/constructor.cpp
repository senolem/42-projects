/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:49:55 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 14:32:53 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_set_constructor(void)
{
	ft::set<int>	st;
	std::list<int>	lst;

	for (size_t i = 0; i < 100; i++)
		lst.push_back(i * 2);
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert(10);
	st.insert(5);
	st.insert(0);
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	ft::set<int>	st2(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(123);
	st2.insert(456);
	st2.insert(789);
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	ft::set<int>	st3 = st2;
	std::cout << st3.empty() << std::endl;
	std::cout << st3.size() << std::endl;
	std::cout << st3.max_size() << std::endl;
	ft::set<int>	st4(lst.begin(), lst.end());
	std::cout << st4.empty() << std::endl;
	std::cout << st4.size() << std::endl;
	std::cout << st4.max_size() << std::endl;
}

void	test_std_set_constructor(void)
{
	ft::set<int>	st;
	std::list<int>	lst;

	for (size_t i = 0; i < 100; i++)
		lst.push_back(i * 2);
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert(10);
	st.insert(5);
	st.insert(0);
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	ft::set<int>	st2(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(123);
	st2.insert(456);
	st2.insert(789);
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	ft::set<int>	st3 = st2;
	std::cout << st3.empty() << std::endl;
	std::cout << st3.size() << std::endl;
	std::cout << st3.max_size() << std::endl;
	ft::set<int>	st4(lst.begin(), lst.end());
	std::cout << st4.empty() << std::endl;
	std::cout << st4.size() << std::endl;
	std::cout << st4.max_size() << std::endl;
}
