/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_files.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:39:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/25 21:31:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

template <typename InputIterator1, typename InputIterator2>
bool	range_equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1 && first2 != last2)
	{
	    if (*first1 != *first2)
			return false;
	    ++first1;
	    ++first2;
	}
	return (first1 == last1) && (first2 == last2);
}

bool compare_files(const std::string &filename1, const std::string &filename2)
{
    std::ifstream	file1(filename1);
    std::ifstream	file2(filename2);
    std::istreambuf_iterator<char>	begin1(file1);
    std::istreambuf_iterator<char>	begin2(file2);
    std::istreambuf_iterator<char>	end;

    return (range_equal(begin1, end, begin2, end));
}

void	print_diff(const std::string &filename1, const std::string &filename2)
{
	if (compare_files(filename1, filename2))
		std::cout << "[\033[92mOK\033[0m]" << std::endl;
	else
		std::cout << "[\033[31mKO\033[0m]" << std::endl;
}