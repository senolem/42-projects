/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:48:38 by albaur            #+#    #+#             */
/*   Updated: 2022/09/27 17:00:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include "Exception.hpp"

template <typename T = int>
class Array
{
	private:
	unsigned int	arrsize;
	T				*array;

	public:
	Array(void) :  arrsize(0), array(new T[0])
	{
		std::cout << "New array address : " << array << std::endl;
	}
	Array(unsigned int n) : arrsize(n), array(new T[n])
	{
		for (size_t i = 0; i < arrsize; ++i)
			array[i] = i;
		std::cout << "New array address : " << array << std::endl;
	}
	Array(Array<T> const &src) : arrsize(src.arrsize), array(new T[src.arrsize])
	{
		for (unsigned int i = 0; i < arrsize; ++i)
			this->array[i] = src.array[i];
		std::cout << "New array address : " << array << std::endl;
	}
	~Array(void)
	{
		delete[] array;
	}
	Array	&operator=(Array const &src)
	{
		if (this != &src)
		{
			arrsize = src.arrsize;
			delete[] array;
			array = new T[arrsize];
			for (size_t i = 0; i < arrsize; ++i)
				array[i] = src.array[i];
			std::cout << "New array address : " << array << std::endl;
		}
		else
			return (*this);
	}
	unsigned int size(void) const
	{
		return (arrsize);
	}
	void	display(void) const
	{
		std::cout << "[";
		for (size_t i = 0; i < arrsize; ++i)
		{
			std::cout << array[i];
			if (i + 1 < arrsize)
				std::cout << ", ";
		}
		std::cout << "]" << std::endl;
	}
	T	&operator[](size_t const &i)
	{
		try
		{
			if (i >= arrsize)
				throw Exception("Array::IndexOutOfRangeException");
			else
				return (array[i]);
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		return (array[0]);
	}
};

template <typename T>
std::ostream &operator<<(std::ostream &stream, Array<T> &src)
{
	stream << "[";
	for (size_t i = 0; i < src.size(); ++i)
	{
		stream << src[i];
		if (i + 1 < src.size())
			stream << ", ";
	}
	stream << "]" << std::endl;
	return (stream);
}

#endif