/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:12:23 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 00:53:41 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <string>
#include <deque>
#include <list>
#include <map>
#include "map.hpp"
#include <stack>
#include "stack.hpp"
#include <vector>
#include "vector.hpp"
#include <set>
#include "set.hpp"
#include "test.hpp"

void	test_map(t_data *data)
{
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |       MAP          |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	(void)data;
}

void	test_set(t_data *data)
{
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |       SET          |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	(void)data;
}

void	test_stack(t_data *data)
{
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |       STACK        |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	(void)data;
}

void	test_vector(t_data *data)
{	
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |       VECTOR       |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	std::cout << "constructor	: ft";
	open_file(data, "logs/ft.vector.constructor.log");
	set_time(data, 0);
	test_ft_vector_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.vector.constructor.log");
	set_time(data, 0);
	test_std_vector_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.vector.constructor.log", "logs/std.vector.constructor.log");

	// element access
	std::cout << "element_access	: ft";
	open_file(data, "logs/ft.vector.element_access.log");
	set_time(data, 0);
	test_ft_vector_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.vector.element_access.log");
	set_time(data, 0);
	test_std_vector_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.vector.element_access.log", "logs/std.vector.element_access.log");

	// iterators
	std::cout << "iterators	: ft";
	open_file(data, "logs/ft.vector.iterators.log");
	set_time(data, 0);
	test_ft_vector_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.vector.iterators.log");
	set_time(data, 0);
	test_std_vector_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.vector.iterators.log", "logs/std.vector.iterators.log");

	// capacity
	std::cout << "capacity	: ft";
	open_file(data, "logs/ft.vector.capacity.log");
	set_time(data, 0);
	test_ft_vector_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.vector.capacity.log");
	set_time(data, 0);
	test_std_vector_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.vector.capacity.log", "logs/std.vector.capacity.log");

	// modifiers
	std::cout << "modifiers	: ft";
	open_file(data, "logs/ft.vector.modifiers.log");
	set_time(data, 0);
	test_ft_vector_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.vector.modifiers.log");
	set_time(data, 0);
	test_std_vector_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.vector.modifiers.log", "logs/std.vector.modifiers.log");
}

int	main(void)
{
	t_data	*data = new t_data;

	test_vector(data);
	test_stack(data);
	test_set(data);
	test_map(data);
	delete data;
}
