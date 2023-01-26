/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_access.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:19:46 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 11:49:00 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_stack_element_access(void)
{
	ft::stack<std::string>	stk;
	std::string				str = "Bonjour";
	std::string				str2 = "KARTOFFELSALAT";

	for (size_t i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			stk.push(str);
		else
			stk.push(str2);
	}
	print_ft_stack(stk);
	while (stk.empty() == false)
	{
		std::cout << stk.top() << std::endl;
		stk.pop();
	}
}

void	test_std_stack_element_access(void)
{
	std::stack<std::string>	stk;
	std::string				str = "Bonjour";
	std::string				str2 = "KARTOFFELSALAT";

	for (size_t i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
			stk.push(str);
		else
			stk.push(str2);
	}
	print_std_stack(stk);
	while (stk.empty() == false)
	{
		std::cout << stk.top() << std::endl;
		stk.pop();
	}
}