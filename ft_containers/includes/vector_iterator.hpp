/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:35:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/19 16:22:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP
# include "utils.hpp"

namespace ft
{	
	template <class T>
	class iter
	{
		protected:
			typedef iterator_traits<T>					iter_traits;

		public:
			typedef T									value_type;
			typedef std::random_access_iterator_tag		iterator_category;
			typedef ptrdiff_t							difference_type;
			typedef T*									pointer;
			typedef const T*							const_pointer;
			typedef T&									reference;
			typedef const T&							const_reference;
			typedef iter<const T>						const_iterator;
		
		private:
			pointer	_data;
		
		public:
			iter(void) : _data()
			{

			}

			iter(pointer other) : _data(other)
			{

			}

			iter(const iter &other) : _data(other._data)
			{

			}

			~iter(void)
			{

			}

			pointer	base(void) const
			{
				return (_data);
			}

			iter	operator=(const iter &other)
			{
				if (this != &other)
					_data = other.base();
				return (*this);
			}

			iter	operator+(difference_type n) const
			{
				return (iter(base() + n));
			}

			iter&	operator++(void)
			{
				_data++;
				return (*this);		
			}

			iter	operator++(int)
			{
				iter(tmp) = *this;
				_data++;
				return (tmp);
			}

			iter&	operator+=(difference_type n)
			{
				_data += n;
				return (*this);
			}

			iter	operator-(difference_type n) const 
			{
				return (iter(base() - n)); 
			}

			iter&	operator--(void)
			{
				_data--;
				return (*this);
			}

			iter	operator--(int)
			{
				iter(tmp) = *this;
				_data--;
				return (tmp);
			}

			iter	operator-=(difference_type n)
			{
				_data -= n;
				return (*this);
			}

			reference	operator*(void)
			{
				return (*_data);
			}

			const_reference	operator*(void) const
			{
				return (*_data);
			}

			pointer	operator->(void)
			{
				return &(operator*());
			}

			const_pointer	operator->(void) const
			{
				return &(operator*());
			}

			reference	operator[](difference_type n)
			{
				return (base()[n]);
			}

			const_reference	operator[](difference_type n) const
			{
				return (base()[n]);
			}

			friend bool	operator==(const iter &lhs, const iter &rhs)
			{
				return (lhs.base() == rhs.base());
			}

			friend bool	operator!=(const iter &lhs, const iter &rhs)
			{
				return (lhs.base() != rhs.base());
			}

			friend bool	operator>(const iter &lhs, const iter &rhs)
			{
				return (lhs.base() > rhs.base());
			}

			friend bool	operator<=(const iter &lhs, const iter &rhs)
			{
				return (lhs.base() <= rhs.base());
			}

			friend bool	operator<(const iter &lhs, const iter &rhs)
			{
				return (lhs.base() < rhs.base());
			}

			friend bool	operator>=(const iter &lhs, const iter &rhs)
			{
				return (lhs.base() >= rhs.base());
			}

			operator	const_iterator(void) const
			{
				return (const_iterator(_data));
			}
	};

	template <class T>
	iter<T>	operator+(typename iter<T>::difference_type n, const iter<T>& it)
	{
		return (it + n);
	}

	template <class Iter1, class Iter2>
	typename iter<Iter1>::difference_type	operator-(const iter<Iter1> &lhs, const iter<Iter2> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <class iterator>
	class reverse_iter
	{
		public:
			typedef typename iterator_traits<iterator>::value_type			value_type;
			typedef iterator												iterator_type;
			typedef typename iterator_traits<iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			typedef typename iterator_traits<iterator>::pointer				pointer;
			typedef typename iterator_traits<iterator>::reference			reference;

		private:
			iterator _data;

		public:
			reverse_iter() : _data()
			{

			}

			reverse_iter(iterator_type other) : _data(other)
			{

			}

			template <class Iter>
			reverse_iter(const reverse_iter<Iter> &other) : _data(other.base())
			{

			}

			template <class Iter>
			reverse_iter	&operator=(const reverse_iter<Iter> &other)
			{
				_data = other.base();
				return  *this;
			}

			~reverse_iter(void)
			{

			}

			iterator_type	base(void) const
			{
				return (_data);
			}

			reverse_iter	operator+(difference_type n) const
			{
				return (reverse_iter(_data - n));
			}

			reverse_iter&	operator++(void)
			{
				--_data;
				return (*this);
			}

			reverse_iter	operator++(int)
			{
				reverse_iter tmp = *this;
				--_data;
				return (tmp);
			}

			reverse_iter&	operator+=(difference_type n)
			{
				_data -= n;
				return (*this);
			}

			reverse_iter	operator-(difference_type n) const
			{
				return (reverse_iter(_data + n));
			}

			reverse_iter&	operator--()
			{
				++_data;
				return (*this);
			}

			reverse_iter	operator--(int)
			{
				reverse_iter tmp = *this;
				++_data;
				return (tmp);
			}

			reverse_iter	operator-=(difference_type n)
			{
				_data += n;
				return (*this);
			}

			reference	operator*() const
			{
				return ((--iterator(_data)).operator*());
			}

			pointer	operator->() const
			{
				return (&(operator*()));
			}

			reference	operator[] (difference_type n) const
			{
				return (*operator+(n));
			}
	};

	template <class Iter1, class Iter2>
	bool	operator==(const reverse_iter<Iter1> &lhs, const reverse_iter<Iter2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator!=(const reverse_iter<Iter1> &lhs, const reverse_iter<Iter2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator<(const reverse_iter<Iter1> &lhs, const reverse_iter<Iter2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator<=(const reverse_iter<Iter1> &lhs, const reverse_iter<Iter2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator>(const reverse_iter<Iter1> &lhs, const reverse_iter<Iter2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter1, class Iter2>
	bool	operator>=(const reverse_iter<Iter1> &lhs, const reverse_iter<Iter2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iter>
	reverse_iter<Iter>	operator+( typename reverse_iter<Iter>::difference_type n, const reverse_iter<Iter> &iter)
	{
		return (iter + n);
	}

	template <class Iter1, class Iter2>
	typename reverse_iter<Iter1>::difference_type	operator-( const reverse_iter<Iter1> &lhs, const reverse_iter<Iter2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
};

#endif