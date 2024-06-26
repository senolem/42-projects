/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:05:11 by albaur            #+#    #+#             */
/*   Updated: 2022/09/21 10:37:28 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>
# include <iostream>

class Contact
{
	private:
	std::string			infos[5];

	public:
	static std::string	fields[5];
	enum Field
	{
		FirstName = 0,
		LastName,
		Nickname,
		PhoneNumber,
		DarkestSecret
	};
	std::string	getInfo(size_t i) const;
	void		setInfo(std::string str, size_t i);
};

#endif
