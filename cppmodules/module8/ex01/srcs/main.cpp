/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:25:31 by albaur            #+#    #+#             */
/*   Updated: 2022/10/03 16:58:53 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int	main(void)
{
	Span sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	//ADDITIONNAL TESTS
	std::cout << std::endl << "ADDITIONNAL TESTS" << std::endl;
	
	Span	test(10);
	for (size_t i = 0; i < 10; ++i)
		test.addNumber(i);
	test.displayArray();
	test.addNumber(99);
	std::cout << std::endl;

	Span test2(1);
	for (size_t i = 0; i < 10; ++i)
		test2.addNumber(i * 10);
	test2.displayArray();
	std::cout << std::endl;

	Span test3(100);
	test3.addNumberRandom();
	test3.displayArray();
	test.addNumber(555);
	std::cout << std::endl;

	Span test4 = test3;
	test4.displayArray();
	std::cout << std::endl;

	Span test5(test4);
	test5.displayArray();
}