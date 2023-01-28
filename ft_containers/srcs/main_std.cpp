/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_std.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:31:12 by albaur            #+#    #+#             */
/*   Updated: 2023/01/28 00:53:18 by albaur           ###   ########.fr       */
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
	std::cout << "                    |        MAP         |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	std::cout << "constructor	: std";
	open_file(data, "logs/std.map.constructor.log");
	set_time(data, 0);
	test_std_map_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// element access
	std::cout << "element_access	: std";
	open_file(data, "logs/std.map.element_access.log");
	set_time(data, 0);
	test_std_map_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// iterators
	std::cout << "iterators	: std";
	open_file(data, "logs/std.map.iterators.log");
	set_time(data, 0);
	test_std_map_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// capacity
	std::cout << "capacity	: std";
	open_file(data, "logs/std.map.capacity.log");
	set_time(data, 0);
	test_std_map_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// modifiers
	std::cout << "modifiers	: std";
	open_file(data, "logs/std.map.modifiers.log");
	set_time(data, 0);
	test_std_map_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// lookup
	std::cout << "lookup		: std";
	open_file(data, "logs/std.map.lookup.log");
	set_time(data, 0);
	test_std_map_lookup();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// observers
	std::cout << "observers	: std";
	open_file(data, "logs/std.map.observers.log");
	set_time(data, 0);
	test_std_map_observers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// comparison
	std::cout << "comparison	: std";
	open_file(data, "logs/std.map.comparison.log");
	set_time(data, 0);
	test_std_map_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;
}

void	test_set(t_data *data)
{
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |        SET         |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	std::cout << "constructor	: std";
	open_file(data, "logs/std.set.constructor.log");
	set_time(data, 0);
	test_std_set_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// iterators
	std::cout << "iterators	: std";
	open_file(data, "logs/std.set.iterators.log");
	set_time(data, 0);
	test_std_set_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// capacity
	std::cout << "capacity	: std";
	open_file(data, "logs/std.set.capacity.log");
	set_time(data, 0);
	test_std_set_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// modifiers
	std::cout << "modifiers	: std";
	open_file(data, "logs/std.set.modifiers.log");
	set_time(data, 0);
	test_std_set_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// lookup
	std::cout << "lookup		: std";
	open_file(data, "logs/std.set.lookup.log");
	set_time(data, 0);
	test_std_set_lookup();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// observers
	std::cout << "observers	: std";
	open_file(data, "logs/std.set.observers.log");
	set_time(data, 0);
	test_std_set_observers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// comparison
	std::cout << "comparison	: std";
	open_file(data, "logs/std.set.comparison.log");
	set_time(data, 0);
	test_std_set_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;
}

void	test_stack(t_data *data)
{
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |       STACK        |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	std::cout << "constructor	: std";
	open_file(data, "logs/std.stack.constructor.log");
	set_time(data, 0);
	test_std_stack_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// element access
	std::cout << "element_access	: std";
	open_file(data, "logs/std.stack.element_access.log");
	set_time(data, 0);
	test_std_stack_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// capacity
	std::cout << "capacity	: std";
	open_file(data, "logs/std.stack.capacity.log");
	set_time(data, 0);
	test_std_stack_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// modifiers
	std::cout << "modifiers	: std";
	open_file(data, "logs/std.stack.modifiers.log");
	set_time(data, 0);
	test_std_stack_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// comparison
	std::cout << "comparison	: std";
	open_file(data, "logs/std.stack.comparison.log");
	set_time(data, 0);
	test_std_stack_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;
}

void	test_vector(t_data *data)
{	
	std::cout << "                    ______________________" << std::endl << std::endl;
	std::cout << "                    |       VECTOR       |" << std::endl;
	std::cout << "                    ______________________" << std::endl << std::endl;

	// constructor
	std::cout << "constructor	: std";
	open_file(data, "logs/std.vector.constructor.log");
	set_time(data, 0);
	test_std_vector_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// element access
	std::cout << "element_access	: std";
	open_file(data, "logs/std.vector.element_access.log");
	set_time(data, 0);
	test_std_vector_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// iterators
	std::cout << "iterators	: std";
	open_file(data, "logs/std.vector.iterators.log");
	set_time(data, 0);
	test_std_vector_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// capacity
	std::cout << "capacity	: std";
	open_file(data, "logs/std.vector.capacity.log");
	set_time(data, 0);
	test_std_vector_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// modifiers
	std::cout << "modifiers	: std";
	open_file(data, "logs/std.vector.modifiers.log");
	set_time(data, 0);
	test_std_vector_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// comparison
	std::cout << "comparison	: std";
	open_file(data, "logs/std.vector.comparison.log");
	set_time(data, 0);
	test_std_vector_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;
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