/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:12:38 by albaur            #+#    #+#             */
/*   Updated: 2022/08/05 16:42:04 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	Harl::debug(void)
{
	std::cout << "[DEBUG] Harl error level is set as \"debug\"." << std::endl;
}

void	Harl::info(void)
{
	std::cout << "[INFO] Harl never stops complaining." << std::endl;
}

void	Harl::warning(void)
{
	std::cout << "[WARNING] Harl is getting really mad." << std::endl;
}

void	Harl::error(void)
{
	std::cout << "[ERROR] Harl is mad at you and won't tell you what the error is." << std::endl;
}

int	Harl::filter(std::string level)
{
    std::string fnString[] =
	{
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};
    for (size_t i = 0; i < 4; i++)
	{
        if (level == fnString[i])
			return (i);
	}
	return (-1);
}

void	Harl::complain(std::string level)
{
	switch(Harl::filter(level))
	{
		case 0:
			Harl::debug();
			Harl::info();
			Harl::warning();
			Harl::error();
			break;
		case 1:
			Harl::info();
			Harl::warning();
			Harl::error();
			break;
		case 2:
			Harl::warning();
			Harl::error();
			break;
		case 3:
			Harl::error();
			break;
		default:
			std::cout << "Harl mumbles something, you can't distinguish a single word..." << std::endl;
			break;
		}
}
