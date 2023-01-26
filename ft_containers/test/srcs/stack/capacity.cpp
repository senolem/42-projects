/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:55:05 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 11:59:45 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_stack_capacity(void)
{
	ft::stack<std::string>	stk;
	
	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
	for (size_t i = 0; i < 26; i++)
		stk.push("test");
	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
	stk.pop();
	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
}

void	test_std_stack_capacity(void)
{
	std::stack<std::string>	stk;
	
	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
	for (size_t i = 0; i < 26; i++)
		stk.push("test");
	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
	stk.pop();
	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
}
