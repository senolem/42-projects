/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:25:17 by albaur            #+#    #+#             */
/*   Updated: 2022/10/03 16:54:27 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(void) : N(1), nb(0), array(1)
{
	
}

Span::Span(const Span &src) : N(src.N), nb(src.nb), array(src.array)
{

}

Span::~Span(void)
{

}

Span	&Span::operator=(const Span &src)
{
	if (this != &src)
	{
		N = src.N;
		nb = src.nb;
		array = src.array;
	}
	return (*this);
}

Span::Span(unsigned int sizeN) : N(sizeN), nb(0), array(sizeN)
{
	
}

void	Span::addNumber(int newNumber)
{
	try
	{
		if (nb >= N)
			throw(Exception("Span::CannotAddMoreNumbersException"));
		else
			array[nb++] = newNumber;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

unsigned int		Span::shortestSpan(void)
{
	int									nb;
	std::vector<int>					tmp(array);
	std::vector<int>::const_iterator	min = min_element(tmp.begin(), tmp.end());

	nb = (*min);
	tmp.erase(min);
	std::vector<int>::const_iterator	min2 = min_element(tmp.begin(), tmp.end());
	return (static_cast<int>(*min2) - nb);
}

unsigned int		Span::longestSpan(void)
{
	std::vector<int>::const_iterator	min = min_element(array.begin(), array.end());
	std::vector<int>::const_iterator	max = max_element(array.begin(), array.end());

	return (static_cast<int>(*max) - static_cast<int>(*min));
}

void	Span::displayArray(void)
{
	std::vector<int>::iterator iter;
	std::vector<int>::iterator tmp;

	std::cout << "[";
	for (iter = array.begin(); iter != array.end(); ++iter)
	{
		std::cout << *iter;
		tmp = iter;
		if (++tmp != array.end())
			std::cout << ", ";
	}
	std::cout << "] (" << array.size() << " elements)" << std::endl;
}

void	Span::addNumberRandom(void)
{
	srand(time(NULL));
	std::generate(array.begin() + nb, array.end(), getRNG);
	nb = N;
}

int	Span::getSize(void)
{
	return (array.size());
}

int	getRNG(void)
{
	return (rand() % 100);
}
