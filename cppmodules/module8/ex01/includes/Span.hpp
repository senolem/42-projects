/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:24:56 by albaur            #+#    #+#             */
/*   Updated: 2022/10/03 16:54:50 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <vector>
# include <algorithm>
# include <random>
# include "Exception.hpp"

class Span
{
	private:
	unsigned int		N;
	unsigned int		nb;
	std::vector<int>	array;

	public:
	Span(void);
	Span(const Span &src);
	~Span(void);
	Span	&operator=(const Span &src);
	Span(unsigned int sizeN);

	void				addNumber(int newNumber);
	unsigned int		shortestSpan(void);
	unsigned int		longestSpan(void);
	void				displayArray(void);
	void				addNumberRandom(void);
	int					getSize(void);
};

int		getRNG(void);

#endif