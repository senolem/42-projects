/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:07:10 by albaur            #+#    #+#             */
/*   Updated: 2022/10/03 17:14:33 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
	public:
	MutantStack(void)
	{

	}
	MutantStack(const MutantStack &src)
	{
		*this = src;
	}
	~MutantStack(void)
	{

	}
	MutantStack &operator=(const MutantStack &src)
	{
		if (this != &src)
			c = src.c;
		return (*this);
	}
	typedef typename std::stack<T>::container_type::iterator	iter;
	iter	begin(void)
	{
		return (c.begin());
	}
	iter	end(void)
	{
		return (c.end());
	}
};

#endif