/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:40:09 by albaur            #+#    #+#             */
/*   Updated: 2022/11/24 16:33:18 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "stack_class.hpp"

namespace ft
{
	template<class T, class Container>
	stack<T, Container>::stack(const container_type &ctnr) : c(ctnr)
	{

	}

	template<class T, class Container>
	stack<T, Container>::~stack(void)
	{

	}

	template<class T, class Container>
	bool	stack<T, Container>::empty(void) const
	{
		return (c.empty());
	}

	template<class T, class Container>
	typename stack<T, Container>::size_type	stack<T, Container>::size(void) const
	{
		return (c.size());
	}

	template<class T, class Container>
	typename stack<T, Container>::value_type	&stack<T, Container>::top(void)
	{
		return (c.back());
	}

	template<class T, class Container>
	const typename stack<T, Container>::value_type	&stack<T, Container>::top(void) const
	{
		return (c.back());
	}

	template<class T, class Container>
	void	stack<T, Container>::push(const value_type &val)
	{
		return (c.push_back(val));
	}

	template<class T, class Container>
	void	stack<T, Container>::pop(void)
	{
		return (c.pop_back());
	}

	template<class T, class Container>
	bool	operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs == rhs);
	}

	template<class T, class Container>
	bool	operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs != rhs);
	}

	template<class T, class Container>
	bool	operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs < rhs);
	}

	template<class T, class Container>
	bool	operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs <= rhs);
	}

	template<class T, class Container>
	bool	operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs > rhs);
	}
	
	template<class T, class Container>
	bool	operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs >= rhs);
	}
}

#endif