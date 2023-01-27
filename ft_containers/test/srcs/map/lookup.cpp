/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:52:15 by albaur            #+#    #+#             */
/*   Updated: 2023/01/27 23:44:37 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_map_lookup(void)
{
	ft::map<std::string, int>																		st;
	ft::pair<std::string, int>																		pr;
	ft::pair<ft::map<std::string, int>::iterator, bool>												pr2;
	ft::map<std::string, int>::iterator																iter;
	ft::map<std::string, int>::iterator 															iter2;
	ft::map<std::string, int>::iterator 															iter3;
	ft::map<std::string, int>::const_iterator 														iter4;
	ft::map<std::string, int>::const_iterator 														iter5;
	ft::pair<ft::map<std::string, int>::iterator, ft::map<std::string, int>::iterator>				pair;
	ft::pair<ft::map<std::string, int>::const_iterator, ft::map<std::string, int>::const_iterator>	pair2;

	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
		{
			pr2 = st.insert(ft::pair<std::string, int>("A", 1));
			std::cout << pr2.first->first << " " << pr2.first->second << std::endl;
		}
		else
		{
			pr2 = st.insert(ft::pair<std::string, int>("B", 2));
			std::cout << pr2.first->first << " " << pr2.first->second << std::endl;
		}
	}
	std::cout << st.count("A") << std::endl;
	pr = *st.find("A");
	std::cout << pr.first << " " << pr.second << std::endl;
	std::cout << st.count("B") << std::endl;
	pr = *st.find("A");
	std::cout << pr.first << " " << pr.second << std::endl;
	std::cout << st.count("B") << std::endl;
	pr = *st.insert(st.begin(), ft::pair<std::string, int>("C", 3));
	std::cout << pr.first << " " << pr.second << std::endl;
	pr = *st.find("C");
	std::cout << pr.first << " " << pr.second << std::endl;
	std::cout << st.count("C") << std::endl;
	iter = st.find("C");
	std::cout << iter->first << " " << iter->second << std::endl;
	pair = st.equal_range("C");
	pair2 = st.equal_range("C");
	iter2 = pair.first;
	iter3 = pair.second;
	iter4 = pair2.first;
	iter5 = pair2.second;
	for (; iter2 != iter3; iter2++)
		std::cout << iter2->first << " " << iter2->second << std::endl;
	for (; iter4 != iter5; iter4++)
		std::cout << iter4->first << " " << iter4->second << std::endl;
	pair = st.equal_range("A");
	pair2 = st.equal_range("A");
	iter2 = pair.first;
	iter3 = pair.second;
	iter4 = pair2.first;
	iter5 = pair2.second;
	for (; iter2 != iter3; iter2++)
		std::cout << iter2->first << " " << iter2->second << std::endl;
	for (; iter4 != iter5; iter4++)
		std::cout << iter4->first << " " << iter4->second << std::endl;
	iter2 = st.lower_bound("C");
	iter4 = st.lower_bound("C");
	std::cout << iter2->first << " " << iter2->second << std::endl;
	std::cout << iter4->first << " " << iter4->second << std::endl;
	iter2 = st.upper_bound("B");
	iter4 = st.upper_bound("B");
	std::cout << iter2->first << " " << iter2->second << std::endl;
	std::cout << iter4->first << " " << iter4->second << std::endl;
}

void	test_std_map_lookup(void)
{
	std::map<std::string, int>																			st;
	std::pair<std::string, int>																			pr;
	std::pair<std::map<std::string, int>::iterator, bool>												pr2;
	std::map<std::string, int>::iterator																iter;
	std::map<std::string, int>::iterator 																iter2;
	std::map<std::string, int>::iterator 																iter3;
	std::map<std::string, int>::const_iterator 															iter4;
	std::map<std::string, int>::const_iterator 															iter5;
	std::pair<std::map<std::string, int>::iterator, std::map<std::string, int>::iterator>				pair;
	std::pair<std::map<std::string, int>::const_iterator, std::map<std::string, int>::const_iterator>	pair2;

	for (size_t i = 0; i < 500; i++)
	{
		if (i % 2 == 0)
		{
			pr2 = st.insert(std::pair<std::string, int>("A", 1));
			std::cout << pr2.first->first << " " << pr2.first->second << std::endl;
		}
		else
		{
			pr2 = st.insert(std::pair<std::string, int>("B", 2));
			std::cout << pr2.first->first << " " << pr2.first->second << std::endl;
		}
	}
	std::cout << st.count("A") << std::endl;
	pr = *st.find("A");
	std::cout << pr.first << " " << pr.second << std::endl;
	std::cout << st.count("B") << std::endl;
	pr = *st.find("A");
	std::cout << pr.first << " " << pr.second << std::endl;
	std::cout << st.count("B") << std::endl;
	pr = *st.insert(st.begin(), std::pair<std::string, int>("C", 3));
	std::cout << pr.first << " " << pr.second << std::endl;
	pr = *st.find("C");
	std::cout << pr.first << " " << pr.second << std::endl;
	std::cout << st.count("C") << std::endl;
	iter = st.find("C");
	std::cout << iter->first << " " << iter->second << std::endl;
	pair = st.equal_range("C");
	pair2 = st.equal_range("C");
	iter2 = pair.first;
	iter3 = pair.second;
	iter4 = pair2.first;
	iter5 = pair2.second;
	for (; iter2 != iter3; iter2++)
		std::cout << iter2->first << " " << iter2->second << std::endl;
	for (; iter4 != iter5; iter4++)
		std::cout << iter4->first << " " << iter4->second << std::endl;
	pair = st.equal_range("A");
	pair2 = st.equal_range("A");
	iter2 = pair.first;
	iter3 = pair.second;
	iter4 = pair2.first;
	iter5 = pair2.second;
	for (; iter2 != iter3; iter2++)
		std::cout << iter2->first << " " << iter2->second << std::endl;
	for (; iter4 != iter5; iter4++)
		std::cout << iter4->first << " " << iter4->second << std::endl;
	iter2 = st.lower_bound("C");
	iter4 = st.lower_bound("C");
	std::cout << iter2->first << " " << iter2->second << std::endl;
	std::cout << iter4->first << " " << iter4->second << std::endl;
	iter2 = st.upper_bound("B");
	iter4 = st.upper_bound("B");
	std::cout << iter2->first << " " << iter2->second << std::endl;
	std::cout << iter4->first << " " << iter4->second << std::endl;
}
