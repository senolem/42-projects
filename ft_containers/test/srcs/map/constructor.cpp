/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:51:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/27 19:21:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_map_constructor(void)
{
	ft::map<int, int>		st;

	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert(ft::pair<int, int>(10, 10));
	st.insert(ft::pair<int, int>(5, 5));
	st.insert(ft::pair<int, int>(0, 0));
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	ft::map<int, int>	st2(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(ft::pair<int, int>(123, 123));
	st2.insert(ft::pair<int, int>(456, 456));
	st2.insert(ft::pair<int, int>(789, 10));
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	ft::map<int, int>	st3 = st2;
	std::cout << st3.empty() << std::endl;
	std::cout << st3.size() << std::endl;
	std::cout << st3.max_size() << std::endl;
	ft::map<int, int>	st4(st3.begin(), st3.end());
	std::cout << st4.empty() << std::endl;
	std::cout << st4.size() << std::endl;
	std::cout << st4.max_size() << std::endl;
}

void	test_std_map_constructor(void)
{
	std::map<int, int>		st;

	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert(std::pair<int, int>(10, 10));
	st.insert(std::pair<int, int>(5, 5));
	st.insert(std::pair<int, int>(0, 0));
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::map<int, int>	st2(st);
	std::cout << st2.empty() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st2.max_size() << std::endl;
	st2.insert(std::pair<int, int>(123, 123));
	st2.insert(std::pair<int, int>(456, 456));
	st2.insert(std::pair<int, int>(789, 10));
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	std::map<int, int>	st3 = st2;
	std::cout << st3.empty() << std::endl;
	std::cout << st3.size() << std::endl;
	std::cout << st3.max_size() << std::endl;
	std::map<int, int>	st4(st3.begin(), st3.end());
	std::cout << st4.empty() << std::endl;
	std::cout << st4.size() << std::endl;
	std::cout << st4.max_size() << std::endl;
}
