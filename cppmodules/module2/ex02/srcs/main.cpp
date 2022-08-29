/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:19:30 by albaur            #+#    #+#             */
/*   Updated: 2022/08/29 16:03:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main(void)
{
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;

	std::cout << std::endl << "additionnal tests :" << std::endl << std::endl;
	std::cout << "expected : min between " << a << " and " << b << std::endl;
	std::cout << "result : " << Fixed::min(a, b) << std::endl << std::endl;

	a = Fixed(2) * 10 + Fixed(5.5f);
	std::cout << "a is now " << a << std::endl << std::endl;

	std::cout << "expected : min between " << a << " and " << b << std::endl;
	std::cout << "result : " << Fixed::min(a, b) << std::endl << std::endl;

	std::cout << "expected : max between " << a << " and " << b << std::endl;
	std::cout << "result : " << Fixed::max(a, b) << std::endl << std::endl;

	a = Fixed(5984563) / Fixed(3.14f) * Fixed(3.14f);
	std::cout << "a is now " << a << std::endl << std::endl;

	std::cout << "expected : min between " << a << " and " << b << std::endl;
	std::cout << "result : " << Fixed::min(a, b) << std::endl << std::endl;

	std::cout << "expected : max between " << a << " and " << b << std::endl;
	std::cout << "result : " << Fixed::max(a, b) << std::endl << std::endl;

	a = (Fixed(12345.6f) - Fixed(12345.6f)) * Fixed(10) / Fixed(2);
	std::cout << "a is now " << a << std::endl << std::endl;
	if (a == 0)
		std::cout << "a equal to 0" << std::endl;
	if (a != 1)
		std::cout << "a is not equal to 1" << std::endl;
	if (a < 1)
		std::cout << "a is lesser than 1" << std::endl;
	if (a > -1)
		std::cout << "a is greater than -1" << std::endl;
	if (a < 100)
		std::cout << "a is lesser or equal than 100" << std::endl;
	if (a > -100)
		std::cout << "a is greater or equal than -100" << std::endl << std::endl;

	a = Fixed(100.5f);
	std::cout << "a is now " << a << std::endl << std::endl;
	if (a == 0)
		std::cout << "a equal to 0" << std::endl;
	if (a != 1)
		std::cout << "a is not equal to 1" << std::endl;
	if (a < 1)
		std::cout << "a is lesser than 1" << std::endl;
	if (a > -1)
		std::cout << "a is greater than -1" << std::endl;
	if (a < 100)
		std::cout << "a is lesser or equal than 100" << std::endl;
	if (a > -100)
		std::cout << "a is greater or equal than -100" << std::endl;
	return (0);
}