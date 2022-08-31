/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:19:30 by albaur            #+#    #+#             */
/*   Updated: 2022/08/31 15:11:46 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

int main (void)
{
	Point	a(1, 1);
	Point	b(2, 3);
	Point	c(3, 1);
	Point	d(2, 2);
	std::cout << "expected to be inside" << std::endl;
	std::cout << "Checking triangle: " << "A" << a << " " << "B" << b << " " << "C" << c << " " << "D" << d << std::endl;
    if (bsp(a, b, c, d) == true)
        std::cout << "Point is inside the triangle" << std::endl;
	else
        std::cout << "Point is outside the triangle" << std::endl;
	std::cout << std::endl;

	Point	e(1, 1);
	Point	f(2, 3);
	Point	g(3, 1);
	Point	h(2.5f, 2);
	std::cout << "expected to be outside (edge of BC segment)" << std::endl;
	std::cout << "Checking triangle: " << "E" << e << " " << "F" << f << " " << "G" << g << " " << "H" << h << std::endl;
	if (bsp(e, f, g, h) == true)
        std::cout << "Point is inside the triangle" << std::endl;
	else
        std::cout << "Point is outside the triangle" << std::endl;
	std::cout << std::endl;
	
	Point	i(1, 1);
	Point	j(2, 3);
	Point	k(3, 1);
	Point	l(3, 1);
	std::cout << "expected to be outside (on C summit)" << std::endl;
	std::cout << "Checking triangle: " << "I" << i << " " << "J" << j << " " << "K" << k << " " << "L" << l << std::endl;
	if (bsp(i, j, k, l) == true)
        std::cout << "Point is inside the triangle" << std::endl;
	else
        std::cout << "Point is outside the triangle" << std::endl;
	std::cout << std::endl;

	Point	m(1, 1);
	Point	n(2, 3);
	Point	o(3, 1);
	Point	p(3, 2.5);
	std::cout << "expected to be outside" << std::endl;
	std::cout << "Checking triangle: " << "M" << m << " " << "N" << n << " " << "O" << o << " " << "P" << p << std::endl;
	if (bsp(m, n, o, p) == true)
        std::cout << "Point is inside the triangle" << std::endl;
	else
        std::cout << "Point is outside the triangle" << std::endl;
    return (0);
}
