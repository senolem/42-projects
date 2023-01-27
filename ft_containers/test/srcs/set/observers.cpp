/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:50:52 by albaur            #+#    #+#             */
/*   Updated: 2023/01/27 18:39:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_set_observers(void)
{
	ft::set<int>					st;
	ft::set<int>::iterator 			iter;
	ft::set<int>::iterator 			iter2;
	ft::set<int>::const_iterator 	iter3;
	ft::set<int>::const_iterator	iter4;

	for (size_t i = 0; i < 100; i++)
	{
		if (i % 3 == 0 && i % 5 == 0 && i != 0)
			st.insert(i);
		else if (i % 3 == 0)
			st.insert(15 * i);
		else if (i % 5 == 0)
			st.insert(20 * i);
		else
			st.insert(i);
	}
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << *iter << " vs " << *iter3 << std::endl;
			if (!st.value_comp()(*iter, *iter3))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (!st.key_comp()(*iter, *iter3))
				std::cout << "key equal" << std::endl;
			else
				std::cout << "key not equal" << std::endl;
		}
	}
	st.insert(55);
	st.insert(22);
	st.insert(42);
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << *iter << " vs " << *iter3 << std::endl;
			if (!st.value_comp()(*iter, *iter3))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (!st.key_comp()(*iter, *iter3))
				std::cout << "key equal" << std::endl;
			else
				std::cout << "key not equal" << std::endl;
		}
	}
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << *iter << " vs " << *iter3 << std::endl;
			if (st.value_comp()(*iter, *iter3))
			{
				std::cout << "value not equal! erasing... " << std::endl;
				st.erase(*iter3);
				iter = st.begin();
				iter2 = st.end();
				iter3 = st.begin();
				iter4 = st.end();
			}
		}
	}
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	size_t i = 0;
	for (; iter != iter2; iter++, i++)
		std::cout << *iter << std::endl;
	std::cout << "Nodes remaining : " << i << " (expected 1)" << std::endl;
}

void	test_std_set_observers(void)
{
	std::set<int>					st;
	std::set<int>::iterator 		iter;
	std::set<int>::iterator 		iter2;
	std::set<int>::const_iterator 	iter3;
	std::set<int>::const_iterator	iter4;

	for (size_t i = 0; i < 100; i++)
	{
		if (i % 3 == 0 && i % 5 == 0 && i != 0)
			st.insert(i);
		else if (i % 3 == 0)
			st.insert(15 * i);
		else if (i % 5 == 0)
			st.insert(20 * i);
		else
			st.insert(i);
	}
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << *iter << " vs " << *iter3 << std::endl;
			if (!st.value_comp()(*iter, *iter3))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (!st.key_comp()(*iter, *iter3))
				std::cout << "key equal" << std::endl;
			else
				std::cout << "key not equal" << std::endl;
		}
	}
	st.insert(55);
	st.insert(22);
	st.insert(42);
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << *iter << " vs " << *iter3 << std::endl;
			if (!st.value_comp()(*iter, *iter3))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (!st.key_comp()(*iter, *iter3))
				std::cout << "key equal" << std::endl;
			else
				std::cout << "key not equal" << std::endl;
		}
	}
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << *iter << " vs " << *iter3 << std::endl;
			if (st.value_comp()(*iter, *iter3))
			{
				std::cout << "value not equal! erasing... " << std::endl;
				st.erase(*iter3);
				iter = st.begin();
				iter2 = st.end();
				iter3 = st.begin();
				iter4 = st.end();
			}
		}
	}
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	size_t i = 0;
	for (; iter != iter2; iter++, i++)
		std::cout << *iter << std::endl;
	std::cout << "Nodes remaining : " << i << " (expected 1)" << std::endl;
}