/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:51:40 by albaur            #+#    #+#             */
/*   Updated: 2022/08/01 21:37:50 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <string>
# include <iostream>
# include <iomanip>
# include "Contact.hpp"

class PhoneBook
{
	private:
	size_t	size;
	size_t	oldest;
	Contact	contacts[8];

	public:
	PhoneBook(void);

	void		add(void);
	void		search(void);
	int			getSize(void);
	void		prompt(size_t i, Contact &contact);
	void		printTable(void);
	void		printInfo(size_t i);
	void		printColumn(Contact contact, size_t i);
	std::string	getOutput(std::string &str);
	bool		checkInput(std::string &str);
};

#endif
