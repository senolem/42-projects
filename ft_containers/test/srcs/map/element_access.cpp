/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_access.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:51:59 by albaur            #+#    #+#             */
/*   Updated: 2023/01/27 19:50:37 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_map_element_access(void)
{
	ft::map<std::string, std::string>		st;

	st.insert(ft::pair<std::string, std::string>("Work it", "Make it"));
	st.insert(ft::pair<std::string, std::string>("Do it", "Makes us"));
	st.insert(ft::pair<std::string, std::string>("Harder", "Better"));
	st.insert(ft::pair<std::string, std::string>("Faster", "Stronger"));
	ft::map<std::string, std::string>::iterator	pr = st.find("Work it");
	ft::map<std::string, std::string>::iterator	pr2 = st.find("Do it");
	ft::map<std::string, std::string>::iterator	pr3 = st.find("Harder");
	ft::map<std::string, std::string>::iterator	pr4 = st.find("Stronger");
	ft::map<std::string, std::string>::iterator	pr5 = st.find("Make it");
	ft::map<std::string, std::string>::iterator	pr6 = st.find("5555");
	if (pr != st.end())
		std::cout << pr->first << " " << pr->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr2 != st.end())
		std::cout << pr2->first << " " << pr2->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr3 != st.end())
		std::cout << pr3->first << " " << pr3->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr4 != st.end())
		std::cout << pr4->first << " " << pr4->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr5 != st.end())
		std::cout << pr5->first << " " << pr5->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr6 != st.end())
		std::cout << pr6->first << " " << pr6->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
}

void	test_std_map_element_access(void)
{
	std::map<std::string, std::string>		st;

	st.insert(std::pair<std::string, std::string>("Work it", "Make it"));
	st.insert(std::pair<std::string, std::string>("Do it", "Makes us"));
	st.insert(std::pair<std::string, std::string>("Harder", "Better"));
	st.insert(std::pair<std::string, std::string>("Faster", "Stronger"));
	std::map<std::string, std::string>::iterator	pr = st.find("Work it");
	std::map<std::string, std::string>::iterator	pr2 = st.find("Do it");
	std::map<std::string, std::string>::iterator	pr3 = st.find("Harder");
	std::map<std::string, std::string>::iterator	pr4 = st.find("Stronger");
	std::map<std::string, std::string>::iterator	pr5 = st.find("Make it");
	std::map<std::string, std::string>::iterator	pr6 = st.find("5555");
	if (pr != st.end())
		std::cout << pr->first << " " << pr->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr2 != st.end())
		std::cout << pr2->first << " " << pr2->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr3 != st.end())
		std::cout << pr3->first << " " << pr3->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr4 != st.end())
		std::cout << pr4->first << " " << pr4->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr5 != st.end())
		std::cout << pr5->first << " " << pr5->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
	if (pr6 != st.end())
		std::cout << pr6->first << " " << pr6->second << std::endl;
	else
		std::cout << "not found ;(" << std::endl;
}
