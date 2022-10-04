/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:07:10 by albaur            #+#    #+#             */
/*   Updated: 2022/10/04 17:16:57 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>
# include <iostream>
# include <list>

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
			this->c = src.c;
		return (*this);
	}
	
	typedef typename std::stack<T>::container_type::iterator	iterator;

	iterator begin(void)
	{
		return (this->c.begin());
	}
	iterator end(void)
	{
		return (this->c.end());
	}
};

#endif