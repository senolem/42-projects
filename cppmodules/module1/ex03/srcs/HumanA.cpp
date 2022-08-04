/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:52:19 by albaur            #+#    #+#             */
/*   Updated: 2022/08/04 12:31:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string newname, Weapon &weapon): weapon_(weapon)
{
	this->name = newname;
}

void	HumanA::setWeapon(Weapon weapon)
{
	this->weapon_ = weapon;
}

void	HumanA::attack(void)
{
	std::cout << name << " attacks with his " << this->weapon_.getType() << std::endl;
}
