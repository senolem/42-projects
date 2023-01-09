/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseRandomAccessIterator.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:34:58 by albaur            #+#    #+#             */
/*   Updated: 2023/01/09 14:08:56 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSERANDOMACCESSITERATOR_HPP
# define REVERSERANDOMACCESSITERATOR_HPP
# include "utils.hpp"

namespace ft
{
	template <class Iterator>
	class ReverseIteratorWrapper
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

			ReverseIteratorWrapper(void) : _base(NULL)
			{

			}
			
			explicit ReverseIteratorWrapper(iterator_type i) : _base(i)
			{

			}

			template <class Iter>
			ReverseIteratorWrapper(const ReverseIteratorWrapper<Iter> &i) : _base(i.base())
			{

			}

			template <class Iter>
			ReverseIteratorWrapper	&operator=(const ReverseIteratorWrapper<Iter> &i)
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

			ReverseIteratorWrapper	operator+(difference_type n) const
			{
				return (ReverseIteratorWrapper(_base - n));
			}

			ReverseIteratorWrapper	operator-(difference_type n) const
			{
				return (ReverseIteratorWrapper(_base + n));
			}

			template <class T>
			difference_type	operator-(ReverseIteratorWrapper<T> const &n)
			{
				return (n.base().operator-(_base));
			}

			ReverseIteratorWrapper	&operator++(void)
			{
				--_base;
				return(*this);
			}

			ReverseIteratorWrapper	operator++(int) 
			{
				ReverseIteratorWrapper	tmp(*this);

				--_base;
				return (tmp);
			}

			ReverseIteratorWrapper	&operator--(void)
			{
				++_base;
				return(*this);
			}

			ReverseIteratorWrapper	operator--(int)
			{
				ReverseIteratorWrapper	tmp(*this);

				++_base;
				return (tmp);
			}

			ReverseIteratorWrapper	&operator+=(difference_type n)
			{
				_base -= n;
				return (*this);
			}

			ReverseIteratorWrapper	&operator-=(difference_type n)
			{
				_base += n;
				return (*this);
			}
	};

	template <class Iter1, class Iter2>
	bool	operator==(const ReverseIteratorWrapper<Iter1> &lhs, const ReverseIteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator!=(const ReverseIteratorWrapper<Iter1> &lhs, const ReverseIteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator<(const ReverseIteratorWrapper<Iter1> &lhs, const ReverseIteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator<=(const ReverseIteratorWrapper<Iter1> &lhs, const ReverseIteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator>(const ReverseIteratorWrapper<Iter1> &lhs, const ReverseIteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	
	template <class Iter1, class Iter2>
	bool	operator>=(const ReverseIteratorWrapper<Iter1> &lhs, const ReverseIteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	
	template <class Iterator>
	ReverseIteratorWrapper<Iterator>	operator+(typename ReverseIteratorWrapper<Iterator>::difference_type n, const ReverseIteratorWrapper<Iterator> &i)
	{
		return (ReverseIteratorWrapper<Iterator>(i.base() - n));
	}

	template <class Iterator>
	typename ReverseIteratorWrapper<Iterator>::difference_type	operator-(const ReverseIteratorWrapper<Iterator> &lhs, const ReverseIteratorWrapper<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif