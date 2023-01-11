/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:35:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/11 18:03:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP
# include "utils.hpp"

namespace ft
{
	template <class _iterator_category, class _value_type, class _difference_type = ptrdiff_t, class _pointer = _value_type*, class _reference = _value_type&>
	struct iterator
	{
		typedef _iterator_category	iterator_category;
		typedef _value_type			value_type;
		typedef _difference_type	difference_type;
		typedef _pointer			pointer;
		typedef _reference			reference;
	};

	template <class Iter>
	class IteratorWrapper
	{
		protected:
			Iter											_base;
			typedef iterator_traits<Iter>					iter_traits;

		public:
			typedef Iter									value_type;
			typedef typename iter_traits::difference_type	difference_type;
			typedef typename iter_traits::reference			reference;
			typedef typename iter_traits::pointer			pointer;
			typedef std::size_t								size_type;

			IteratorWrapper(void) : _base(Iter())
			{

			}

			IteratorWrapper(const value_type &it) : _base(it)
			{

			}

			template <class T>
			IteratorWrapper(const IteratorWrapper<T> &other): _base(other.base())
			{

			}

			reference	operator*(void) const
			{
				return *(_base);
			}

			pointer	operator->(void) const
			{
				return &(operator*());
			}

			value_type	base(void) const
			{
				return (_base);
			}

			IteratorWrapper	&operator++(void)
			{
				_base++;
				return (*this);
			}

			IteratorWrapper	operator++(int)
			{
				IteratorWrapper tmp = *this;
				++(*this);
				return (tmp);
			}

			IteratorWrapper	&operator--(void)
			{
				_base--;
				return (*this);
			}

			IteratorWrapper	operator--(int)
			{
				IteratorWrapper tmp = *this;
				--(*this);
				return (tmp);
			}

			IteratorWrapper	&operator+=(std::size_t n)
			{
				_base += n;
				return (*this);
			}

			IteratorWrapper	&operator-=(std::size_t n)
			{
				_base -= n;
				return (*this);
			}

			IteratorWrapper	operator+(std::size_t n) const
			{
				return (_base + n);
			}

			IteratorWrapper	operator-(std::size_t n) const
			{
				return (_base - n);
			}

			IteratorWrapper	&operator[](std::size_t index) const
			{
				return *(*this + index);
			}

			ptrdiff_t	operator-(const IteratorWrapper &x)
			{
				return (_base - x._base);
			}
	};

	template <class Iter1, class Iter2>
	bool operator==(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator!=(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator<(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	
	template <class Iter1, class Iter2>
	bool operator<=(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator>(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator>=(const IteratorWrapper<Iter1> &lhs, const IteratorWrapper<Iter2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class T>
	class Iterator : public iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef T																		value_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::reference		reference;
			typedef typename iterator<std::random_access_iterator_tag, T>::pointer			pointer;
		
		protected:
			pointer	_pointer;
		
		public:
			Iterator(void) : _pointer()
			{

			}

			Iterator(value_type *pointer) : _pointer(pointer)
			{

			}

			pointer	base(void) const
			{
				return (_pointer);
			}

			reference	operator*(void)
			{
				return *(_pointer);
			}

			pointer	operator->(void)
			{
				return &(operator*());
			}

			Iterator	&operator++(void)
			{
				_pointer++;
				return *this;
			}

			Iterator	operator++(int)
			{
				Iterator tmp = *this;
				++(*this);
				return tmp;
			}

			Iterator	&operator--(void)
			{
				_pointer--;
				return *this;
			}

			Iterator	operator--(int)
			{
				Iterator tmp = *this;
				--(*this);
				return tmp;
			}

			Iterator	&operator+=(std::size_t n)
			{
				_pointer += n;
				return *this;
			}

			Iterator	&operator-=(std::size_t n)
			{
				_pointer -= n;
				return *this;
			}

			Iterator	operator+(std::size_t n) const
			{
				return (_pointer + n);
			}

			Iterator	operator-(std::size_t n) const
			{ 
				return (_pointer - n);
			}

			Iterator	&operator[](std::size_t index) const
			{
				return *(*this + index);
			}

			ptrdiff_t	operator-(const Iterator &x)
			{
				return (_pointer - x._pointer);
			}

			bool	operator== (const Iterator &x)
			{
				return (this->base() == x.base());
			}

			bool	operator!=(const Iterator &x)
			{
				return (this->base() != x.base());
			}

			bool	operator<(const Iterator &x)
			{
				return (this->base() < x.base());
			}

			bool	operator<=(const Iterator &x)
			{
				return (this->base() <= x.base());
			}

			bool	operator>(const Iterator &x)
			{
				return (this->base() > x.base());
			}

			bool	operator>=(const Iterator &x)
			{
				return (this->base() >= x.base());
			}
	};

	template <class T>
	class ConstIterator : public iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef T																		value_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::reference		reference;
			typedef typename iterator<std::random_access_iterator_tag, T>::pointer			pointer;
		
		protected:
			pointer	_pointer;
		
		public:
			ConstIterator(void) : _pointer()
			{

			}

			ConstIterator(value_type *ptr) : _pointer(ptr)
			{

			}

			pointer	base(void) const
			{
				return (_pointer);
			}

			reference	operator*(void) const
			{
				return *(_pointer);
			}

			pointer	operator->(void) const
			{
				return &(operator*());
			}
			
			const ConstIterator	&operator++(void)
			{
				_pointer++;
				return (*this);
			}

			const ConstIterator	operator++(int)
			{
				ConstIterator tmp = *this;
				++(*this);
				return (tmp);
			}

			const ConstIterator	&operator--(void)
			{
				_pointer--;
				return (*this);
			}

			const ConstIterator	operator--(int)
			{
				ConstIterator tmp = *this;
				--(*this);
				return (tmp);
			}
			
			const ConstIterator	&operator+=(std::size_t n)
			{
				_pointer += n;
				return (*this);
			}

			const ConstIterator	&operator-=(std::size_t n)
			{
				_pointer -= n;
				return (*this);
			}

			const ConstIterator	operator+(std::size_t n)
			{
				return (_pointer + n);
			}

			const ConstIterator	operator-(std::size_t n)
			{
				return (_pointer - n);
			}

			const ConstIterator	&operator[](std::size_t n)
			{
				return *(*this + n);
			}

			ptrdiff_t	operator-(const ConstIterator &x)
			{
				return (_pointer - x._pointer);
			}

			bool	operator==(const ConstIterator &x)
			{
				return (this->base() == x.base());
			}

			bool	operator!=(const ConstIterator &x)
			{
				return (this->base() != x.base());
			}

			bool	operator<(const ConstIterator &x)
			{
				return (this->base() < x.base());
			}

			bool		operator<=(const ConstIterator &x)
			{
				return (this->base() <= x.base());
			}

			bool		operator>(const ConstIterator &x)
			{
				return (this->base() > x.base());
			}

			bool		operator>=(const ConstIterator &x)
			{
				return (this->base() >= x.base());
			}
	};

	template <class Iter>
	class ReverseIterator
	{
		protected:
			Iter											_base;
			typedef iterator_traits<Iter>					iter_traits;

		public:
			typedef Iter									value_type;
			typedef typename iter_traits::difference_type	difference_type;
			typedef typename iter_traits::reference			reference;
			typedef typename iter_traits::pointer			pointer;
			typedef std::size_t								size_type;

			ReverseIterator(void) : _base(Iter())
			{

			}

			ReverseIterator(const value_type &it) : _base(it)
			{

			}

			template <class T>
			ReverseIterator(const ReverseIterator<T> &other): _base(other.base())
			{

			}

			reference	operator*(void)
			{
				return *(_base);
			}

			pointer	operator->(void) const
			{
				return (&(operator*()));
			}

			value_type	base(void) const
			{
				return (_base);
			}

			ReverseIterator	&operator++(void)
			{
				_base--;
				return (*this);
			}

			ReverseIterator	operator++(int)
			{
				ReverseIterator tmp = *this;
				--(*this);
				return (tmp);
			}

			ReverseIterator	&operator--(void)
			{
				_base++;
				return (*this);
			}

			ReverseIterator	operator--(int)
			{
				ReverseIterator tmp = *this;
				++(*this);
				return (tmp);
			}

			ReverseIterator	&operator+=(std::size_t n)
			{
				_base += n;
				return (*this);
			}

			ReverseIterator	&operator-=(std::size_t n)
			{
				_base -= n;
				return (*this);
			}

			ReverseIterator	operator+(std::size_t n)
			{
				return (_base + n);
			}

			ReverseIterator	operator-(std::size_t n)
			{
				return (_base - n);
			}

			ReverseIterator	&operator[](std::size_t n)
			{
				return *(*this + n);
			}

			ptrdiff_t		operator-(const ReverseIterator &x)
			{
				return (_base - x._base);
			}
	};

	template <class Iter1, class Iter2>
	bool operator== (const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator!= (const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator< (const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator<= (const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator> (const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator>= (const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
	{
		return lhs.base() >= rhs.base();
	}
}

#endif