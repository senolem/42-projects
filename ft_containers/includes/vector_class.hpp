/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:43:49 by albaur            #+#    #+#             */
/*   Updated: 2022/11/22 16:37:36 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_CLASS_HPP
# define VECTOR_CLASS_HPP

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

			class iterator
			{

			}

			class const_iterator
			{

			}

			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			explicit vector(const allocator_type& alloc = allocator_type());
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector(const vector& x);
			~vector(void);
			vector& operator= (const vector& x);

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
			reference				back(void) const;

			// modifiers
			template <class InputIterator> 
			void					assign(InputIterator first, InputIterator last);
			void					assign(size_type n, const value_type& val);
			void					push_back (const value_type& val);
			void					pop_back(void);
			iterator				insert(iterator position, const value_type& val);
    		void					insert(iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last);
			iterator				erase(iterator position);iterator erase (iterator first, iterator last);
			void					swap(vector& x);
			void					clear(void);

			// allocator
			allocator_type			get_allocator() const;
	};

	// non member function overloads
	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
}

#endif