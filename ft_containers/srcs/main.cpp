/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:12:23 by albaur            #+#    #+#             */
/*   Updated: 2023/01/05 11:31:03 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <stack>
#include "stack.hpp"
#include <vector>
#include "vector.hpp"
#define MAX_ITER 10
#define RESERVE_SIZE 32
#define RESIZE_SIZE 16

void	print_is_empty(bool	isempty, bool expected)
{
	std::cout << "Is empty ? ";
	if (isempty)
		std::cout << "true";
	else
		std::cout << "false";
	if (expected)
		std::cout << " (expected true)" << std::endl;
	else
		std::cout << " (expected false)" << std::endl;
}

void	print_std_vector(std::vector<int> vector)
{
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i] << " ";
	std::cout << std::endl;
}

void	print_ft_vector(ft::vector<int> vector)
{
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i] << " ";
	std::cout << std::endl;
}

void	test_ft_stack(void)
{
	ft::stack<std::string>	stack1;

	print_is_empty(stack1.empty(), true);
	std::cout << "Size = " << stack1.size() << " (expected 0)" << std::endl;
	stack1.push("cahsohtoa");
	std::cout << "Pushing string \"cahsohtoa\" = " << stack1.top() << std::endl;
	stack1.push("i am a banana");
	std::cout << "Pushing string \"i am a banana\" = " << stack1.top() << std::endl;
	std::cout << "Size = " << stack1.size() << " (expected 2)" << std::endl;
	print_is_empty(stack1.empty(), false);
	stack1.pop();
	std::cout << "Popping top element = " << stack1.top() << std::endl;
	print_is_empty(stack1.empty(), false);
	std::cout << "Size = " << stack1.size() << " (expected 1)" << std::endl;
}

void	test_ft_vector(void)
{
	ft::vector<int>		vector1;
	ft::vector<int>		vector2;

	for (size_t i = 0; i <= 10; i++)
		vector2.push_back(i);
	for (size_t i = 0; i < MAX_ITER; i++)
		vector1.push_back(rand() % MAX_ITER);
	print_ft_vector(vector1);
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
	print_is_empty(vector1.empty(), false);
	vector1.resize(0);
	std::cout << "Resized to 0 elements. New size = " << vector1.size() << " (expected 0)" << std::endl;
	print_is_empty(vector1.empty(), true);
	vector1.resize(RESIZE_SIZE * 2);
	std::cout << "Resized to " << RESIZE_SIZE * 2 << " elements. New size = " << vector1.size() << " (expected " << RESIZE_SIZE * 2 << ")" << std::endl;
	vector1.assign(vector2.begin(), vector2.end());
	std::cout << "Assigning vector 0 to 10 = ";
	print_ft_vector(vector1);
	std::cout << "Operator [0] = " << vector1[0] << std::endl;
	std::cout << "Operator [2] = " << vector1[2] << std::endl;
	std::cout << "At(0) = " << vector1.at(0) << std::endl;
	std::cout << "At(3) = " << vector1.at(3) << std::endl;
	std::cout << "Front = " << vector1.front() << std::endl;
	std::cout << "Back = " << vector1.back() << std::endl;
	vector1.assign(5, 9);
	std::cout << "Assigning 5 x 9 = ";
	print_ft_vector(vector1);
	vector1.push_back(5);
	std::cout << "Pushing back 5 = ";
	print_ft_vector(vector1);
	vector1.pop_back();
	std::cout << "Popping back = ";
	print_ft_vector(vector1);
	vector1.insert(vector1.begin(), 3);
	std::cout << "Inserting 3 before begin = ";
	print_ft_vector(vector1);
	std::cout << "Inserting 7 x 4 before end = ";
	vector1.insert(vector1.end(), 7, 4);
	print_ft_vector(vector1);
	std::cout << "Inserting vector 0 to 10 before second element = ";
	vector1.insert(vector1.begin() + 1, vector2.begin(), vector2.end());
	print_ft_vector(vector1);
	std::cout << "Erasing begin = ";
	vector1.erase(vector1.begin());
	print_ft_vector(vector1);
	vector1.erase(vector1.begin(), vector1.begin() + 2);
	std::cout << "Erasing first to third element = ";
	print_ft_vector(vector1);
	vector1.swap(vector2);
	std::cout << "Swapping with vector 0 to 10 = ";
	print_ft_vector(vector1);
	std::cout << "Original vector 0 to 10 is now = ";
	print_ft_vector(vector2);
	vector1.clear();
	std::cout << "Clearing vector = ";
	print_ft_vector(vector1);
}

void	test_std_vector(void)
{
	std::vector<int>		vector1;
	std::vector<int>		vector2;

	for (size_t i = 0; i <= 10; i++)
		vector2.push_back(i);
	for (size_t i = 0; i < MAX_ITER; i++)
		vector1.push_back(rand() % MAX_ITER);
	print_std_vector(vector1);
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
	print_is_empty(vector1.empty(), false);
	vector1.resize(0);
	std::cout << "Resized to 0 elements. New size = " << vector1.size() << " (expected 0)" << std::endl;
	print_is_empty(vector1.empty(), true);
	vector1.resize(RESIZE_SIZE * 2);
	std::cout << "Resized to " << RESIZE_SIZE * 2 << " elements. New size = " << vector1.size() << " (expected " << RESIZE_SIZE * 2 << ")" << std::endl;
	vector1.assign(vector2.begin(), vector2.end());
	std::cout << "Assigning vector 0 to 10 = ";
	print_std_vector(vector1);
	std::cout << "Operator [0] = " << vector1[0] << std::endl;
	std::cout << "Operator [2] = " << vector1[2] << std::endl;
	std::cout << "At(0) = " << vector1.at(0) << std::endl;
	std::cout << "At(3) = " << vector1.at(3) << std::endl;
	std::cout << "Front = " << vector1.front() << std::endl;
	std::cout << "Back = " << vector1.back() << std::endl;
	vector1.assign(5, 9);
	std::cout << "Assigning 5 x 9 = ";
	print_std_vector(vector1);
	vector1.push_back(5);
	std::cout << "Pushing back 5 = ";
	print_std_vector(vector1);
	vector1.pop_back();
	std::cout << "Popping back = ";
	print_std_vector(vector1);
	vector1.insert(vector1.begin(), 3);
	std::cout << "Inserting 3 before begin = ";
	print_std_vector(vector1);
	std::cout << "Inserting 7 x 4 before end = ";
	vector1.insert(vector1.end(), 7, 4);
	print_std_vector(vector1);
	std::cout << "Inserting vector 0 to 10 before second element = ";
	vector1.insert(vector1.begin() + 1, vector2.begin(), vector2.end());
	print_std_vector(vector1);
	std::cout << "Erasing begin = ";
	vector1.erase(vector1.begin());
	print_std_vector(vector1);
	vector1.erase(vector1.begin(), vector1.begin() + 2);
	std::cout << "Erasing first to third element = ";
	print_std_vector(vector1);
	vector1.swap(vector2);
	std::cout << "Swapping with vector 0 to 10 = ";
	print_std_vector(vector1);
	std::cout << "Original vector 0 to 10 is now = ";
	print_std_vector(vector2);
	vector1.clear();
	std::cout << "Clearing vector = ";
	print_std_vector(vector1);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || std::to_string(atoi(argv[2])).length() > 1 || !(argv[2][0] >= '0' && argv[2][0] <= '9') || (atoi(argv[2]) != 0 && atoi(argv[2]) != 1))
	{
		std::cerr << "Usage: ./ft_containers seed mode" << std::endl;
		std::cerr << "Mode : Use 0 to test ft containers and 1 for the stdlib." << std::endl;
		return (1);
	}
	const int	seed = atoi(argv[1]);
	srand(seed);
	std::cout << "Current seed : " << seed << std::endl;
	if (atoi(argv[2]) == false)
	{
		std::cout << "Testing : ft::vector" << std::endl << std::endl;
		test_ft_vector();
		std::cout << "______________________________________________________________________________" << std::endl;
		std::cout << "Testing : ft::stack" << std::endl << std::endl;
		test_ft_stack();
	}
	else
	{
		std::cout << "Testing : std::vector" << std::endl << std::endl;
		test_std_vector();
	}
	return (0);
}
