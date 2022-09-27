/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:53:10 by albaur            #+#    #+#             */
/*   Updated: 2022/09/27 16:57:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int	main(void)
{
	Array<int> test;
	Array<int> test2(10);
	Array<int> test3(test2);
	Array<int> test4 = test2;

	std::cout << "size : " << test.size() << std::endl;
	std::cout << "size : " << test2.size() << std::endl;
	std::cout << "size : " << test3.size() << std::endl;
	std::cout << "size : " << test4.size() << std::endl;

	std::cout << test;
	std::cout << test2;
	std::cout << test3;
	std::cout << test4;

	std::cout << test[100] << std::endl;
	std::cout << test2[11] << std::endl;
	std::cout << test3[50] << std::endl;
	std::cout << test4[1000] << std::endl;
}