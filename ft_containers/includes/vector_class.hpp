/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:43:49 by albaur            #+#    #+#             */
/*   Updated: 2023/01/17 15:28:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_CLASS_HPP
# define VECTOR_CLASS_HPP
# include <memory>
# include "vector_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef size_t											size_type;
			typedef ptrdiff_t										difference_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

			typedef iter<value_type>						iterator;
			typedef iter<const value_type>					const_iterator;
			typedef reverse_iter<iterator>					reverse_iterator;
			typedef reverse_iter<const_iterator>			const_reverse_iterator;

			explicit vector(const allocator_type &alloc = allocator_type());
			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
			template <class InputIt>
			vector(typename ft::enable_if<!std::numeric_limits<InputIt>::is_integer, InputIt>::type first, InputIt last, const allocator_type &alloc = allocator_type());
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
			void					assign(typename ft::enable_if<!std::numeric_limits<InputIt>::is_integer, InputIt>::type first, InputIt last);
			void					assign(size_type n, const value_type &val);
			void					push_back(const value_type &val);
			void					pop_back(void);
			iterator				insert(iterator position, const value_type &val);
    		void					insert(iterator position, size_type n, const value_type &val);
			template <class InputIt>
			void					insert(iterator position, InputIt first, typename ft::enable_if<!std::numeric_limits<InputIt>::is_integer, InputIt>::type last);
			iterator				erase(iterator position);
			iterator				erase(iterator first, iterator last);
			void					swap(vector &x);
			void					clear(void);

			// allocator
			allocator_type			get_allocator() const;

			private:
				T				*_data;
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