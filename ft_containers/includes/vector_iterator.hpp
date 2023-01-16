/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:35:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/16 15:34:16 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP
# include "utils.hpp"

namespace ft
{
	template <class _Category, class _Tp, class _Distance = ptrdiff_t, class _Pointer = _Tp*, class _Reference = _Tp&>
	struct iterator
	{
		typedef _Category	iterator_category;
		typedef _Tp			value_type;
		typedef _Distance	difference_type;
		typedef _Pointer	pointer;
		typedef _Reference	reference;
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
	class VectorIterator : public iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef T																		value_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::reference		reference;
			typedef typename iterator<std::random_access_iterator_tag, T>::pointer			pointer;
		
		protected:
			pointer	_pointer;
		
		public:
			VectorIterator(void) : _pointer()
			{

			}

			VectorIterator(value_type *pointer) : _pointer(pointer)
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

			VectorIterator	&operator++(void)
			{
				_pointer++;
				return *this;
			}

			VectorIterator	operator++(int)
			{
				VectorIterator tmp = *this;
				++(*this);
				return tmp;
			}

			VectorIterator	&operator--(void)
			{
				_pointer--;
				return *this;
			}

			VectorIterator	operator--(int)
			{
				VectorIterator tmp = *this;
				--(*this);
				return tmp;
			}

			VectorIterator	&operator+=(std::size_t n)
			{
				_pointer += n;
				return *this;
			}

			VectorIterator	&operator-=(std::size_t n)
			{
				_pointer -= n;
				return *this;
			}

			VectorIterator	operator+(std::size_t n) const
			{
				return (_pointer + n);
			}

			VectorIterator	operator-(std::size_t n) const
			{ 
				return (_pointer - n);
			}

			VectorIterator	&operator[](std::size_t index) const
			{
				return *(*this + index);
			}

			ptrdiff_t	operator-(const VectorIterator &x)
			{
				return (_pointer - x._pointer);
			}

			bool	operator== (const VectorIterator &x)
			{
				return (this->base() == x.base());
			}

			bool	operator!=(const VectorIterator &x)
			{
				return (this->base() != x.base());
			}

			bool	operator<(const VectorIterator &x)
			{
				return (this->base() < x.base());
			}

			bool	operator<=(const VectorIterator &x)
			{
				return (this->base() <= x.base());
			}

			bool	operator>(const VectorIterator &x)
			{
				return (this->base() > x.base());
			}

			bool	operator>=(const VectorIterator &x)
			{
				return (this->base() >= x.base());
			}
	};

	template <class T>
	class VectorConstIterator : public iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef T																		value_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::reference 		reference;
			typedef typename iterator<std::random_access_iterator_tag, T>::pointer			pointer;
		
		protected:
			pointer	_pointer;
		
		public:
			VectorConstIterator(void) : _pointer()
			{

			}

			VectorConstIterator(value_type *ptr) : _pointer(ptr)
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
			
			const VectorConstIterator	&operator++(void)
			{
				_pointer++;
				return (*this);
			}

			const VectorConstIterator	operator++(int)
			{
				VectorConstIterator tmp = *this;
				++(*this);
				return (tmp);
			}

			const VectorConstIterator	&operator--(void)
			{
				_pointer--;
				return (*this);
			}

			const VectorConstIterator	operator--(int)
			{
				VectorConstIterator tmp = *this;
				--(*this);
				return (tmp);
			}
			
			const VectorConstIterator	&operator+=(std::size_t n)
			{
				_pointer += n;
				return (*this);
			}

			const VectorConstIterator	&operator-=(std::size_t n)
			{
				_pointer -= n;
				return (*this);
			}

			const VectorConstIterator	operator+(std::size_t n)
			{
				return (_pointer + n);
			}

			const VectorConstIterator	operator-(std::size_t n)
			{
				return (_pointer - n);
			}

			const VectorConstIterator	&operator[](std::size_t n)
			{
				return *(*this + n);
			}

			ptrdiff_t	operator-(const VectorConstIterator &x)
			{
				return (_pointer - x._pointer);
			}

			bool	operator==(const VectorConstIterator &x)
			{
				return (this->base() == x.base());
			}

			bool	operator!=(const VectorConstIterator &x)
			{
				return (this->base() != x.base());
			}

			bool	operator<(const VectorConstIterator &x)
			{
				return (this->base() < x.base());
			}

			bool		operator<=(const VectorConstIterator &x)
			{
				return (this->base() <= x.base());
			}

			bool		operator>(const VectorConstIterator &x)
			{
				return (this->base() > x.base());
			}

			bool		operator>=(const VectorConstIterator &x)
			{
				return (this->base() >= x.base());
			}
	};

	template <class Iter>
	class VectorReverseIterator
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

			VectorReverseIterator(void) : _base(Iter())
			{

			}

			VectorReverseIterator(const value_type &it) : _base(it)
			{

			}

			template <class T>
			VectorReverseIterator(const VectorReverseIterator<T> &other): _base(other.base())
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

			VectorReverseIterator	&operator++(void)
			{
				_base--;
				return (*this);
			}

			VectorReverseIterator	operator++(int)
			{
				VectorReverseIterator tmp = *this;
				--(*this);
				return (tmp);
			}

			VectorReverseIterator	&operator--(void)
			{
				_base++;
				return (*this);
			}

			VectorReverseIterator	operator--(int)
			{
				VectorReverseIterator tmp = *this;
				++(*this);
				return (tmp);
			}

			VectorReverseIterator	&operator+=(std::size_t n)
			{
				_base += n;
				return (*this);
			}

			VectorReverseIterator	&operator-=(std::size_t n)
			{
				_base -= n;
				return (*this);
			}

			VectorReverseIterator	operator+(std::size_t n)
			{
				return (_base + n);
			}

			VectorReverseIterator	operator-(std::size_t n)
			{
				return (_base - n);
			}

			VectorReverseIterator	&operator[](std::size_t n)
			{
				return *(*this + n);
			}

			ptrdiff_t		operator-(const VectorReverseIterator &x)
			{
				return (_base - x._base);
			}
	};

	template <class Iter1, class Iter2>
	bool operator== (const VectorReverseIterator<Iter1> &lhs, const VectorReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator!= (const VectorReverseIterator<Iter1> &lhs, const VectorReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator< (const VectorReverseIterator<Iter1> &lhs, const VectorReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator<= (const VectorReverseIterator<Iter1> &lhs, const VectorReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator> (const VectorReverseIterator<Iter1> &lhs, const VectorReverseIterator<Iter2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iter1, class Iter2>
	bool operator>= (const VectorReverseIterator<Iter1> &lhs, const VectorReverseIterator<Iter2> &rhs)
	{
		return lhs.base() >= rhs.base();
	}
}

#endif