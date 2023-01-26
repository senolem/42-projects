/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:06:15 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 11:18:53 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_stack_constructor(void)
{
	ft::stack<int>	stk;

	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
	for (size_t i = 0; i < 500; i++)
		stk.push(i);
	print_ft_stack(stk);
	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
	ft::stack<int>	stk2(stk);
	std::cout << stk2.empty() << std::endl;
	std::cout << stk2.size() << std::endl;
	for (size_t i = 0; i < 250; i++)
		stk2.pop();
	print_ft_stack(stk2);
	std::cout << stk2.empty() << std::endl;
	std::cout << stk2.size() << std::endl;
	ft::stack<int>	stk3 = stk2;
	for (size_t i = 0; i < 10; i++)
		stk3.push(i * 8);
	print_ft_stack(stk3);
	std::cout << stk3.empty() << std::endl;
	std::cout << stk3.size() << std::endl;
	std::list<std::string>	lst;
	ft::stack<std::string, std::list<std::string> >	stk4(lst);
	std::cout << stk4.empty() << std::endl;
	std::cout << stk4.size() << std::endl;
	print_ft_stack(stk4);
	lst.push_back("Bonjour");
	lst.push_back("ceci");
	lst.push_back("est");
	lst.push_back("un");
	lst.push_back("test");
	stk4.push(lst.front());
	stk4.push(lst.back());
	print_ft_stack(stk4);
	std::cout << stk3.empty() << std::endl;
	std::cout << stk3.size() << std::endl;
}

void	test_std_stack_constructor(void)
{
	std::stack<int>	stk;

	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
	for (size_t i = 0; i < 500; i++)
		stk.push(i);
	print_std_stack(stk);
	std::cout << stk.empty() << std::endl;
	std::cout << stk.size() << std::endl;
	std::stack<int>	stk2(stk);
	std::cout << stk2.empty() << std::endl;
	std::cout << stk2.size() << std::endl;
	for (size_t i = 0; i < 250; i++)
		stk2.pop();
	print_std_stack(stk2);
	std::cout << stk2.empty() << std::endl;
	std::cout << stk2.size() << std::endl;
	std::stack<int>	stk3 = stk2;
	for (size_t i = 0; i < 10; i++)
		stk3.push(i * 8);
	print_std_stack(stk3);
	std::cout << stk3.empty() << std::endl;
	std::cout << stk3.size() << std::endl;
	std::list<std::string>	lst;
	std::stack<std::string, std::list<std::string> >	stk4(lst);
	std::cout << stk4.empty() << std::endl;
	std::cout << stk4.size() << std::endl;
	print_std_stack(stk4);
	lst.push_back("Bonjour");
	lst.push_back("ceci");
	lst.push_back("est");
	lst.push_back("un");
	lst.push_back("test");
	stk4.push(lst.front());
	stk4.push(lst.back());
	print_std_stack(stk4);
	std::cout << stk3.empty() << std::endl;
	std::cout << stk3.size() << std::endl;
}
