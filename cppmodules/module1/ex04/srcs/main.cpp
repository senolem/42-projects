/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:33:48 by albaur            #+#    #+#             */
/*   Updated: 2022/08/04 14:05:45 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Losers.hpp"

int	main(int argc, char **argv)
{
	char			c;
	std::ifstream	file;
	std::string		str;

	if (argc != 4)
	{
		std::cout << "Error: invalid arguments." << std::endl;
		std::cout << "usage: <filename> <string1> <string2>" << std::endl;
		return (1);
	}
	file.open(argv[1], std::ofstream::in | std::ofstream::out);
	if (file.fail())
	{
		std::cout << "Error: " << argv[1] << ": ";
		std::cout << "no suck file or directory" << std::endl;
		return (1);
	}
	while (!file.eof() && file >> std::noskipws >> c)
		str += c;
	file.close();
	return (0);
}