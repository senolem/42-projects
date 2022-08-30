/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:19:30 by albaur            #+#    #+#             */
/*   Updated: 2022/08/30 23:24:18 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

int main (void)
{
	//expected to be inside
    if (bsp(Point(1, 1), Point(2, 3), Point(3, 1), Point(2, 2)) == true)
        std::cout << "Point is inside the triangle" << std::endl;
	else
        std::cout << "Point is outside the triangle" << std::endl;

	//expected to be outside
	if (bsp(Point(1, 1), Point(2, 3), Point(3, 1), Point(2.5, 2)) == true)
        std::cout << "Point is inside the triangle" << std::endl;
	else
        std::cout << "Point is outside the triangle" << std::endl;
	
	//expected to be outside (on C point)
	if (bsp(Point(1, 1), Point(2, 3), Point(3, 1), Point(3, 1)) == true)
        std::cout << "Point is inside the triangle" << std::endl;
	else
        std::cout << "Point is outside the triangle" << std::endl;
    return (0);
}
