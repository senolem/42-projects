/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:48:34 by albaur            #+#    #+#             */
/*   Updated: 2022/10/03 10:23:05 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

template<typename T>
void	printContainer(T container)
{
	typename T::iterator iter;
	typename T::iterator tmp;
	for (iter = container.begin(); iter != container.end(); ++iter)
	{
		std::cout << *iter;
		tmp = iter;
		if (++tmp != container.end())
			std::cout << ", ";
	}
	std::cout << std::endl;
}

int	main(void)
{
	std::array<int, 3>		a = {1, 2, 3};
	std::vector<int>		v(10, 999);
	std::deque<int>			d(100, 123);
	std::list<int>			l;
	std::forward_list<int>	f;

	std::cout << "Testing array : " << std::endl;
	printContainer(a);
	easyfind(a, 1);
	easyfind(a, 3);
	easyfind(a, 4);
	std::cout << std::endl;

	std::cout << "Testing vector : " << std::endl;
	printContainer(v);
	std::cout << "Vector size = " << v.size() << std::endl;
	easyfind(v, 999);
	v.push_back(111);
	std::cout << "Vector size = " << v.size() << std::endl;
	easyfind(v, 111);
	easyfind(a, 4);
	std::cout << std::endl;

	std::cout << "Testing deque : " << std::endl;
	printContainer(d);
	easyfind(d, 123);
	easyfind(d, 4);
	std::cout << std::endl;

	std::cout << "Testing list : " << std::endl;
	for (size_t i = 0; i < 10; ++i)
		l.push_back(i * 10);
	printContainer(l);
	easyfind(l, 0);
	easyfind(l, 55);
	easyfind(l, 60);
	easyfind(l, 90);
	std::cout << std::endl;

	std::cout << "Testing forward list : " << std::endl;
	f.assign(l.begin(), l.end());
	f.reverse();
	printContainer(f);
	easyfind(f, 90);
	easyfind(f, 55);
	easyfind(f, 40);
}