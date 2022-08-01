/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:12:27 by albaur            #+#    #+#             */
/*   Updated: 2022/08/01 20:09:08 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : size() {
	contacts = new Contact[8];
}

int	PhoneBook::getSize(void)
{
	return (this->size);
}

void	PhoneBook::add(void)
{
	Contact	newContact;

	prompt(Contact::FirstName, newContact);
	prompt(Contact::LastName, newContact);
	prompt(Contact::Nickname, newContact);
	prompt(Contact::PhoneNumber, newContact);
	prompt(Contact::DarkestSecret, newContact);
	contacts[size % 8] = newContact;
	++size;
}

void	PhoneBook::prompt(size_t i, Contact &contact)
{
	bool		running = true;
	std::string	input;

	while (running)
	{
		std::cout << Contact::fields[i] << " > ";
		getline(std::cin, input);
		if (checkInput(input))
		{
			contact.infos[i] = input;
			running = false;
		}
		else
			std::cout << "Invalid input! Contact's fields cannot be empty." << std::endl;
	}
}

bool	PhoneBook::checkInput(std::string &input)
{
	for (size_t i = 0; i < input.length(); i++)
	{
		if (std::isalnum(input.c_str()[i]))
			return (true);
	}
	return (false);
}

void	PhoneBook::search(void)
{
	std::string input;
	int			nb;

	if (size == 0)
	{
		std::cout << "Currently, you do not have any contact added." << std::endl;
		return ;
	}
	printTable();
	std::cout << "[Index] > ";
	getline(std::cin, input);
	try
	{
		nb = std::stoi(input);
	}
	catch(...)
	{
		nb = -1;
	}
	if (nb < 0 || nb > 8)
		std::cout << "Invalid input! Index must an unsigned integer smaller than 8." << std::endl;
	else if (nb >= (int)size)
		std::cout << "Contact doesn't exist. Current contacts count : " << size << std::endl;
	else
		printInfo(nb);
}

void	PhoneBook::printTable(void)
{
	std::cout << "|-------------------------------------------|" << std::endl;
	std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
	std::cout << "|-------------------------------------------|" << std::endl;
	for (size_t i = 0; i < size; i++)
		printColumn(contacts[i], i);
	std::cout << std::endl;
	std::cout << "|-------------------------------------------|" << std::endl;
}

void	PhoneBook::printInfo(size_t i)
{
	for (size_t f = 0; f < 5; f++)
		std::cout << Contact::fields[f] << " : " << contacts[i].infos[f] << std::endl;
}

void	PhoneBook::printColumn(Contact contact, size_t i)
{
	std::cout << '|' << std::right << std::setw(10) << i << '|';
	for (size_t j = 0; j < 3; j++)
		std::cout << std::right << std::setw(10) << getOutput(contact.infos[j]) << '|';
}

std::string	PhoneBook::getOutput(std::string &str)
{
	if (str.length() > 10)
		return (str.substr(0, 9).append("."));
	else
		return (str);
}