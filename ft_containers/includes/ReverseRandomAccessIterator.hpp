/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseRandomAccessIterator.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:34:58 by albaur            #+#    #+#             */
/*   Updated: 2023/01/09 16:08:37 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSERANDOMACCESSITERATOR_HPP
# define REVERSERANDOMACCESSITERATOR_HPP
# include "utils.hpp"

namespace ft
{
	template <class Iterator>
	class ReverseIterator
	{
		protected:
			Iterator	_base;

		public:
			typedef Iterator								iterator_type;
			typedef iterator_traits<Iterator>				iter_traits;
			typedef typename iter_traits::reference			reference;
			typedef typename iter_traits::pointer			pointer;
			typedef typename iter_traits::difference_type	difference_type;
			typedef typename iter_traits::value_type		value_type;

			ReverseIterator(void) : _base(NULL)
			{

			}
			
			explicit ReverseIterator(iterator_type i) : _base(i)
			{

			}

			template <class Iter>
			ReverseIterator(const ReverseIterator<Iter> &i) : _base(i.base())
			{

			}

			template <class Iter>
			ReverseIterator	&operator=(const ReverseIterator<Iter> &i)
			{
				_base = i.base;
				return (*this);
			}

			iterator_type	base(void) const
			{
				return (_base);
			}

			reference		operator*(void) const
			{
				return *(_base);
			}

			pointer			operator->(void) const
			{
				return (&(operator*()));
			}

			reference		operator[](difference_type n) const
			{
				return *(*this + n);
			}

			ReverseIterator	operator+(difference_type n) const
			{
				return (ReverseIterator(_base - n));
			}

			ReverseIterator	operator-(difference_type n) const
			{
				return (ReverseIterator(_base + n));
			}

			template <class T>
			difference_type	operator-(ReverseIterator<T> const &n)
			{
				return (n.base().operator-(_base));
			}

			ReverseIterator	&operator++(void)
			{
				--_base;
				return(*this);
			}

			ReverseIterator	operator++(int) 
			{
				ReverseIterator	tmp(*this);

				--_base;
				return (tmp);
			}

			ReverseIterator	&operator--(void)
			{
				++_base;
				return(*this);
			}

			ReverseIterator	operator--(int)
			{
				ReverseIterator	tmp(*this);

				++_base;
				return (tmp);
			}

			ReverseIterator	&operator+=(difference_type n)
			{
				_base -= n;
				return (*this);
			}

			ReverseIterator	&operator-=(difference_type n)
			{
				_base += n;
				return (*this);
			}
	};

	template <class Iter1, class Iter2>
	bool	operator==(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator!=(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator<(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator<=(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator>(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	
	template <class Iter1, class Iter2>
	bool	operator>=(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	
	template <class Iterator>
	ReverseIterator<Iterator>	operator+(typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator> &i)
	{
		return (ReverseIterator<Iterator>(i.base() - n));
	}

	template <class Iterator>
	typename ReverseIterator<Iterator>::difference_type	operator-(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif