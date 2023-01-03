/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseRandomAccessIterator.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:34:58 by albaur            #+#    #+#             */
/*   Updated: 2023/01/03 16:26:48 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSERANDOMACCESSITERATOR_HPP
# define REVERSERANDOMACCESSITERATOR_HPP
# include "RandomAccessIterator.hpp"

namespace ft
{
	template <class Iterator>
	class ReverseRandomAccessIterator
	{
		protected:
			Iterator	_base;

		public:
			typedef Iterator							iterator_type;
			typedef typename Iterator::difference_type	difference_type;
			typedef typename Iterator::pointer			pointer;
			typedef typename Iterator::reference		reference;

			ReverseRandomAccessIterator(void) : _base(NULL) {}
			explicit ReverseRandomAccessIterator(iterator_type i) : _base(i) {}
			template <class Iter>
			ReverseRandomAccessIterator(const ReverseRandomAccessIterator<Iter> &i) : _base(i.base()) {}
			template <class Iter>
			ReverseRandomAccessIterator	&operator=(const ReverseRandomAccessIterator<Iter> &i) {_base = i.base; return (*this);}

			iterator_type	base(void) const {return (_base);};

			reference		operator*(void) const {return *(_base);}
			pointer			operator->(void) const {return (&(operator*()));}
			reference		operator[](difference_type n) const {return *(*this + n);}
			ReverseRandomAccessIterator	operator+(difference_type n) const {return (ReverseRandomAccessIterator(_base - n));}
			ReverseRandomAccessIterator	operator-(difference_type n) const {return (ReverseRandomAccessIterator(_base + n));}
			template <class T>
			difference_type	operator-(ReverseRandomAccessIterator<T> const &n) {return (n.base().operator-(_base));}
			ReverseRandomAccessIterator	&operator++(void) {--_base; return(*this);}
			ReverseRandomAccessIterator	operator++(int) {ReverseRandomAccessIterator	tmp(*this); --_base; return (tmp);}
			ReverseRandomAccessIterator	&operator--(void) {++_base; return(*this);}
			ReverseRandomAccessIterator	operator--(int) {ReverseRandomAccessIterator	tmp(*this); ++_base; return (tmp);}
			ReverseRandomAccessIterator	&operator+=(difference_type n) {_base -= n; return (*this);}
			ReverseRandomAccessIterator	&operator-=(difference_type n) {_base += n; return (*this);}
	};

	template <class Iter1, class Iter2>
	bool	operator==(const ReverseRandomAccessIterator<Iter1> &lhs, const ReverseRandomAccessIterator<Iter2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator!=(const ReverseRandomAccessIterator<Iter1> &lhs, const ReverseRandomAccessIterator<Iter2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator<(const ReverseRandomAccessIterator<Iter1> &lhs, const ReverseRandomAccessIterator<Iter2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator<=(const ReverseRandomAccessIterator<Iter1> &lhs, const ReverseRandomAccessIterator<Iter2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator>(const ReverseRandomAccessIterator<Iter1> &lhs, const ReverseRandomAccessIterator<Iter2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	
	template <class Iter1, class Iter2>
	bool	operator>=(const ReverseRandomAccessIterator<Iter1> &lhs, const ReverseRandomAccessIterator<Iter2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	
	template <class Iterator>
	ReverseRandomAccessIterator<Iterator>	operator+(typename ReverseRandomAccessIterator<Iterator>::difference_type n, const ReverseRandomAccessIterator<Iterator> &i)
	{
		return (ReverseRandomAccessIterator<Iterator>(i.base() - n));
	}

	template <class Iterator>
	typename ReverseRandomAccessIterator<Iterator>::difference_type	operator-(const ReverseRandomAccessIterator<Iterator> &lhs, const ReverseRandomAccessIterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif