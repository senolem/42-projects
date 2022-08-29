/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:19:42 by albaur            #+#    #+#             */
/*   Updated: 2022/08/29 12:39:48 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void) : integer(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const &src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed	&Fixed::operator=(Fixed const &src)
{
	std::cout << "Copy assignement operator called" << std::endl;
	integer = src.getRawBits();
	return (*this);
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(int const nbint)
{
	std::cout << "Int constructor called" << std::endl;
	integer = nbint << width;
}

Fixed::Fixed(float const nbfloat)
{
	std::cout << "Float constructor called" << std::endl;
	float	bits = 1 << width;
	integer = (int)roundf(nbfloat * bits);
}

int	Fixed::getRawBits(void)	const
{
	return (integer);
}

void	Fixed::setRawBits(int const raw)
{
	integer = raw;
}

float	Fixed::toFloat(void) const
{
	float	bits = 1 << width;
	float	nb;

	nb = (float)integer / bits;
	return (nb);
}

int		Fixed::toInt(void) const
{
	return (integer >> width);
}

std::ostream	&operator<<(std::ostream &stream, const Fixed &src)
{
	return (stream << src.toFloat());
}