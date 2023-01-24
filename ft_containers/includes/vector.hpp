/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:43:49 by albaur            #+#    #+#             */
/*   Updated: 2023/01/24 16:47:56 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include "vector.hpp"
# include "vector_iterator.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef size_t										size_type;
			typedef ptrdiff_t									difference_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef iter<value_type>							iterator;
			typedef iter<const value_type>						const_iterator;
			typedef reverse_iter<iterator>						reverse_iterator;
			typedef reverse_iter<const_iterator>				const_reverse_iterator;

		private:
				T				*_data;
        		allocator_type	_alloc;
				size_type		_size;
				size_type		_capacity;
				size_type		_max_size;

		public:
			explicit vector(const allocator_type &alloc = allocator_type()) : _data(NULL), _alloc(alloc), _size(0), _capacity(0), _max_size(0)
			{

			}

			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
			{
				_data = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
				_alloc.construct(&_data[i], val);
			}

			template <class InputIt>
			vector(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last, const allocator_type &alloc = allocator_type())  : _alloc(alloc), _size(0), _capacity(0)
			{
				_capacity = ft::InputIt_get_len(first, last);
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _capacity; i++)
				{
					_alloc.construct(&_data[i], *first++);
					++_size;
				}
			}

			vector(const vector &other) : _data(NULL), _alloc(allocator_type()), _size(other.size()), _capacity(other.capacity())
			{
				_max_size = other.max_size();
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_data[i], other[i]);
			}

			~vector(void)
			{
				clear();
				_data = NULL;
			}
			
			vector& operator=(const vector &other)
			{
				vector<T, Allocator> tmp;
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
			iterator				begin(void)
			{
				return (iterator(_data));
			}

			const_iterator			begin(void) const
			{
				return (const_iterator(_data));
			}

			iterator				end(void)
			{
				return (iterator(_data + _size));
			}

			const_iterator			end(void) const
			{
				return (const_iterator(_data + _size));
			}

			reverse_iterator		rbegin(void)
			{
				return (reverse_iterator(&_data[_size]));
			}

			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(&_data[_size]));
			}

			reverse_iterator		rend(void)
			{
				return (reverse_iterator(_data));
			}

			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(_data));
			}

			// capacity
			size_type				size(void) const
			{
				return (_size);
			}

			size_type				max_size(void) const
			{
				return (_alloc.max_size());
			}

			void					resize(size_type n, value_type val = value_type())
			{
				if (n < size())
				{
					while (n != _size)
						pop_back();
				}
				else
				{
					if (n > _capacity)
					{
						if (_capacity == 0)
							reserve(n);
						else if (n > _capacity * 2)
							reserve(n);
						else
							reserve(_capacity * 2);
					}
					while (n != _size)
					{
						_alloc.construct(&_data[_size], val);
						_size++;
					}
				}
			}

			size_type				capacity(void) const
			{
				return (_capacity);
			}

			bool					empty(void) const
			{
				if (size() > 0)
					return (false);
				return (true);
			}

			void					reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("length_error");
				if (n != 0 && n > _capacity)
				{
					T	*tmp = _alloc.allocate(n);

					_capacity = n;
					for (size_t i = 0; i < _size; i++)
						_alloc.construct(&tmp[i], _data[i]);
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(&_data[i]);
					_alloc.deallocate(_data, _capacity);
					_data = tmp;
				}
			}

			// element access
			reference				operator[](size_type n)
			{
				return (_data[n]);
			}

			const_reference			operator[](size_type n) const
			{
				return (_data[n]);
			}

			reference				at(size_type n)
			{
				if (n >= size())
					throw (std::out_of_range("out_of_range"));
				else
					return (_data[n]);
			}

			const_reference			at(size_type n) const
			{
				if (n >= size())
					throw (std::out_of_range("out_of_range"));
				else
					return (_data[n]);
			}

			reference				front(void)
			{
				return (_data[0]);
			}

			const_reference			front(void) const
			{
				return (_data[0]);
			}

			reference				back(void)
			{
				return (_data[size() - 1]);
			}

			const_reference			back(void) const
			{
				return (_data[size() - 1]);
			}
			
			// modifiers
			template <class InputIt> 
			void					assign(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
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

			void					assign(size_type n, const value_type &val)
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

			void					push_back(const value_type &val)
			{
				if (_size == _capacity)
					resize(_size + 1, val);
				else
					_alloc.construct(&_data[_size++], val);
			}

			void					pop_back(void)
			{
				_alloc.destroy(&_data[--_size]);
			}

			iterator				insert(iterator position, const value_type &val)
			{
				difference_type	pos = position - begin();

				insert(position, 1, val);
				return (iterator(begin() + pos));
			}

    		void					insert(iterator position, size_type n, const value_type &val)
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

			template <class InputIt>
			void					insert(iterator position, InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last)
			{
				difference_type	pos = position - begin();
				difference_type	pos2 = end() - begin();
				iterator		iter;
				iterator		iter2;
		
				resize(_size + InputIt_get_len(first, last));
				iter = begin() + pos2;
				iter2 = end();
				position = begin() + pos;
		
				while (iter != position)
					*(--iter2) = *(--iter);
				while (first != last)
					*position++ = *(first++);
			}

			iterator				erase(iterator position)
			{
				size_type			val = position - begin();

				_size -= 1;
				_alloc.destroy(&_data[val]);
				for (size_type i = val; i < _size; i++)
				{
					_alloc.construct(&_data[i], _data[i + 1]);
					_alloc.destroy(&_data[i + 1]);
				}
				return iterator(&_data[val]);
			}

			iterator				erase(iterator first, iterator last)
			{
				int	toreturn = 0;

				if (InputIt_get_len(first, last) == 0)
					return (last);
				if (last == end())
					toreturn = 1;
				difference_type	diff = last - first;
				for (iterator iter = first; iter < last; iter++)
					_alloc.destroy(&*iter);
				std::copy(last, end(), first);
				_size -= diff;
				if (toreturn)
					return (end());
				else
					return (first);
			}

			void					swap(vector &x)
			{
				ft::swap_elements(_data, x._data);
				ft::swap_elements(_alloc, x._alloc);
				ft::swap_elements(_size, x._size);
				ft::swap_elements(_capacity, x._capacity);
				ft::swap_elements(_max_size, x._max_size);
			}

			void					clear(void)
			{
				iterator	iter = begin();
				for (size_type i = 0; i < _capacity; i++)
					_alloc.destroy(&*iter++);
				_size = 0;
			}

			// allocator
			allocator_type			get_allocator() const
			{
				return (_alloc);
			}
	};

	// non member function overloads
	template <class T, class Alloc>
	bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool	operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif