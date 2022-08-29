/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:19:56 by albaur            #+#    #+#             */
/*   Updated: 2022/08/28 15:16:27 by albaur           ###   ########.fr       */
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
};

std::ostream &operator<<(std::ostream &stream, Fixed const &src);

#endif