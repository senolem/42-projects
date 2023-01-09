/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:35:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/09 16:11:17 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP
# include "utils.hpp"

namespace ft
{
	template <class T, bool use_const = false>
	class Iterator
	{
		protected:
			T	*val;

		public:
			typedef typename enable_const<use_const, T&, const T&>::type	reference;
			typedef typename enable_const<use_const, T*, const T*>::type	pointer;
			typedef iterator_traits<Iterator>								iter_traits;
			typedef typename iter_traits::difference_type					difference_type;
			typedef typename iter_traits::value_type						value_type;

			Iterator(void) : val(NULL)
			{

			}

			Iterator(T *src) : val(src)
			{

			}

			Iterator(const Iterator<T, false> &src) : val(NULL)
			{
				*this = src;
			}

			virtual ~Iterator(void)
			{

			}

			Iterator			&operator=(Iterator const &rhs)
			{
				if (this != &rhs)
					val = rhs.val;
				return (*this);
			}

			bool							operator==(Iterator const &rhs) const
			{
				return (val == rhs.val);
			}

			bool							operator!=(Iterator const &rhs) const
			{
				return (val != rhs.val);
			}

			bool							operator>(Iterator const &rhs) const
			{
				return (val > rhs.val);
			}

			bool							operator>=(Iterator const &rhs) const
			{
				return (val >= rhs.val);
			}

			bool							operator<(Iterator const &rhs) const
			{
				return (val < rhs.val);
			}

			bool							operator<=(Iterator const &rhs) const
			{
				return (val <= rhs.val);
			}

			Iterator<T> 		&operator++(void)
			{
				val++;
				return (*this);
			}

			Iterator<T> 		operator++(int)
			{
				Iterator<T>	tmp(*this);
				val++;
				return (tmp);
			}

			Iterator<T> 		&operator--(void)
			{
				val--;
				return (*this);
			}

			Iterator<T> 		operator--(int)
			{
				Iterator<T>	tmp(*this);
				val--;
				return (tmp);
			}

			Iterator<T>			operator+(difference_type n) const
			{
				return Iterator(val + n);
			}

			friend Iterator<T>	operator+(difference_type n, Iterator const &rhs)
			{
				return (rhs.operator+(n));
			}

			Iterator<T>			operator-(difference_type n) const
			{
				return (Iterator(val + n));
			}

			difference_type					operator-(Iterator const &n) const
			{
				return (val - n.val);
			}

			Iterator<T>			&operator+=(difference_type n)
			{
				val += n;
				return (*this);
			}

			Iterator<T>			&operator-=(difference_type n)
			{
				val -= n;
				return (*this);
			}

			reference						operator*(void) const
			{
				return (*val);
			}

			pointer							operator->(void) const
			{
				return (val);
			}

			reference						operator[](size_type n) const
			{
				return (val[n]);
			}
	};
}

#endif