/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:12:23 by albaur            #+#    #+#             */
/*   Updated: 2023/01/02 17:09:36 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <map>
#include "stack.hpp"
#include <vector>
#include "vector.hpp"
#define MAX_ITER 10
#define RESERVE_SIZE 32
#define RESIZE_SIZE 16

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		return (1);
	}

	const int	seed = atoi(argv[1]);

	std::cout << "Current seed : " << seed << std::endl;
	ft::vector<std::string>		vector1;
	ft::vector<int>				vector2;
	std::vector<std::string>	vector3;
	std::vector<int>			vector4;

	std::cout << "Testing : ft::vector" << std::endl;
	srand(seed);
	for (size_t i = 0; i < MAX_ITER; i++)
		vector2.push_back(rand() % MAX_ITER);
	ft::vector<int>::iterator iter = vector2.begin();
	for (; iter != vector2.end(); iter++)
		std::cout << *iter << " ";
	std::cout << *iter << std::endl;
	std::cout << "First element = " << *(vector2.begin()) << std::endl;
	std::cout << "Last element = " << *(vector2.end()) << std::endl;
	std::cout << "ReverseFirst element = " << *(vector2.rbegin()) << std::endl;
	std::cout << "ReverseLast element = " << *(vector2.rend()) << std::endl;
	std::cout << "Size = " << vector2.size() << " (expected " << MAX_ITER << ")" << std::endl;
	std::cout << "Max Size = " << vector2.max_size() << std::endl;
	std::cout << "Capacity = " << vector2.capacity() << std::endl;
	vector2.reserve(vector2.capacity() / 2);
	std::cout << "Reserved " << vector2.capacity() / 2 << " elements. New capacity = " << vector2.capacity() << " (expected " << vector2.capacity() << ")" << std::endl;
	vector2.reserve(vector2.capacity());
	std::cout << "Reserved " << vector2.capacity() << " elements. New capacity = " << vector2.capacity() << " (expected " << vector2.capacity() << ")" << std::endl;
	vector2.reserve(RESERVE_SIZE);
	std::cout << "Reserved " << RESERVE_SIZE << " elements. New capacity = " << vector2.capacity() << " (expected " << RESERVE_SIZE << ")" << std::endl;
	vector2.resize(RESIZE_SIZE * 2);
	std::cout << "Resized to " << RESIZE_SIZE * 2 << " elements. New size = " << vector2.size() << " (expected " << RESIZE_SIZE * 2 << ")" << std::endl;
	vector2.resize(RESIZE_SIZE);
	std::cout << "Resized to " << RESIZE_SIZE << " elements. New size = " << vector2.size() << " (expected " << RESIZE_SIZE << ")" << std::endl;
	vector2.resize(RESIZE_SIZE / 2);
	std::cout << "Resized to " << RESIZE_SIZE / 2 << " elements. New size = " << vector2.size() << " (expected " << RESIZE_SIZE / 2 << ")" << std::endl;
	std::cout << "Is empty ? ";
	if (vector2.empty())
		std::cout << "true";
	else
		std::cout << "false";
	std::cout << " (expected false)" << std::endl;
	vector2.resize(0);
	std::cout << "Resized to 0 elements. New size = " << vector2.size() << " (expected 0)" << std::endl;
	std::cout << "Is empty ? ";
	if (vector2.empty())
		std::cout << "true";
	else
		std::cout << "false";
	std::cout << " (expected true)" << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << "Testing : std::vector" << std::endl;
	srand(seed);
	for (size_t i = 0; i < MAX_ITER; i++)
		vector4.push_back(rand() % MAX_ITER);
	std::vector<int>::iterator iter2 = vector4.begin();
	for (; iter2 != vector4.end(); iter2++)
		std::cout << *iter2 << " ";
	std::cout << *iter << std::endl;
	std::cout << "First element = " << *(vector4.begin()) << std::endl;
	std::cout << "Last element = " << *(vector4.end()) << std::endl;
	std::cout << "ReverseFirst element = " << *(vector4.rbegin()) << std::endl;
	std::cout << "ReverseLast element = " << *(vector4.rend()) << std::endl;
	std::cout << "Size = " << vector4.size() << " (expected " << MAX_ITER << ")" << std::endl;
	std::cout << "Max Size = " << vector4.max_size() << std::endl;
	std::cout << "Capacity = " << vector4.capacity() << std::endl;
	vector4.reserve(vector4.capacity() / 2);
	std::cout << "Reserved " << vector4.capacity() / 2 << " elements. New capacity = " << vector4.capacity() << " (expected " << vector4.capacity() << ")" << std::endl;
	vector4.reserve(vector4.capacity());
	std::cout << "Reserved " << vector4.capacity() << " elements. New capacity = " << vector4.capacity() << " (expected " << vector4.capacity() << ")" << std::endl;
	vector4.reserve(RESERVE_SIZE);
	std::cout << "Reserved " << RESERVE_SIZE << " elements. New capacity = " << vector4.capacity() << " (expected " << RESERVE_SIZE << ")" << std::endl;
	vector2.resize(RESIZE_SIZE * 2);
	std::cout << "Resized to " << RESIZE_SIZE * 2 << " elements. New size = " << vector2.size() << " (expected " << RESIZE_SIZE * 2 << ")" << std::endl;
	vector2.resize(RESIZE_SIZE);
	std::cout << "Resized to " << RESIZE_SIZE << " elements. New size = " << vector2.size() << " (expected " << RESIZE_SIZE << ")" << std::endl;
	vector2.resize(RESIZE_SIZE / 2);
	std::cout << "Resized to " << RESIZE_SIZE / 2 << " elements. New size = " << vector2.size() << " (expected " << RESIZE_SIZE / 2 << ")" << std::endl;
	std::cout << "Is empty ? ";
	if (vector4.empty())
		std::cout << "true";
	else
		std::cout << "false";
	std::cout << " (expected false)" << std::endl;
	vector4.resize(0);
	std::cout << "Resized to 0 elements. New size = " << vector4.size() << " (expected 0)" << std::endl;
	std::cout << "Is empty ? ";
	if (vector4.empty())
		std::cout << "true";
	else
		std::cout << "false";
	std::cout << " (expected true)" << std::endl;
	return (0);
}
