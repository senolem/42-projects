/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:12:38 by albaur            #+#    #+#             */
/*   Updated: 2022/08/05 16:45:01 by albaur           ###   ########.fr       */
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

void	Harl::complain(std::string level)
{
    std::string fnString[] =
	{
		"debug",
		"info",
		"warning",
		"error"
	};
    fnPointer fnMap[] =
	{
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};
	
    for (size_t i = 0; i < 4; i++)
	{
        if (level == fnString[i])
			(this->*fnMap[i])();
	}
}
