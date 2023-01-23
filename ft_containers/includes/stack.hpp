/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:59 by albaur            #+#    #+#             */
/*   Updated: 2023/01/23 19:00:13 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_CLASS_HPP
# define STACK_CLASS_HPP
# include "vector_class.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;
			typedef typename container_type::size_type			size_type;

		protected:
			container_type	c;

		public:
			explicit			stack(const container_type &ctnr = container_type())  : c(ctnr)
			{

			}

			virtual				~stack(void)
			{

			}
			
			bool				empty(void) const
			{
				return (c.empty());
			}

			size_type			size(void) const
			{
				return (c.size());
			}

			value_type			&top(void)
			{
				return (c.back());
			}

			const value_type	&top(void) const
			{
				return (c.back());
			}

			void				push(const value_type &val)
			{
				return (c.push_back(val));
			}

			void				pop(void)
			{
				return (c.pop_back());
			}
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs == rhs);
	}
	
	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs != rhs);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs < rhs);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs <= rhs);
	}
	
	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs > rhs);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs >= rhs);
	}
}

#endif