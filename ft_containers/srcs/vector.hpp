/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   vector.hpp										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: albaur <albaur@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/11/22 14:44:03 by albaur			#+#	#+#			 */
/*   Updated: 2022/11/29 14:42:45 by albaur		   ###   ########.fr	   */
/*																			*/
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

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::iterator::operator+(difference_type n) const
	{
		return (RandomAccessIterator<T>::operator+(n));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator& vector<T, Alloc>::iterator::operator++(void)
	{
		RandomAccessIterator<T>::operator++();
		return (*this);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::iterator::operator++(int)
	{
		return (RandomAccessIterator<T>::operator++(0));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator& vector<T, Alloc>::iterator::operator--(void)
	{
		RandomAccessIterator<T>::operator--();
		(return *this);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::iterator::operator--(int)
	{
		return (RandomAccessIterator<T>::operator--(0));
	}

	template<class T, class Alloc>
	vector<T, Alloc>::const_iterator::const_iterator() : RandomAccessIterator<T>()
	{

	}

	template<class T, class Alloc>
	vector<T, Alloc>::const_iterator::const_iterator(T *src) : RandomAccessIterator<T>(src)
	{

	}

	// template<class T, class Alloc>
	// vector<T, Alloc>::const_iterator::const_iterator(const RandomAccessIterator<T> &src) : RandomAccessIterator<T>(src)
	// {

	// }

	template<class T, class Alloc>
	vector<T, Alloc>::const_iterator::~const_iterator()
	{

	}

	template <class T, class Alloc> 
	typename vector<T, Alloc>::const_iterator::reference vector<T, Alloc>::const_iterator::operator*() const
	{
		return *(this->_val);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator::pointer vector<T, Alloc>::const_iterator::operator->() const
	{
		return (this->_val);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator::const_reference vector<T, Alloc>::const_iterator::operator[](size_type n) const
	{
		return (this->_val[n]);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator& vector<T, Alloc>::const_iterator::operator+=(difference_type n)
	{
		this->_val += n;
		return (*this);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator& vector<T, Alloc>::const_iterator::operator-=(difference_type n)
	{
		this->_val -= n;
		return (*this);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator::difference_type vector<T, Alloc>::const_iterator::operator-(const RandomAccessIterator<T> &n) const
	{
		return (RandomAccessIterator<T>::operator-(n));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::const_iterator::operator-(difference_type n) const
	{
		return (RandomAccessIterator<T>::operator-(n));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::const_iterator::operator+(difference_type n) const
	{
		return (RandomAccessIterator<T>::operator+(n));
	}
	
	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator& vector<T, Alloc>::const_iterator::operator++(void)
	{
		RandomAccessIterator<T>::operator++();
		return (*this);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::const_iterator::operator++(int)
	{
		return (RandomAccessIterator<T>::operator++(0));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator& vector<T, Alloc>::const_iterator::operator--(void)
	{
		RandomAccessIterator<T>::operator--();
		return (*this);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::const_iterator::operator--(int)
	{
		return (RandomAccessIterator<T>::operator--(0));
	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(const allocator_type &alloc) : _data(NULL), _alloc(alloc), _size(0), _capacity(0), _max_size(0)
	{

	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(size_type n, const value_type &val, const allocator_type &alloc) : _alloc(alloc), _size(n), _capacity(n)
	{
		_data = _alloc.allocate(n);
		for (size_t i = 0; i < n; i++)
			_alloc.construct(&_data[i], val);
	}

	template <class T, class Alloc>
	template <class InputIt>
	vector<T, Alloc>::vector(InputIt first, InputIt last, const allocator_type &alloc) : _alloc(alloc), _size(0), _capacity(0)
	{
		_capacity = ft::InputIt_get_len(first, last);
		_data = _alloc.allocate(_capacity);
		for (size_t i = 0; first != last; i++)
		{
			_alloc.construct(&data[i], *first);
			++_size;
		}
	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(vector const &other) : _data(NULL), _alloc(allocator_type()), _size(other.size()), _capacity(other.capacity())
	{
		_max_size = other.max_size();
		_data = _alloc.allocate(_capacity);
		for (size_t i = 0; i < _size; i++)
			_alloc.construct(&_data[i], other[i]);
	}

	template <class T, class Alloc>
	vector<T, Alloc>
}

#endif
