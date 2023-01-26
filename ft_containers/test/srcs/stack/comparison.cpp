/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:25:40 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 13:36:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_stack_comparison(void)
{
	ft::stack<int>	stk;

	stk.push(10);
	ft::stack<int>	stk2(stk);
	if (stk == stk2)
		std::cout << "equal" << std::endl;
	stk.push(10);
	if (stk == stk2)
		std::cout << "equal" << std::endl;
	if (stk != stk2)
		std::cout << "not equal" << std::endl;
	stk.pop();
	if (stk == stk2)
		std::cout << "equal" << std::endl;
	stk2.push(100);
	if (stk2 > stk)
		std::cout << "greater than" << std::endl;
	if (stk2 < stk)
		std::cout << "lower than" << std::endl;
	stk2.pop();
	if (stk2 >= stk)
		std::cout << "greater or equal than" << std::endl;
	if (stk2 <= stk)
		std::cout << "lower or equal than" << std::endl;
	stk.push(100);
	if (stk2 < stk)
		std::cout << "lower than" << std::endl;
	if (stk2 <= stk)
		std::cout << "lower or equal than" << std::endl;
}

void	test_std_stack_comparison(void)
{
	ft::stack<int>	stk;

	stk.push(10);
	ft::stack<int>	stk2(stk);
	if (stk == stk2)
		std::cout << "equal" << std::endl;
	stk.push(10);
	if (stk == stk2)
		std::cout << "equal" << std::endl;
	if (stk != stk2)
		std::cout << "not equal" << std::endl;
	stk.pop();
	if (stk == stk2)
		std::cout << "equal" << std::endl;
	stk2.push(100);
	if (stk2 > stk)
		std::cout << "greater than" << std::endl;
	if (stk2 < stk)
		std::cout << "lower than" << std::endl;
	stk2.pop();
	if (stk2 >= stk)
		std::cout << "greater or equal than" << std::endl;
	if (stk2 <= stk)
		std::cout << "lower or equal than" << std::endl;
	stk.push(100);
	if (stk2 < stk)
		std::cout << "lower than" << std::endl;
	if (stk2 <= stk)
		std::cout << "lower or equal than" << std::endl;
}
