/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:54:08 by albaur            #+#    #+#             */
/*   Updated: 2022/09/23 11:05:28 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Iter.hpp"

class Test
{
	private:
	int			nb;
	std::string	str;

	public:
	Test(void) : nb(123), str("Hola")
	{
		return ;
	}
	int	getNb(void) const
	{
		return (this->nb);
	}
	std::string getStr(void) const
	{
		return (this->str);
	}
};

std::ostream	&operator<<(std::ostream &stream, const Test &src)
{
	return (stream << "NB = " << src.getNb() << " STR = " << src.getStr());
}

template <typename T>
void display(T const &var)
{
	std::cout << var << std::endl;
}

int	main(void)
{
	Test		test[10];
	int			intTab[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::string stringTab[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
	::iter(intTab, 10, display);
	::iter(stringTab, 10, display);
	::iter(test, 10, display);
}