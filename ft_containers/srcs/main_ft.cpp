/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:31:12 by albaur            #+#    #+#             */
/*   Updated: 2023/01/28 02:14:56 by albaur           ###   ########.fr       */
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
	std::cout << std::endl;

	// element access
	std::cout << "element_access	: ft";
	open_file(data, "logs/ft.map.element_access.log");
	set_time(data, 0);
	test_ft_map_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// iterators
	std::cout << "iterators	: ft";
	open_file(data, "logs/ft.map.iterators.log");
	set_time(data, 0);
	test_ft_map_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// capacity
	std::cout << "capacity	: ft";
	open_file(data, "logs/ft.map.capacity.log");
	set_time(data, 0);
	test_ft_map_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// modifiers
	std::cout << "modifiers	: ft";
	open_file(data, "logs/ft.map.modifiers.log");
	set_time(data, 0);
	test_ft_map_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// lookup
	std::cout << "lookup		: ft";
	open_file(data, "logs/ft.map.lookup.log");
	set_time(data, 0);
	test_ft_map_lookup();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// observers
	std::cout << "observers	: ft";
	open_file(data, "logs/ft.map.observers.log");
	set_time(data, 0);
	test_ft_map_observers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// comparison
	std::cout << "comparison	: ft";
	open_file(data, "logs/ft.map.comparison.log");
	set_time(data, 0);
	test_ft_map_comparison();
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
	std::cout << "constructor	: ft";
	open_file(data, "logs/ft.set.constructor.log");
	set_time(data, 0);
	test_ft_set_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// iterators
	std::cout << "iterators	: ft";
	open_file(data, "logs/ft.set.iterators.log");
	set_time(data, 0);
	test_ft_set_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// capacity
	std::cout << "capacity	: ft";
	open_file(data, "logs/ft.set.capacity.log");
	set_time(data, 0);
	test_ft_set_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// modifiers
	std::cout << "modifiers	: ft";
	open_file(data, "logs/ft.set.modifiers.log");
	set_time(data, 0);
	test_ft_set_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// lookup
	std::cout << "lookup		: ft";
	open_file(data, "logs/ft.set.lookup.log");
	set_time(data, 0);
	test_ft_set_lookup();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// observers
	std::cout << "observers	: ft";
	open_file(data, "logs/ft.set.observers.log");
	set_time(data, 0);
	test_ft_set_observers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// comparison
	std::cout << "comparison	: ft";
	open_file(data, "logs/ft.set.comparison.log");
	set_time(data, 0);
	test_ft_set_comparison();
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
	std::cout << "constructor	: ft";
	open_file(data, "logs/ft.stack.constructor.log");
	set_time(data, 0);
	test_ft_stack_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// element access
	std::cout << "element_access	: ft";
	open_file(data, "logs/ft.stack.element_access.log");
	set_time(data, 0);
	test_ft_stack_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// capacity
	std::cout << "capacity	: ft";
	open_file(data, "logs/ft.stack.capacity.log");
	set_time(data, 0);
	test_ft_stack_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// modifiers
	std::cout << "modifiers	: ft";
	open_file(data, "logs/ft.stack.modifiers.log");
	set_time(data, 0);
	test_ft_stack_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// comparison
	std::cout << "comparison	: ft";
	open_file(data, "logs/ft.stack.comparison.log");
	set_time(data, 0);
	test_ft_stack_comparison();
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
	std::cout << "constructor	: ft";
	open_file(data, "logs/ft.vector.constructor.log");
	set_time(data, 0);
	test_ft_vector_constructor();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// element access
	std::cout << "element_access	: ft";
	open_file(data, "logs/ft.vector.element_access.log");
	set_time(data, 0);
	test_ft_vector_element_access();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// iterators
	std::cout << "iterators	: ft";
	open_file(data, "logs/ft.vector.iterators.log");
	set_time(data, 0);
	test_ft_vector_iterators();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// capacity
	std::cout << "capacity	: ft";
	open_file(data, "logs/ft.vector.capacity.log");
	set_time(data, 0);
	test_ft_vector_capacity();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// modifiers
	std::cout << "modifiers	: ft";
	open_file(data, "logs/ft.vector.modifiers.log");
	set_time(data, 0);
	test_ft_vector_modifiers();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;

	// comparison
	std::cout << "comparison	: ft";
	open_file(data, "logs/ft.vector.comparison.log");
	set_time(data, 0);
	test_ft_vector_comparison();
	set_time(data, 1);
	close_file(data);
	print_time(data);
	std::cout << std::endl;
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