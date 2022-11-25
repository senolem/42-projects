/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:44:03 by albaur            #+#    #+#             */
/*   Updated: 2022/11/25 16:10:47 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "vector_class.hpp"

namespace ft
{
	template<class T, class Alloc>
	vector<T, Alloc>::iterator::iterator(void) : RandomAccessIterator<T>()
	{

	}

	template<class T, class Alloc>
	vector<T, Alloc>::iterator::iterator(T *src) : RandomAccessIterator<T>(src)
	{

	}

	template<class T, class Alloc>
	vector<T, Alloc>::iterator::iterator(iterator const &src) : RandomAccessIterator<T>(src)
	{

	}

	template<class T, class Alloc>
	vector<T, Alloc>::iterator::iterator(const RandomAccessIterator<T> &src) : RandomAccessIterator<T>(src)
	{

	}

	template<class T, class Alloc>
	vector<T, Alloc>::iterator::~iterator(void)
	{
		
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator::reference	vector<T, Alloc>::iterator::operator*(void) const
	{
		return (*this->val);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator::pointer	vector<T, Alloc>::iterator::operator->(void) const
	{
		return (this->val);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator::reference	vector<T, Alloc>::iterator::operator[](size_type n) const
	{
		return (this->val[n]);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator	&vector<T, Alloc>::iterator::operator+=(difference_type n)
	{
		this->val += n;
		return (*this);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator	&vector<T, Alloc>::iterator::operator-=(difference_type n)
	{
		this->val -= n;
		return (*this);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator::difference_type	vector<T, Alloc>::iterator::operator-(const RandomAccessIterator<T> &n) const
	{
		return (RandomAccessIterator<T>operator-(n));
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::iterator::operator-(difference_type n) const
	{
		return (RandomAccessIterator<T>operator-(n));
	}

	
}

#endif
