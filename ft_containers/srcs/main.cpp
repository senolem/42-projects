/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:12:23 by albaur            #+#    #+#             */
/*   Updated: 2023/01/28 02:14:07 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/stat.h>
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
	std::cout << "                    |        MAP         |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	std::cout << "constructor	: ft";
	open_file(data, "logs/ft.map.constructor.log");
	set_time(data, 0);
	test_ft_map_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.map.constructor.log");
	set_time(data, 0);
	test_std_map_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.map.constructor.log", "logs/std.map.constructor.log");

	// element access
	std::cout << "element_access	: ft";
	open_file(data, "logs/ft.map.element_access.log");
	set_time(data, 0);
	test_ft_map_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.map.element_access.log");
	set_time(data, 0);
	test_std_map_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.map.element_access.log", "logs/std.map.element_access.log");

	// iterators
	std::cout << "iterators	: ft";
	open_file(data, "logs/ft.map.iterators.log");
	set_time(data, 0);
	test_ft_map_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.map.iterators.log");
	set_time(data, 0);
	test_std_map_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.map.iterators.log", "logs/std.map.iterators.log");

	// capacity
	std::cout << "capacity	: ft";
	open_file(data, "logs/ft.map.capacity.log");
	set_time(data, 0);
	test_ft_map_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.map.capacity.log");
	set_time(data, 0);
	test_std_map_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.map.capacity.log", "logs/std.map.capacity.log");

	// modifiers
	std::cout << "modifiers	: ft";
	open_file(data, "logs/ft.map.modifiers.log");
	set_time(data, 0);
	test_ft_map_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.map.modifiers.log");
	set_time(data, 0);
	test_std_map_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.map.modifiers.log", "logs/std.map.modifiers.log");

	// lookup
	std::cout << "lookup		: ft";
	open_file(data, "logs/ft.map.lookup.log");
	set_time(data, 0);
	test_ft_map_lookup();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.map.lookup.log");
	set_time(data, 0);
	test_std_map_lookup();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.map.lookup.log", "logs/std.map.lookup.log");

	// observers
	std::cout << "observers	: ft";
	open_file(data, "logs/ft.map.observers.log");
	set_time(data, 0);
	test_ft_map_observers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.map.observers.log");
	set_time(data, 0);
	test_std_map_observers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.map.observers.log", "logs/std.map.observers.log");

	// comparison
	std::cout << "comparison	: ft";
	open_file(data, "logs/ft.map.comparison.log");
	set_time(data, 0);
	test_ft_map_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.map.comparison.log");
	set_time(data, 0);
	test_std_map_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.map.comparison.log", "logs/std.map.comparison.log");
}

void	test_set(t_data *data)
{
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |        SET         |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	std::cout << "constructor	: ft";
	open_file(data, "logs/ft.set.constructor.log");
	set_time(data, 0);
	test_ft_set_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.set.constructor.log");
	set_time(data, 0);
	test_std_set_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.set.constructor.log", "logs/std.set.constructor.log");

	// iterators
	std::cout << "iterators	: ft";
	open_file(data, "logs/ft.set.iterators.log");
	set_time(data, 0);
	test_ft_set_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.set.iterators.log");
	set_time(data, 0);
	test_std_set_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.set.iterators.log", "logs/std.set.iterators.log");

	// capacity
	std::cout << "capacity	: ft";
	open_file(data, "logs/ft.set.capacity.log");
	set_time(data, 0);
	test_ft_set_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.set.capacity.log");
	set_time(data, 0);
	test_std_set_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.set.capacity.log", "logs/std.set.capacity.log");

	// modifiers
	std::cout << "modifiers	: ft";
	open_file(data, "logs/ft.set.modifiers.log");
	set_time(data, 0);
	test_ft_set_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.set.modifiers.log");
	set_time(data, 0);
	test_std_set_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.set.modifiers.log", "logs/std.set.modifiers.log");

	// lookup
	std::cout << "lookup		: ft";
	open_file(data, "logs/ft.set.lookup.log");
	set_time(data, 0);
	test_ft_set_lookup();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.set.lookup.log");
	set_time(data, 0);
	test_std_set_lookup();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.set.lookup.log", "logs/std.set.lookup.log");

	// observers
	std::cout << "observers	: ft";
	open_file(data, "logs/ft.set.observers.log");
	set_time(data, 0);
	test_ft_set_observers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.set.observers.log");
	set_time(data, 0);
	test_std_set_observers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.set.observers.log", "logs/std.set.observers.log");

	// comparison
	std::cout << "comparison	: ft";
	open_file(data, "logs/ft.set.comparison.log");
	set_time(data, 0);
	test_ft_set_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.set.comparison.log");
	set_time(data, 0);
	test_std_set_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.set.comparison.log", "logs/std.set.comparison.log");
}

void	test_stack(t_data *data)
{
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |       STACK        |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	std::cout << "constructor	: ft";
	open_file(data, "logs/ft.stack.constructor.log");
	set_time(data, 0);
	test_ft_stack_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.stack.constructor.log");
	set_time(data, 0);
	test_std_stack_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.stack.constructor.log", "logs/std.stack.constructor.log");

	// element access
	std::cout << "element_access	: ft";
	open_file(data, "logs/ft.stack.element_access.log");
	set_time(data, 0);
	test_ft_stack_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.stack.element_access.log");
	set_time(data, 0);
	test_std_stack_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.stack.element_access.log", "logs/std.stack.element_access.log");

	// capacity
	std::cout << "capacity	: ft";
	open_file(data, "logs/ft.stack.capacity.log");
	set_time(data, 0);
	test_ft_stack_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.stack.capacity.log");
	set_time(data, 0);
	test_std_stack_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.stack.capacity.log", "logs/std.stack.capacity.log");

	// modifiers
	std::cout << "modifiers	: ft";
	open_file(data, "logs/ft.stack.modifiers.log");
	set_time(data, 0);
	test_ft_stack_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.stack.modifiers.log");
	set_time(data, 0);
	test_std_stack_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.stack.modifiers.log", "logs/std.stack.modifiers.log");

	// comparison
	std::cout << "comparison	: ft";
	open_file(data, "logs/ft.stack.comparison.log");
	set_time(data, 0);
	test_ft_stack_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.stack.comparison.log");
	set_time(data, 0);
	test_std_stack_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.stack.comparison.log", "logs/std.stack.comparison.log");
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

	// comparison
	std::cout << "comparison	: ft";
	open_file(data, "logs/ft.vector.comparison.log");
	set_time(data, 0);
	test_ft_vector_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | std :";
	open_file(data, "logs/std.vector.comparison.log");
	set_time(data, 0);
	test_std_vector_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << " | Diff : ";
	print_diff("logs/ft.vector.comparison.log", "logs/std.vector.comparison.log");
}

int	main(void)
{
	t_data		*data = new t_data;
	struct stat	st = {.st_mode = 0777};

	if (stat("logs", &st) == -1)
    	mkdir("logs", 0777);
	test_vector(data);
	test_stack(data);
	test_set(data);
	test_map(data);
	delete data;
}
