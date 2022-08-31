/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:57:22 by albaur            #+#    #+#             */
/*   Updated: 2022/08/31 14:54:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
	private:
	const Fixed	x;
	const Fixed	y;

	public:
	Point(void);
	Point(const float f1, const float f2);
	Point(const Point &src);
	Point	&operator=(const Point &src);
	~Point(void);
	bool	operator==(Point src) const;

	float getX(void) const;
	float getY(void) const;

};

std::ostream &operator<<(std::ostream &stream, Point const &src);
bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif