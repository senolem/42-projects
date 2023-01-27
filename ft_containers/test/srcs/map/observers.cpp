/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:52:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/28 00:17:29 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_map_observers(void)
{
	ft::map<int, size_t>					st;
	ft::map<int, size_t>::iterator 			iter;
	ft::map<int, size_t>::iterator 			iter2;
	ft::map<int, size_t>::const_iterator 	iter3;
	ft::map<int, size_t>::const_iterator	iter4;

	for (size_t i = 0; i < 100; i++)
	{
		if (i % 3 == 0 && i % 5 == 0 && i != 0)
			st.insert(ft::pair<int, size_t>(i, i));
		else if (i % 3 == 0)
			st.insert(ft::pair<int, size_t>(15 * i, i * 2));
		else if (i % 5 == 0)
			st.insert(ft::pair<int, size_t>(20 * i, i * 3));
		else
			st.insert(ft::pair<int, size_t>(i, i));
	}
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << iter->first << "," << iter->second << " vs " << iter3->first << "," << iter3->second << std::endl;
			if (!st.value_comp()(*iter, *iter3))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (!st.key_comp()(iter->first, iter3->first))
				std::cout << "key equal" << std::endl;
			else
				std::cout << "key not equal" << std::endl;
		}
	}
	st.insert(ft::pair<int, size_t>(55, 44));
	st.insert(ft::pair<int, size_t>(33, 22));
	st.insert(ft::pair<int, size_t>(42, 84));
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << iter->first << "," << iter->second << " vs " << iter3->first << "," << iter3->second << std::endl;
			if (!st.value_comp()(*iter, *iter3))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (!st.key_comp()(iter->first, iter3->first))
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
			std::cout << "Comparing: " << iter->first << "," << iter->second << " vs " << iter3->first << "," << iter3->second << std::endl;
			if (st.value_comp()(*iter, *iter3))
			{
				std::cout << "value not equal! erasing... " << std::endl;
				st.erase(iter3->first);
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
		std::cout << iter->first << "," << iter->second << std::endl;
	std::cout << "Nodes remaining : " << i << " (expected 1)" << std::endl;
}

void	test_std_map_observers(void)
{
	std::map<int, size_t>					st;
	std::map<int, size_t>::iterator 			iter;
	std::map<int, size_t>::iterator 			iter2;
	std::map<int, size_t>::const_iterator 	iter3;
	std::map<int, size_t>::const_iterator	iter4;

	for (size_t i = 0; i < 100; i++)
	{
		if (i % 3 == 0 && i % 5 == 0 && i != 0)
			st.insert(std::pair<int, size_t>(i, i));
		else if (i % 3 == 0)
			st.insert(std::pair<int, size_t>(15 * i, i * 2));
		else if (i % 5 == 0)
			st.insert(std::pair<int, size_t>(20 * i, i * 3));
		else
			st.insert(std::pair<int, size_t>(i, i));
	}
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << iter->first << "," << iter->second << " vs " << iter3->first << "," << iter3->second << std::endl;
			if (!st.value_comp()(*iter, *iter3))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (!st.key_comp()(iter->first, iter3->first))
				std::cout << "key equal" << std::endl;
			else
				std::cout << "key not equal" << std::endl;
		}
	}
	st.insert(std::pair<int, size_t>(55, 44));
	st.insert(std::pair<int, size_t>(33, 22));
	st.insert(std::pair<int, size_t>(42, 84));
	iter = st.begin();
	iter2 = st.end();
	iter3 = st.begin();
	iter4 = st.end();
	for (; iter != iter2; iter++)
	{
		for (; iter3 != iter4; iter3++)
		{
			std::cout << "Comparing: " << iter->first << "," << iter->second << " vs " << iter3->first << "," << iter3->second << std::endl;
			if (!st.value_comp()(*iter, *iter3))
				std::cout << "value equal" << std::endl;
			else
				std::cout << "value not equal" << std::endl;
			if (!st.key_comp()(iter->first, iter3->first))
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
			std::cout << "Comparing: " << iter->first << "," << iter->second << " vs " << iter3->first << "," << iter3->second << std::endl;
			if (st.value_comp()(*iter, *iter3))
			{
				std::cout << "value not equal! erasing... " << std::endl;
				st.erase(iter3->first);
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
		std::cout << iter->first << "," << iter->second << std::endl;
	std::cout << "Nodes remaining : " << i << " (expected 1)" << std::endl;
}
