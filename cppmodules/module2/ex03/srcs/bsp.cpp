/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:03:35 by albaur            #+#    #+#             */
/*   Updated: 2022/08/31 16:17:29 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

static float	absval(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static float	area(Point p1, Point p2, Point p3)
{
	   return absval((p1.getX() * (p2.getY() - p3.getY()) + p2.getX() * (p3.getY() - p1.getY()) + p3.getX() * (p1.getY() - p2.getY())) / 2);
}

static float	sign(Point p1, Point p2, Point p3)
{
	return ((p1.getX() - p3.getX())) * (p2.getY() - p3.getY()) - (p2.getX() - p3.getX()) * (p1.getY() - p3.getY()); 
}

static bool	isoutofarea(Point const a, Point const b, Point const c, Point const point)
{
	float	abcarea = area(a, b, c);
	float	result = area(point, a, b) + area(point, b, c) + area(point, a, c);

	if (abcarea == result)
		return (false);
	else
		return (true);
}

bool    bsp(Point const a, Point const b, Point const c, Point const point)
{
	if (point == a || point == b || point == c)
		return (false);
	if (sign(a, b, point) == 0 || sign(b, c, point) == 0 || sign(a, c, point) == 0)
		return (false);
	if (isoutofarea(a, b, c, point))
		return (false);
	return (true);
}
