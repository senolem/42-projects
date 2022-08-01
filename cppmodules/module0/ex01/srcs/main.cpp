/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:12:20 by albaur            #+#    #+#             */
/*   Updated: 2022/08/01 20:15:09 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int	main(void)
{
	std::string	input;
	PhoneBook	phonebook;
	bool		status = true;

	std::cout << "📞 Please enter a valid command (SEARCH, ADD or EXIT)." << std::endl;
	while (status)
	{
		std::cout << "📝 (" << phonebook.getSize() << ") > ";
		getline(std::cin, input);
		if (input == "ADD")
			phonebook.add();
		else if (input == "SEARCH")
			phonebook.search();
		else if (input == "EXIT")
			status = false;
		else if (std::cin.eof())
		{
			std::cout << std::endl;
			status = false;
		}
		else if (input.length() != 0)
			std::cout << "Unknown command. Available commands : SEARCH, ADD, EXIT." << std::endl;
	}
	std::cout << "Exiting..." << std::endl;
}