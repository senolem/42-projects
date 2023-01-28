/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:51:26 by albaur            #+#    #+#             */
/*   Updated: 2023/01/28 12:42:14 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_map_comparison(void)
{
	ft::map<std::string, size_t>	st;
	for (size_t i = 0; i < 42; i++)
	{
		if (i % 3 == 0 && i % 5 == 0)
			st.insert(ft::pair<std::string, size_t>("La purée de carottes c'est pas mal non plus...", 22));
		else if (i % 3 == 0)
			st.insert(ft::pair<std::string, size_t>("Ce projet est long u_u", 33));
		else if (i % 5 == 0)
			st.insert(ft::pair<std::string, size_t>("Mais on apprend des trucs... à défaut de savoir faire un fizzbuzz", 44));
		else
			st.insert(ft::pair<std::string, size_t>("...sulp non lam sap tse'c settorac ed eérup aL", 55));
	}
	ft::map<std::string, size_t>	st2;
	if (st == st2)
		std::cout << "equal" << std::endl;
	if (st != st2)
		std::cout << "not equal" << std::endl;
	if (st < st2)
		std::cout << "lower than" << std::endl;
	if (st <= st2)
		std::cout << "lower or equal than" << std::endl;
	if (st > st2)
		std::cout << "greater than" << std::endl;
	if (st >= st2)
		std::cout << "greater or equal than" << std::endl;
	st2 = st;
	if (st == st2)
		std::cout << "equal" << std::endl;
	if (st != st2)
		std::cout << "not equal" << std::endl;
	if (st < st2)
		std::cout << "lower than" << std::endl;
	if (st <= st2)
		std::cout << "lower or equal than" << std::endl;
	if (st > st2)
		std::cout << "greater than" << std::endl;
	if (st >= st2)
		std::cout << "greater or equal than" << std::endl;
	ft::map<std::string, size_t>	st3(st);
	if (st == st3)
		std::cout << "equal" << std::endl;
	if (st != st3)
		std::cout << "not equal" << std::endl;
	if (st < st3)
		std::cout << "lower than" << std::endl;
	if (st <= st3)
		std::cout << "lower or equal than" << std::endl;
	if (st > st3)
		std::cout << "greater than" << std::endl;
	if (st >= st3)
		std::cout << "greater or equal than" << std::endl;
	st.erase(st.begin());
	if (st == st2)
		std::cout << "equal" << std::endl;
	if (st != st2)
		std::cout << "not equal" << std::endl;
	if (st < st2)
		std::cout << "lower than" << std::endl;
	if (st <= st2)
		std::cout << "lower or equal than" << std::endl;
	if (st > st2)
		std::cout << "greater than" << std::endl;
	if (st >= st2)
		std::cout << "greater or equal than" << std::endl;
	if (st == st3)
		std::cout << "equal" << std::endl;
	if (st != st3)
		std::cout << "not equal" << std::endl;
	if (st < st3)
		std::cout << "lower than" << std::endl;
	if (st <= st3)
		std::cout << "lower or equal than" << std::endl;
	if (st > st3)
		std::cout << "greater than" << std::endl;
	if (st >= st3)
		std::cout << "greater or equal than" << std::endl;
	st.clear();
	st2.clear();
	if (st == st2)
		std::cout << "equal" << std::endl;
	if (st != st2)
		std::cout << "not equal" << std::endl;
	if (st < st2)
		std::cout << "lower than" << std::endl;
	if (st <= st2)
		std::cout << "lower or equal than" << std::endl;
	if (st > st2)
		std::cout << "greater than" << std::endl;
	if (st >= st2)
		std::cout << "greater or equal than" << std::endl;
}

void	test_std_map_comparison(void)
{
	std::map<std::string, size_t>	st;
	for (size_t i = 0; i < 42; i++)
	{
		if (i % 3 == 0 && i % 5 == 0)
			st.insert(std::pair<std::string, size_t>("La purée de carottes c'est pas mal non plus...", 22));
		else if (i % 3 == 0)
			st.insert(std::pair<std::string, size_t>("Ce projet est long u_u", 33));
		else if (i % 5 == 0)
			st.insert(std::pair<std::string, size_t>("Mais on apprend des trucs... à défaut de savoir faire un fizzbuzz", 44));
		else
			st.insert(std::pair<std::string, size_t>("...sulp non lam sap tse'c settorac ed eérup aL", 55));
	}
	std::map<std::string, size_t>	st2;
	if (st == st2)
		std::cout << "equal" << std::endl;
	if (st != st2)
		std::cout << "not equal" << std::endl;
	if (st < st2)
		std::cout << "lower than" << std::endl;
	if (st <= st2)
		std::cout << "lower or equal than" << std::endl;
	if (st > st2)
		std::cout << "greater than" << std::endl;
	if (st >= st2)
		std::cout << "greater or equal than" << std::endl;
	st2 = st;
	if (st == st2)
		std::cout << "equal" << std::endl;
	if (st != st2)
		std::cout << "not equal" << std::endl;
	if (st < st2)
		std::cout << "lower than" << std::endl;
	if (st <= st2)
		std::cout << "lower or equal than" << std::endl;
	if (st > st2)
		std::cout << "greater than" << std::endl;
	if (st >= st2)
		std::cout << "greater or equal than" << std::endl;
	std::map<std::string, size_t>	st3(st);
	if (st == st3)
		std::cout << "equal" << std::endl;
	if (st != st3)
		std::cout << "not equal" << std::endl;
	if (st < st3)
		std::cout << "lower than" << std::endl;
	if (st <= st3)
		std::cout << "lower or equal than" << std::endl;
	if (st > st3)
		std::cout << "greater than" << std::endl;
	if (st >= st3)
		std::cout << "greater or equal than" << std::endl;
	st.erase(st.begin());
	if (st == st2)
		std::cout << "equal" << std::endl;
	if (st != st2)
		std::cout << "not equal" << std::endl;
	if (st < st2)
		std::cout << "lower than" << std::endl;
	if (st <= st2)
		std::cout << "lower or equal than" << std::endl;
	if (st > st2)
		std::cout << "greater than" << std::endl;
	if (st >= st2)
		std::cout << "greater or equal than" << std::endl;
	if (st == st3)
		std::cout << "equal" << std::endl;
	if (st != st3)
		std::cout << "not equal" << std::endl;
	if (st < st3)
		std::cout << "lower than" << std::endl;
	if (st <= st3)
		std::cout << "lower or equal than" << std::endl;
	if (st > st3)
		std::cout << "greater than" << std::endl;
	if (st >= st3)
		std::cout << "greater or equal than" << std::endl;
	st.clear();
	st2.clear();
	if (st == st2)
		std::cout << "equal" << std::endl;
	if (st != st2)
		std::cout << "not equal" << std::endl;
	if (st < st2)
		std::cout << "lower than" << std::endl;
	if (st <= st2)
		std::cout << "lower or equal than" << std::endl;
	if (st > st2)
		std::cout << "greater than" << std::endl;
	if (st >= st2)
		std::cout << "greater or equal than" << std::endl;
}
