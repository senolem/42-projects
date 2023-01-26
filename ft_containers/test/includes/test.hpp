/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:16:41 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 13:59:09 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# include "vector.hpp"
# include <vector>
# include "stack.hpp"
# include <stack>
# include "map.hpp"
# include <map>
# include "set.hpp"
# include <set>
# include <fstream>
# include <list>

typedef struct s_data
{
	std::fstream									file;
	std::streambuf									*buffer_cout;
	std::streambuf									*buffer_file;
	std::chrono::high_resolution_clock::time_point	now;
	std::chrono::high_resolution_clock::time_point	after;
	std::chrono::duration<double, std::milli>		ms;
}	t_data;

// ft
void	test_ft_vector_constructor(void);
void	test_ft_vector_element_access(void);
void	test_ft_vector_iterators(void);
void	test_ft_vector_capacity(void);
void	test_ft_vector_modifiers(void);
void	test_ft_vector_comparison(void);
void	test_ft_stack_constructor(void);
void	test_ft_stack_element_access(void);
void	test_ft_stack_capacity(void);
void	test_ft_stack_modifiers(void);
void	test_ft_stack_comparison(void);
void	test_ft_set_constructor(void);
void	test_ft_set_iterators(void);
void	test_ft_set_capacity(void);
void	test_ft_set_modifiers(void);
void	test_ft_set_lookup(void);
void	test_ft_set_observers(void);
void	test_ft_set_comparison(void);
void	test_ft_map_constructor(void);
void	test_ft_map_element_access(void);
void	test_ft_map_iterators(void);
void	test_ft_map_capacity(void);
void	test_ft_map_modifiers(void);
void	test_ft_map_lookup(void);
void	test_ft_map_observers(void);
void	test_ft_map_comparison(void);

// std
void	test_std_vector_constructor(void);
void	test_std_vector_element_access(void);
void	test_std_vector_iterators(void);
void	test_std_vector_capacity(void);
void	test_std_vector_modifiers(void);
void	test_std_vector_comparison(void);
void	test_std_stack_constructor(void);
void	test_std_stack_element_access(void);
void	test_std_stack_capacity(void);
void	test_std_stack_modifiers(void);
void	test_std_stack_comparison(void);
void	test_std_set_constructor(void);
void	test_std_set_iterators(void);
void	test_std_set_capacity(void);
void	test_std_set_modifiers(void);
void	test_std_set_lookup(void);
void	test_std_set_observers(void);
void	test_std_set_comparison(void);
void	test_std_map_constructor(void);
void	test_std_map_element_access(void);
void	test_std_map_iterators(void);
void	test_std_map_capacity(void);
void	test_std_map_modifiers(void);
void	test_std_map_lookup(void);
void	test_std_map_observers(void);
void	test_std_map_comparison(void);

// utils
void	print_diff(const std::string &filename1, const std::string &filename2);
bool	compare_files(const std::string &filename1, const std::string &filename2);
void	close_file(t_data *data);
s_data	*open_file(t_data *data, std::string path);
void	set_time(t_data *data, bool mode);
void	print_time(t_data *data);

// print
template <class T>
void	print_ft_vector(ft::vector<T> vect)
{
	typename ft::vector<T>::iterator begin = vect.begin();
	typename ft::vector<T>::iterator end = vect.end();
	for (; begin != end; begin++)
		std::cout << *begin << std::endl;
}

template <class T>
void	print_std_vector(std::vector<T> vect)
{
	typename std::vector<T>::iterator begin = vect.begin();
	typename std::vector<T>::iterator end = vect.end();
	for (; begin != end; begin++)
		std::cout << *begin << std::endl;
}

template <class T, class Container>
void	print_ft_stack(ft::stack<T, Container> stk)
{
	ft::stack<T, Container>	stk2(stk);
	while (stk2.empty() == false)
	{
		std::cout << stk2.top() << std::endl;
		stk2.pop();
	}
}

template <class T, class Container>
void	print_std_stack(std::stack<T, Container> stk)
{
	std::stack<T, Container>	stk2(stk);
	while (stk2.empty() == false)
	{
		std::cout << stk2.top() << std::endl;
		stk2.pop();
	}
}

#endif