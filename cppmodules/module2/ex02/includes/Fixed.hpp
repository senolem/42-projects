/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:19:56 by albaur            #+#    #+#             */
/*   Updated: 2022/08/29 15:12:04 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	private:
	int					integer;
	const static int	width = 8;

	public:
	Fixed(void);
	Fixed(Fixed const &src);
	Fixed	&operator=(Fixed const &src);
	~Fixed(void);
	Fixed(int const nbint);
	Fixed(float const nbfloat);

	int		getRawBits(void) const;
	void	setRawBits(int const raw);
	float	toFloat(void) const;
	int		toInt(void) const;

	bool	operator>(Fixed src) const;
	bool	operator<(Fixed src) const;
	bool	operator>=(Fixed src) const;
	bool	operator<=(Fixed src) const;
	bool	operator==(Fixed src) const;
	bool	operator!=(Fixed src) const;
	Fixed	operator+(Fixed src) const;
	Fixed	operator-(Fixed src) const;
	Fixed	operator*(Fixed src) const;
	Fixed	operator/(Fixed src) const;
	Fixed	operator++(int);
	Fixed	operator++(void);
	Fixed	operator--(int);
	Fixed	operator--(void);
	static Fixed	&min(Fixed &n1, Fixed &n2);
	static const Fixed	&min(const Fixed &n1, const Fixed &n2);
	static Fixed	&max(Fixed &n1, Fixed &n2);
	static const Fixed	&max(const Fixed &n1, const Fixed &n2);
};

std::ostream &operator<<(std::ostream &stream, Fixed const &src);

#endif