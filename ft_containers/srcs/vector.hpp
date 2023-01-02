/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:49:08 by albaur            #+#    #+#             */
/*   Updated: 2023/01/02 11:18:08 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "vector_class.hpp"
# include "utils.hpp"
# include "Exception.hpp"

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
		return (RandomAccessIterator<T>::operator-(n));
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::iterator::operator-(difference_type n) const
	{
		return (RandomAccessIterator<T>::operator-(n));
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
		return (*this);
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

	template<class T, class Alloc>
	vector<T, Alloc>::const_iterator::const_iterator(const RandomAccessIterator<T> &src) : RandomAccessIterator<T>(src)
	{

	}

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
		for (size_type i = 0; i < n; i++)
			_alloc.construct(&_data[i], val);
	}

	template <class T, class Alloc>
	template <class InputIt>
	vector<T, Alloc>::vector(InputIt first, InputIt last, const allocator_type &alloc) : _alloc(alloc), _size(0), _capacity(0)
	{
		_capacity = ft::InputIt_get_len(first, last);
		_data = _alloc.allocate(_capacity);
		for (size_type i = 0; first != last; i++)
		{
			_alloc.construct(&_data[i], *first);
			++_size;
		}
	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(vector const &other) : _data(NULL), _alloc(allocator_type()), _size(other.size()), _capacity(other.capacity())
	{
		_max_size = other.max_size();
		_data = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; i++)
			_alloc.construct(&_data[i], other[i]);
	}

	template <class T, class Alloc>
	vector<T, Alloc>::~vector(void)
	{
		clear();
		_data = NULL;
	}

	template <class T, class Alloc>
	vector<T, Alloc> & vector<T, Alloc>::operator=(const vector &other)
    {
        vector<T, Alloc> tmp;
        if (this != &other)
        {
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			if (other.size() > tmp._capacity)
				tmp._capacity = other.size();
			if (other.capacity() < _capacity)
				tmp._capacity = _capacity;
			tmp._data = _alloc.allocate(tmp._capacity);
			const_iterator first = other.begin();
			const_iterator last = other.end();
			for (size_type i = 0; first != last; ++first)
				tmp._alloc.construct(&tmp._data[i++], *first);
			_data = tmp._data;
			_size = other.size();
			_capacity = tmp._capacity;
		}
		return (*this);
	}

	// iterators

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::begin(void)
	{
		return (iterator(_data));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator	vector<T, Alloc>::begin(void) const
	{
		return (const_iterator(_data));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::end(void)
	{
		return (iterator(_data + _size));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator	vector<T, Alloc>::end(void) const
	{
		return (const_iterator(_data + _size));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator	vector<T, Alloc>::rbegin(void)
	{
		return (reverse_iterator(end()));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rbegin(void) const
	{
		return (const_reverse_iterator(end()));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator	vector<T, Alloc>::rend(void)
	{
		return (reverse_iterator(begin()));
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rend(void) const
	{
		return (const_reverse_iterator(begin()));
	}

	// capacity

	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::size(void) const
	{
		return (_size);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::max_size(void) const
	{
		return (_max_size);
	}

	template <class T, class Alloc>
	void	vector<T, Alloc>::resize(size_type n, value_type val)
	{
		if (n < size())
		{
			while (n != _size)
				_alloc.destroy(&_data[_size--]);
		}
		else
		{
			if (n <= _capacity * 2)
				reserve(_capacity * 2);
			else
				reserve(n);
			while (_size < n)
			{
				_alloc.construct(&_data[_size], val);
				++_size;
			}
		}
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::capacity(void) const
	{
		return (_capacity);
	}

	template <class T, class Alloc>
	bool	vector<T, Alloc>::empty(void) const
	{
		if (size() > 0)
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	void	vector<T, Alloc>::reserve(size_type n)
	{
		if (n > _capacity)
		{
			T	*tmp;

			_capacity = n;
			tmp = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(&tmp[i], _data[i]);
				_alloc.destroy(&_data[i]);
			}
			_data = tmp;
		}
	}

	// element access

	template <class T, class Alloc>
	typename vector<T, Alloc>::reference	vector<T, Alloc>::operator[](size_type n)
	{
		return (_data[n]);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::operator[](size_type n) const
	{
		return (_data[n]);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::reference	vector<T, Alloc>::at(size_type n)
	{
		if (n >= size())
			throw (Exception("out_of_range"));
		else
			return (_data[n]);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::at(size_type n) const
	{
		if (n >= size())
			throw (Exception("out_of_range"));
		else
			return (_data[n]);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::reference	vector<T, Alloc>::front(void)
	{
		return (_data[0]);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::front(void) const
	{
		return (_data[0]);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::reference	vector<T, Alloc>::back(void)
	{
		return (_data[size() - 1]);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::back(void) const
	{
		return (_data[size() - 1]);
	}

	// modifiers

	template <class T, class Alloc>
	template <class InputIt>
	void	vector<T, Alloc>::assign(InputIt first, InputIt last)
	{
		size_type	len = InputIt_get_len(first, last);

		clear();
		if (len > capacity())
		{
			_alloc.deallocate(_data, _capacity);
			_capacity = len;
			_size = 0;
			_data = _alloc.allocate(len);
		}
		for (; first != last; first++)
			_alloc.construct(&_data[_size++], *first);
	}

	template <class T, class Alloc>
	void	vector<T, Alloc>::assign(size_type n, const value_type &val)
	{
		clear();
		if (n > capacity())
		{
			_alloc.deallocate(_data, _capacity);
			_capacity = n;
			_size = 0;
			_data = _alloc.allocate(n);
		}
		for (size_type i = 0; i < n; i++)
			_alloc.construct(&_data[_size++], val);
	}

	template <class T, class Alloc>
	void	vector<T, Alloc>::push_back(const value_type &val)
	{
		if (_size == _capacity)
			resize(_size + 1, val);
		else
			_alloc.construct(&_data[_size++], val);
	}

	template <class T, class Alloc>
	void	vector<T, Alloc>::pop_back(void)
	{
		_alloc.destroy(&_data[_size--]);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::insert(iterator position, const value_type &val)
	{
		difference_type	pos = position - begin();

		insert(position, 1, val);
		return (iterator(begin() + pos));
	}

	template <class T, class Alloc>
	void	vector<T, Alloc>::insert(iterator position, size_type n, const value_type &val)
	{
		difference_type	pos = position - begin();
		difference_type	pos2 = end() - begin();
		iterator		iter;
		iterator		iter2;

		resize(_size + n);
		iter = begin() + pos2;
		iter2 = end();
		position = begin() + pos;
		while (iter != position)
			*(--iter2) = *(--iter);
		while (n > 0)
		{
			*(position++) = val;
			--n;
		}
	}

	template <class T, class Alloc>
	template <class InputIt>
	void	vector<T, Alloc>::insert(iterator position, InputIt first, InputIt last)
	{
		difference_type	pos2 = end() - begin();
		iterator		iter;
		iterator		iter2;

		resize(_size + InputIt_get_len(first, last));
		iter = begin() + pos2;
		iter2 = end();

		while (iter != position)
			*(--iter2) = *(--iter);
		while (first != last)
			position++ = *(first++);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator position)
	{
		_alloc.destroy(position);
		std::copy(position + 1, end(), position);
		_size--;
		return (position);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator first, iterator last)
	{
		difference_type	diff = last - first;
		for (iterator iter; iter < last; iter++)
			_alloc.destroy(iter);
		std::copy(last, end(), first);
		_size -= diff;
		return (first);
	}

	template <class T, class Alloc>
	void	vector<T, Alloc>::swap(vector &x)
	{
		T*				tmp_data;
		allocator_type	tmp_alloc;
		size_type		tmp_size;
		size_type		tmp_capacity;
		size_type		tmp_max_size;

		tmp_data = x._data;
		tmp_alloc = x._alloc;
		tmp_size = x._size;
		tmp_capacity = x._capacity;
		tmp_max_size = x._max_size;
		x._data = _data;
		x._alloc = _alloc;
		x._size = _size;
		x._capacity = _capacity;
		x._max_size = _max_size;
		_data = tmp_data;
		_alloc = tmp_alloc;
		_size = tmp_size;
		_capacity = tmp_capacity;
		_max_size = tmp_max_size;
	}

	template <class T, class Alloc>
	void	vector<T, Alloc>::clear()
	{
		iterator	iter = begin();
		for (size_type i = 0; i < _capacity; i++)
			_alloc.destroy(&*iter++);
		_size = 0;
	}
}

#endif
