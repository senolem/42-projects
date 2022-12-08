/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:43:49 by albaur            #+#    #+#             */
/*   Updated: 2022/12/08 17:00:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_CLASS_HPP
# define VECTOR_CLASS_HPP
# include <memory>
# include "RandomAccessIterator.hpp"
# include "ReverseRandomAccessIterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

			class iterator : public RandomAccessIterator<value_type>
			{
				public:
					typedef value_type			&reference;
					typedef value_type const	&const_reference;
					typedef value_type			*pointer;
					typedef	ptrdiff_t			difference_type;
				
					iterator(void);
					iterator(T *src);
					iterator(iterator const &src);
					virtual ~iterator(void);

					reference		operator*(void) const;
					pointer			operator->(void) const;
					reference		operator[](size_type n) const;
					iterator		&operator+=(difference_type n);
					iterator		&operator-=(difference_type n);
					difference_type	operator-(const RandomAccessIterator<value_type> &n) const;
					iterator		operator-(difference_type n) const;
					iterator		operator+(difference_type n) const;
					friend iterator	operator+(difference_type n, const iterator &rhs)
					{
						return (rhs.operator+(n));
					};
					iterator		&operator++(void);
					iterator		operator++(int);
					iterator		&operator--(void);
					iterator		operator--(int);

				private:
					typedef RandomAccessIterator<T>	type;
					iterator(const RandomAccessIterator<T> &src);
			};

			class const_iterator : public RandomAccessIterator<value_type>
			{
				public:
					typedef value_type const	&reference;
					typedef value_type const	&const_reference;
					typedef value_type const	*pointer;
					typedef	ptrdiff_t const		difference_type;
				
					const_iterator(void);
					const_iterator(T *src);
					const_iterator(const RandomAccessIterator<value_type> &src);
					virtual ~const_iterator(void);

					reference				operator*(void) const;
					pointer					operator->(void) const;
					reference				operator[](size_type n) const;
					const_iterator			&operator+=(difference_type n);
					const_iterator			&operator-=(difference_type n);
					difference_type			operator-(const RandomAccessIterator<value_type> &n) const;
					const_iterator			operator-(difference_type n) const;
					const_iterator			operator+(difference_type n) const;
					friend const_iterator	operator+(difference_type n, const const_iterator &rhs)
					{
						return (rhs.operator+(n));
					}
					const_iterator		&operator++(void);
					const_iterator		operator++(int);
					const_iterator		&operator--(void);
					const_iterator		operator--(int);
			};

			typedef ft::ReverseRandomAccessIterator<iterator>		reverse_iterator;
			typedef ft::ReverseRandomAccessIterator<const_iterator>	const_reverse_iterator;

			explicit vector(const allocator_type &alloc = allocator_type());
			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
			template <class InputIt>
			vector(InputIt first, InputIt last, const allocator_type &alloc = allocator_type());
			vector(const vector &other);
			~vector(void);
			vector& operator=(const vector &other);

			// iterators
			iterator				begin(void);
			const_iterator			begin(void) const;
			iterator				end(void);
			const_iterator			end(void) const;
			reverse_iterator		rbegin(void);
			const_reverse_iterator	rbegin(void) const;
			reverse_iterator		rend(void);
			const_reverse_iterator	rend(void) const;

			// capacity
			size_type				size(void) const;
			size_type				max_size(void) const;
			void					resize(size_type n, value_type val = value_type());
			size_type				capacity(void) const;
			bool					empty(void) const;
			void					reserve(size_type n);

			// element access
			reference				operator[](size_type n);
			const_reference			operator[](size_type n) const;
			reference				at(size_type n);
			const_reference			at(size_type n) const;
			reference				front(void);
			const_reference			front(void) const;
			reference				back(void);
			const_reference			back(void) const;

			// modifiers
			template <class InputIt> 
			void					assign(InputIt first, InputIt last);
			void					assign(size_type n, const value_type &val);
			void					push_back (const value_type &val);
			void					pop_back(void);
			iterator				insert(iterator position, const value_type  &val);
    		void					insert(iterator position, size_type n, const value_type &val);
			template <class InputIt>
			void					insert(iterator position, InputIt first, InputIt last);
			iterator				erase(iterator position);
			iterator				erase(iterator first, iterator last);
			void					swap(vector &x);
			void					clear(void);

			// allocator
			allocator_type			get_allocator() const;

			private:
				T*				_data;
        		allocator_type	_alloc;
				size_type		_size;
				size_type		_capacity;
				size_type		_max_size;
	};

	// non member function overloads
	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc> &y);
	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
}

#endif