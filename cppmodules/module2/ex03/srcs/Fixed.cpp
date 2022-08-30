/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:19:42 by albaur            #+#    #+#             */
/*   Updated: 2022/08/30 23:06:18 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void) : integer(0)
{
	//std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &src)
{
	*this = src;
}

Fixed	&Fixed::operator=(const Fixed &src)
{
	integer = src.getRawBits();
	return (*this);
}

Fixed::~Fixed(void)
{
	//std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const int nbint)
{
	integer = nbint << width;
}

Fixed::Fixed(const float nbfloat)
{
	float	bits = 1 << width;
	integer = (int)roundf(nbfloat * bits);
}

int	Fixed::getRawBits(void)	const
{
	return (integer);
}

void	Fixed::setRawBits(const int raw)
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

bool	Fixed::operator>(Fixed src) const
{
	return (this->toFloat() > src.toFloat());
}

bool	Fixed::operator<(Fixed src) const
{
	return (this->toFloat() < src.toFloat());
}

bool	Fixed::operator>=(Fixed src) const
{
	return (this->toFloat() >= src.toFloat());
}

bool	Fixed::operator<=(Fixed src) const
{
	return (this->toFloat() <= src.toFloat());
}

bool	Fixed::operator==(Fixed src) const
{
	return (this->toFloat() == src.toFloat());
}

bool	Fixed::operator!=(Fixed src) const
{
	return (this->toFloat() != src.toFloat());
}

Fixed	Fixed::operator+(Fixed src) const
{
	return (this->toFloat() + src.toFloat());
}

Fixed	Fixed::operator-(Fixed src) const
{
	return (this->toFloat() - src.toFloat());
}

Fixed	Fixed::operator*(Fixed src) const
{
	return (this->toFloat() * src.toFloat());
}

Fixed	Fixed::operator/(Fixed src) const
{
	return (this->toFloat() / src.toFloat());
}

Fixed	Fixed::operator++(int)
{
	Fixed tmp;

	tmp = *this;
	this->integer++;
	return (tmp);
}

Fixed	Fixed::operator++(void)
{
	this->integer++;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed tmp;

	tmp = *this;
	this->integer--;
	return (tmp);
}

Fixed	Fixed::operator--(void)
{
	this->integer--;
	return (*this);
}

Fixed	&Fixed::min(Fixed &n1, Fixed &n2)
{
	return (n1.toFloat() <= n2.toFloat() ? (n1):(n2));
}

const Fixed	&Fixed::min(const Fixed &n1, const Fixed &n2)
{
	return (n1.toFloat() <= n2.toFloat() ? (n1):(n2));
}

Fixed	&Fixed::max(Fixed &n1, Fixed &n2)
{
	return (n1.toFloat() >= n2.toFloat() ? (n1):(n2));
}

const Fixed	&Fixed::max(const Fixed &n1, const Fixed &n2)
{
	return (n1.toFloat() >= n2.toFloat() ? (n1):(n2));
}