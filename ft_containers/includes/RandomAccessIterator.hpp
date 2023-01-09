/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:35:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/09 18:07:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP
# include "utils.hpp"

namespace ft
{

	template<class _iterator_category, class _value_type, class _difference_type = ptrdiff_t, class _pointer = _value_type*, class _reference = _value_type&>
	struct iterator
	{
		typedef _value_type			value_type;
		typedef _difference_type	difference_type;
		typedef _pointer			pointer;
		typedef _reference			reference;
		typedef _iterator_category	iterator_category;
	};

	template <class Iter>
	class IteratorWrapper
	{

		public:
			typedef Iter														iterator_type;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef typename iterator_traits<iterator_type>::reference			reference;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef size_t														size_type;


			IteratorWrapper(void) : _base(NULL)
			{

			}

			IteratorWrapper(Iter *src) : _base(src)
			{

			}

			IteratorWrapper(const IteratorWrapper<Iter> &src) : _base(NULL)
			{
				*this = src;
			}

			virtual ~IteratorWrapper(void)
			{

			}

			IteratorWrapper	&operator=(IteratorWrapper const &rhs)
			{
				if (this != &rhs)
					_base = rhs._base;
				return (*this);
			}

			IteratorWrapper<Iter>	&operator++(void)
			{
				_base++;
				return (*this);
			}

			IteratorWrapper<Iter>	operator++(int)
			{
				IteratorWrapper<Iter>	tmp(*this);
				_base++;
				return (tmp);
			}

			IteratorWrapper<Iter>	&operator--(void)
			{
				_base--;
				return (*this);
			}

			IteratorWrapper<Iter>	operator--(int)
			{
				IteratorWrapper<Iter>	tmp(*this);
				_base--;
				return (tmp);
			}

			IteratorWrapper<Iter>	operator+(difference_type n) const
			{
				return IteratorWrapper(_base + n);
			}

			friend IteratorWrapper<Iter>	operator+(difference_type n, IteratorWrapper const &rhs)
			{
				return (rhs.operator+(n));
			}

			IteratorWrapper<Iter>	operator-(difference_type n) const
			{
				return (IteratorWrapper(_base + n));
			}

			difference_type	operator-(IteratorWrapper const &n) const
			{
				return (_base - n._base);
			}

			IteratorWrapper<Iter>	&operator+=(difference_type n)
			{
				_base += n;
				return (*this);
			}

			IteratorWrapper<Iter>	&operator-=(difference_type n)
			{
				_base -= n;
				return (*this);
			}

			reference	operator*(void) const
			{
				return (*_base);
			}

			pointer	operator->(void) const
			{
				return (_base);
			}

			reference	operator[](size_type n) const
			{
				return (_base[n]);
			}

			template <class Iter1, class Iter2> friend
			bool operator==(const IteratorWrapper<Iter1>&, const IteratorWrapper<Iter2>&);
			template <class Iter1, class Iter2> friend
			bool operator<(const IteratorWrapper<Iter1>&, const IteratorWrapper<Iter2>&);
			template <class Iter1, class Iter2> friend
			bool operator!=(const IteratorWrapper<Iter1>&, const IteratorWrapper<Iter2>&);
			template <class Iter1, class Iter2> friend
			bool operator>(const IteratorWrapper<Iter1>&, const IteratorWrapper<Iter2>&);
			template <class Iter1, class Iter2> friend
			bool operator>=(const IteratorWrapper<Iter1>&, const IteratorWrapper<Iter2>&);
			template <class Iter1, class Iter2> friend
			bool operator<=(const IteratorWrapper<Iter1>&, const IteratorWrapper<Iter2>&);
			template <class Iter1, class Iter2> friend
			bool operator+(const IteratorWrapper<Iter1>&, const IteratorWrapper<Iter2>&);

		private:
			iterator_type	_base;
	};

	template <class Iter1, class Iter2>
	bool	operator==(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs._base == rhs._base);
	}

	template <class Iter1, class Iter2>
	bool	operator!=(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs._base != rhs._base);
	}

	template <class Iter1, class Iter2>
	bool	operator<(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs._base < rhs._base);
	}

	template <class Iter1, class Iter2>
	bool	operator<=(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs._base <= rhs._base);
	}

	template <class Iter1, class Iter2>
	bool	operator>(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs._base > rhs._base);
	}
	
	template <class Iter1, class Iter2>
	bool	operator>=(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs._base >= rhs._base);
	}
}

#endif