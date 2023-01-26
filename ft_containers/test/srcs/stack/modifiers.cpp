/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:25:42 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 13:28:56 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_stack_modifiers(void)
{
	ft::stack<int>	stk;

	stk.push(10);
	std::cout << stk.top() << std::endl;
	stk.push(5);
	std::cout << stk.top() << std::endl;
	stk.push(0);
	std::cout << stk.top() << std::endl;
	stk.pop();
	std::cout << stk.top() << std::endl;
	stk.pop();
	std::cout << stk.top() << std::endl;
	stk.push(5);
	std::cout << stk.top() << std::endl;
	stk.push(5);
	std::cout << stk.top() << std::endl;
}

void	test_std_stack_modifiers(void)
{
	std::stack<int>	stk;

	stk.push(10);
	std::cout << stk.top() << std::endl;
	stk.push(5);
	std::cout << stk.top() << std::endl;
	stk.push(0);
	std::cout << stk.top() << std::endl;
	stk.pop();
	std::cout << stk.top() << std::endl;
	stk.pop();
	std::cout << stk.top() << std::endl;
	stk.push(5);
	std::cout << stk.top() << std::endl;
	stk.push(5);
	std::cout << stk.top() << std::endl;
}
