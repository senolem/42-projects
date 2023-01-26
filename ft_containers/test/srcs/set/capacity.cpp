/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:48:45 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 16:02:26 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_set_capacity(void)
{
	ft::set<std::string>	st;

	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	for (size_t i = 0; i < 26; i++)
		st.insert("test");
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert("test");
	st.insert("purée de pomme de terres");
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
}

void	test_std_set_capacity(void)
{
	std::set<std::string>	st;

	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	for (size_t i = 0; i < 26; i++)
		st.insert("test");
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.clear();
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
	st.insert("test");
	st.insert("purée de pomme de terres");
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st.max_size() << std::endl;
}
