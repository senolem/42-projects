/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:52:08 by albaur            #+#    #+#             */
/*   Updated: 2022/08/04 12:12:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string weaponName)
{
	type = weaponName;
}

std::string& Weapon::getType(void)
{
	return (type);
}

void	Weapon::setType(std::string newtype)
{
	type = newtype;
}
