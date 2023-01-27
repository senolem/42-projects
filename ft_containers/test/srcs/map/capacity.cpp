/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:48:45 by albaur            #+#    #+#             */
/*   Updated: 2023/01/27 19:07:50 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_map_capacity(void)
{
	ft::map<std::string, int>	st;

	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	for (size_t i = 0; i < 26; i++)
		st.insert(ft::pair<std::string, int>("test", i));
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert(ft::pair<std::string, int>("test", 84));
	st.insert(ft::pair<std::string, int>("purée de pommes de terre", 42));
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
}

void	test_std_map_capacity(void)
{
	std::map<std::string, int>	st;

	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	for (size_t i = 0; i < 26; i++)
		st.insert(std::pair<std::string, int>("test", i));
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert(std::pair<std::string, int>("test", 84));
	st.insert(std::pair<std::string, int>("purée de pommes de terre", 42));
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
}
