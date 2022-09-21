/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:59:39 by albaur            #+#    #+#             */
/*   Updated: 2022/09/21 15:22:23 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Identify.hpp"

Base *generate(void)
{
	typedef std::chrono::high_resolution_clock	hrc;
	Base										*ptr;
	hrc::time_point								beginning = hrc::now();
	hrc::duration								d = hrc::now() - beginning;
	unsigned									seed = d.count();
	std::default_random_engine					generator(seed);
	std::uniform_int_distribution<int>			distribution(1, 3);
	int											RNG = distribution(generator);
	
	switch (RNG)
	{
	case 1:
		ptr = new A;
		break ;
	case 2:
		ptr = new B;
		break ;
	case 3:
		ptr = new C;
		break ;
	}
	return (ptr);
}

void identify(Base *p)
{
	std::string str;
	A	*a;
	B	*b;
	C	*c;
	if ((a = dynamic_cast<A *>(p)))
		std::cout << "Type is A" << str << std::endl;
	if ((b = dynamic_cast<B *>(p)))
		std::cout << "Type is B" << str << std::endl;
	if ((c = dynamic_cast<C *>(p)))
		std::cout << "Type is C" << str << std::endl;
}

void identify(Base &p)
{
	std::string str;

	try
	{
		A &refA = dynamic_cast<A &>(p);
		(void)refA;
		str = "A";
	}
	catch (std::exception & e)
	{
		(void)e;
	}
	try
	{
		B &refB = dynamic_cast<B &>(p);
		(void)refB;
		str = "B";
	}
	catch (std::exception &e)
	{
		(void)e;
	}
	try
	{
		C &refC = dynamic_cast<C &>(p);
		(void)refC;
		str = "C";
	}
	catch (std::exception &e)
	{
		(void)e;
	}
	std::cout << "Type is " << str << std::endl;
}
