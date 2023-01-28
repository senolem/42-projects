/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:49:12 by albaur            #+#    #+#             */
/*   Updated: 2023/01/28 12:42:14 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	test_ft_set_comparison(void)
{
	ft::set<std::string>	st;
	for (size_t i = 0; i < 42; i++)
	{
		if (i % 3 == 0 && i % 5 == 0)
			st.insert("La purée de carottes c'est pas mal non plus...");
		else if (i % 3 == 0)
			st.insert("Ce projet est long u_u");
		else if (i % 5 == 0)
			st.insert("Mais on apprend des trucs... à défaut de savoir faire un fizzbuzz");
		else
			st.insert("...sulp non lam sap tse'c settorac ed eérup aL");
	}
	ft::set<std::string>	st2;
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
	ft::set<std::string>	st3(st);
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

void	test_std_set_comparison(void)
{
	std::set<std::string>	st;
	for (size_t i = 0; i < 42; i++)
	{
		if (i % 3 == 0 && i % 5 == 0)
			st.insert("La purée de carottes c'est pas mal non plus...");
		else if (i % 3 == 0)
			st.insert("Ce projet est long u_u");
		else if (i % 5 == 0)
			st.insert("Mais on apprend des trucs... à défaut de savoir faire un fizzbuzz");
		else
			st.insert("...sulp non lam sap tse'c settorac ed eérup aL");
	}
	std::set<std::string>	st2;
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
	std::set<std::string>	st3(st);
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