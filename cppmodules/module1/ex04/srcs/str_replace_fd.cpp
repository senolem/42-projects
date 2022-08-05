/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace_fd.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:52:34 by albaur            #+#    #+#             */
/*   Updated: 2022/08/05 12:05:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Losers.hpp"

int	str_replace_fd(std::string str, char *filename, char *string1, char *string2)
{
	std::ofstream	file;
	std::string		newfile = filename;
	int				pos;

	newfile.append(".replace");
	file.open(newfile);
	if (file.fail())
	{
		std::cout << "Error: " << newfile << ": ";
		std::cout << "cannot create file " << std::endl;
		return (1);
	}
	for (ssize_t i = 0; (size_t)i < str.size(); i++)
	{
		pos = str.find(string1, i);
		if (pos == i && pos > 0)
		{
			file << string2;
			i += std::string(string1).size();
		}
		file << str[i];
	}
	file.close();
	return (0);
}
