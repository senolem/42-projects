/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:25:17 by albaur            #+#    #+#             */
/*   Updated: 2022/10/04 16:13:19 by albaur           ###   ########.fr       */
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

Span::Span(unsigned int sizeN) : N(sizeN), nb(0), array(0)
{
	
}

void	Span::addNumber(int newNumber)
{
	try
	{
		if (nb >= N)
			throw(Exception("Span::CannotAddMoreNumbersException"));
		else
		{
			++nb;
			array.push_back(newNumber);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

unsigned int		Span::shortestSpan(void)
{
	int							dist = 0;
	int							tmpDist = 0;
	std::vector<int>			tmp(array);
	std::vector<int>::iterator	iter;
	std::vector<int>::iterator	tmpIter;

	try
	{
		if (array.size() == 0)
			throw(Exception("Span::EmptyVectorException"));
		else if (array.size() == 1)
			throw(Exception("Span::OnlyElementException"));
		else
		{
			std::sort(tmp.begin(), tmp.end());
			for (iter = tmp.begin(); iter != tmp.end(); ++iter)
			{
				tmpIter = iter;
				++tmpIter;
				tmpDist = *tmpIter - *iter;
				if (iter == tmp.begin() || (tmpDist < dist && tmpIter != tmp.end()))
					dist = tmpDist;
			}
			return (dist);
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (1);
}

unsigned int		Span::longestSpan(void)
{
	std::vector<int>::const_iterator	min = min_element(array.begin(), array.end());
	std::vector<int>::const_iterator	max = max_element(array.begin(), array.end());
	try
	{
		if (array.size() == 0)
			throw(Exception("Span::EmptyVectorException"));
		else if (array.size() == 1)
			throw(Exception("Span::OnlyElementException"));
		else
			return (static_cast<int>(*max) - static_cast<int>(*min));
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (1);
}

void	Span::displayArray(void)
{
	std::cout << "[";
	for (size_t i = 0; i < nb; ++i)
	{
		std::cout << array[i];
		if (i + 1 < nb)
			std::cout << ", ";
	}
	std::cout << "] (" << nb << " elements)" << std::endl;
}

void	Span::addNumberRandom(void)
{
	srand(time(NULL));
	for (size_t i = 0; i < N; ++i)
		this->addNumber(getRNG());
}

int	Span::getSize(void)
{
	return (array.size());
}

int	getRNG(void)
{
	return (rand() % 100);
}
