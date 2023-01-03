/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:12:23 by albaur            #+#    #+#             */
/*   Updated: 2023/01/03 14:51:13 by albaur           ###   ########.fr       */
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

void	test_ft_vector(void)
{
	ft::vector<int>		vector1;
	ft::vector<int>		vector2;

	for (size_t i = 0; i <= 10; i++)
		vector2.push_back(i);
	for (size_t i = 0; i < MAX_ITER; i++)
		vector1.push_back(rand() % MAX_ITER);
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	std::cout << "Begin = " << *(vector1.begin()) << std::endl;
	std::cout << "End = " << *(vector1.end()) << std::endl;
	std::cout << "ReverseBegin = " << *(vector1.rbegin()) << std::endl;
	std::cout << "ReverseEnd = " << *(vector1.rend()) << std::endl;
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
	vector1.assign(vector2.begin(), vector2.end());
	std::cout << "Assigning vector 0 to 10 = ";
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	std::cout << "Operator [0] = " << vector1[0] << std::endl;
	std::cout << "At(0) = " << vector1.at(0) << std::endl;
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
	vector1.insert(vector1.begin() + 1, vector2.begin(), vector2.end());
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
}

void	test_std_vector(void)
{
	std::vector<int>		vector1;
	std::vector<int>		vector2;

	for (size_t i = 0; i <= 10; i++)
		vector2.push_back(i);
	for (size_t i = 0; i < MAX_ITER; i++)
		vector1.push_back(rand() % MAX_ITER);
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	std::cout << "Begin = " << *(vector1.begin()) << std::endl;
	std::cout << "End = " << *(vector1.end()) << std::endl;
	std::cout << "ReverseBegin = " << *(vector1.rbegin()) << std::endl;
	std::cout << "ReverseEnd = " << *(vector1.rend()) << std::endl;
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
	vector1.assign(vector2.begin(), vector2.end());
	std::cout << "Assigning vector 0 to 10 = ";
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
	std::cout << "Operator [0] = " << vector1[0] << std::endl;
	std::cout << "At(0) = " << vector1.at(0) << std::endl;
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
	vector1.insert(vector1.begin() + 1, vector2.begin(), vector2.end());
	for (size_t i = 0; i < vector1.size(); i++)
		std::cout << vector1[i] << " ";
	std::cout << std::endl;
}

int	main(int argc, char **argv)
{
	if (argc != 3 || std::to_string(atoi(argv[2])).length() > 1 || !(argv[2][0] >= '0' && argv[2][0] <= '9') || (atoi(argv[2]) != 0 && atoi(argv[2]) != 1))
	{
		std::cerr << "Usage: ./test seed mode" << std::endl;
		std::cerr << "Mode : Use 0 to test ft containers and 1 for the std lib." << std::endl;
		return (1);
	}
	const int	seed = atoi(argv[1]);
	srand(seed);
	std::cout << "Current seed : " << seed << std::endl;
	if (atoi(argv[2]) == false)
	{
		std::cout << "Testing : ft::vector" << std::endl << std::endl;
		test_ft_vector();
	}
	else
	{
		std::cout << "Testing : std::vector" << std::endl << std::endl;
		test_std_vector();
	}
	return (0);
}
