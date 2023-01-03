/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:12:23 by albaur            #+#    #+#             */
/*   Updated: 2023/01/03 12:13:16 by albaur           ###   ########.fr       */
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
	ft::vector<int>		vector1;
	std::vector<int>	vector2;
	ft::vector<int>		vector3;
	std::vector<int>	vector4;

	for (size_t i = 0; i <= 10; i++)
		vector3.push_back(i);
	for (size_t i = 0; i <= 10; i++)
		vector4.push_back(i);

	std::cout << "Testing : ft::vector" << std::endl;
	srand(seed);
	for (size_t i = 0; i < MAX_ITER; i++)
		vector1.push_back(rand() % MAX_ITER);
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	std::cout << "First element = " << *(vector1.begin()) << std::endl;
	std::cout << "Last element = " << *(vector1.end()) << std::endl;
	std::cout << "ReverseFirst element = " << *(vector1.rbegin()) << std::endl;
	std::cout << "ReverseLast element = " << *(vector1.rend()) << std::endl;
	std::cout << "Size = " << vector1.size() << " (expected " << MAX_ITER << ")" << std::endl;
	std::cout << "Max Size = " << vector1.max_size() << std::endl;
	std::cout << "Capacity = " << vector1.capacity() << std::endl;
	vector1.reserve(vector1.capacity() / 2);
	std::cout << "Reserved " << vector1.capacity() / 2 << " elements. New capacity = " << vector1.capacity() << " (expected " << vector1.capacity() << ")" << std::endl;
	vector1.reserve(vector1.capacity());
	std::cout << "Reserved " << vector1.capacity() << " elements. New capacity = " << vector1.capacity() << " (expected " << vector1.capacity() << ")" << std::endl;
	vector1.reserve(RESERVE_SIZE);
	std::cout << "Reserved " << RESERVE_SIZE << " elements. New capacity = " << vector1.capacity() << " (expected " << RESERVE_SIZE << ")" << std::endl;
	vector1.resize(RESIZE_SIZE);
	std::cout << "Resized to " << RESIZE_SIZE << " elements. New size = " << vector1.size() << " (expected " << RESIZE_SIZE << ")" << std::endl;
	vector1.resize(RESIZE_SIZE / 2);
	std::cout << "Resized to " << RESIZE_SIZE / 2 << " elements. New size = " << vector1.size() << " (expected " << RESIZE_SIZE / 2 << ")" << std::endl;
	std::cout << "Is empty ? ";
	if (vector1.empty())
		std::cout << "true";
	else
		std::cout << "false";
	std::cout << " (expected false)" << std::endl;
	vector1.resize(0);
	std::cout << "Resized to 0 elements. New size = " << vector1.size() << " (expected 0)" << std::endl;
	std::cout << "Is empty ? ";
	if (vector1.empty())
		std::cout << "true";
	else
		std::cout << "false";
	std::cout << " (expected true)" << std::endl;
	vector1.resize(RESIZE_SIZE * 2);
	std::cout << "Resized to " << RESIZE_SIZE * 2 << " elements. New size = " << vector1.size() << " (expected " << RESIZE_SIZE * 2 << ")" << std::endl;
	vector1.assign(vector3.begin(), vector3.end());
	std::cout << "Assigning vector 0 to 10 = ";
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	std::cout << "Operator [0] = " << vector1[0] << std::endl;
	std::cout << "At[0] = " << vector1.at(0) << std::endl;
	std::cout << "Front = " << vector1.front() << std::endl;
	std::cout << "Back = " << vector1.back() << std::endl;
	vector1.assign((ft::vector<int>::size_type)5, 9);
	std::cout << "Assigning 5 x 9 = ";
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	vector1.push_back(5);
	std::cout << "Pushing back 5 = ";
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	vector1.pop_back();
	std::cout << "Popping back = ";
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	vector1.insert(vector1.begin(), 3);
	std::cout << "Inserting 3 before begin = ";
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	std::cout << "Inserting 7 x 4 before end = ";
	vector1.insert(vector1.end(), 7, 4);
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	std::cout << "Inserting vector 0 to 10 before second element = ";
	vector1.insert(vector1.begin() + 1, vector3.begin(), vector3.end());
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;

	std::cout << "________________________________________________________________________________" << std::endl;

	std::cout << "Testing : std::vector" << std::endl;
	srand(seed);
	for (size_t i = 0; i < MAX_ITER; i++)
		vector2.push_back(rand() % MAX_ITER);
	for (size_t i = 0; i < vector2.size(); i++)
		std::cout << vector2[i] << " ";
	std::cout << std::endl;
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
	vector2.resize(RESIZE_SIZE * 2);
	std::cout << "Resized to " << RESIZE_SIZE * 2 << " elements. New size = " << vector2.size() << " (expected " << RESIZE_SIZE * 2 << ")" << std::endl;
	vector2.assign(vector4.begin(), vector4.end());
	std::cout << "Assigning vector 0 to 10 = ";
	for (size_t i = 0; i < vector2.size(); i++)
		std::cout << vector2[i] << " ";
	std::cout << std::endl;
	std::cout << "Operator [0] = " << vector2[0] << std::endl;
	std::cout << "At[0] = " << vector2.at(0) << std::endl;
	std::cout << "Front = " << vector2.front() << std::endl;
	std::cout << "Back = " << vector2.back() << std::endl;
	vector2.assign((ft::vector<int>::size_type)5, 9);
	std::cout << "Assigning 5 x 9 = ";
	for (size_t i = 0; i < vector2.size(); i++)
		std::cout << vector2[i] << " ";
	std::cout << std::endl;
	vector2.push_back(5);
	std::cout << "Pushing back 5 = ";
	for (size_t i = 0; i < vector2.size(); i++)
		std::cout << vector2[i] << " ";
	std::cout << std::endl;
	vector2.pop_back();
	std::cout << "Popping back = ";
	for (size_t i = 0; i < vector2.size(); i++)
		std::cout << vector2[i] << " ";
	std::cout << std::endl;
	vector2.insert(vector2.begin(), 3);
	std::cout << "Inserting 3 before begin = ";
	for (size_t i = 0; i < vector2.size(); i++)
		std::cout << vector2[i] << " ";
	std::cout << std::endl;
	std::cout << "Inserting 7 x 4 before end = ";
	vector2.insert(vector2.end(), 7, 4);
	for (size_t i = 0; i < vector2.size(); i++)
		std::cout << vector2[i] << " ";
	std::cout << std::endl;
	std::cout << "Inserting vector 0 to 10 before second element = ";
	vector2.insert(vector2.begin() + 1, vector4.begin(), vector4.end());
	for (size_t i = 0; i < vector2.size(); i++)
		std::cout << vector2[i] << " ";
	std::cout << std::endl;
	return (0);
}
