/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:03:26 by albaur            #+#    #+#             */
/*   Updated: 2022/08/31 14:55:57 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(void) : x(0), y(0)
{
	//std::cout << "Default constructor called" << std::endl;
}

Point::Point(const float f1, const float f2) : x(f1), y(f2)
{
	//std::cout << "Copy constructor called" << std::endl;
}

Point::Point(const Point &src) : x(src.x), y(src.y)
{
	//std::cout << "Assignment constructor called" << std::endl;
}

Point	&Point::operator=(const Point &src)
{
	(void)src;
	return (*this);
}

Point::~Point(void)
{
	//std::cout << "Destructor called" << std::endl;
}

bool	Point::operator==(Point src) const
{
	if (this->getX() == src.getX() && this->getY() == src.getY())
		return (true);
	else
		return (false);
}

float	Point::getX(void) const
{
	return (this->x.toFloat());
}


float	Point::getY(void) const
{
	return (this->y.toFloat());
}

std::ostream	&operator<<(std::ostream &stream, const Point &src)
{
	return (stream << "[" << src.getX() << ", " << src.getY() << "]");
}