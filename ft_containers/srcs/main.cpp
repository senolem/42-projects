/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:12:23 by albaur            #+#    #+#             */
/*   Updated: 2023/01/26 00:21:49 by albaur           ###   ########.fr       */
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

void	test_vector(t_data *data)
{	
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |       VECTOR       |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	std::cout << "constructor	: ft";
	open_file(data, "logs/ft.vector.log");
	set_time(data, 0);
	test_ft_vector_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.vector.log");
	set_time(data, 0);
	test_std_vector_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.vector.log", "logs/std.vector.log");

	// element access
	std::cout << "element_access	: ft";
	open_file(data, "logs/ft.element_access.log");
	set_time(data, 0);
	test_ft_vector_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.element_access.log");
	set_time(data, 0);
	test_std_vector_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.element_access.log", "logs/std.element_access.log");

	// iterators
	std::cout << "iterators	: ft";
	open_file(data, "logs/ft.iterators.log");
	set_time(data, 0);
	test_ft_vector_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.iterators.log");
	set_time(data, 0);
	test_std_vector_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.iterators.log", "logs/std.iterators.log");

	// capacity
	std::cout << "capacity	: ft";
	open_file(data, "logs/ft.capacity.log");
	set_time(data, 0);
	test_ft_vector_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.capacity.log");
	set_time(data, 0);
	test_std_vector_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.capacity.log", "logs/std.capacity.log");

	// modifiers
	std::cout << "modifiers	: ft";
	open_file(data, "logs/ft.modifiers.log");
	set_time(data, 0);
	test_ft_vector_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.modifiers.log");
	set_time(data, 0);
	test_std_vector_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.modifiers.log", "logs/std.modifiers.log");
}

int	main(void)
{
	t_data	*data = new t_data;

	test_vector(data);
	delete data;
}
