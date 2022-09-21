/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:35:32 by albaur            #+#    #+#             */
/*   Updated: 2022/09/21 18:42:01 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : Name(DEFAULT_CLAP_CODENAME)
{
	std::cout << "ClapTrap initialized without codename, using default one: (" << DEFAULT_CLAP_CODENAME << ")." << std::endl;
	std::cout << "ClapTrap codename \'" << this->Name << "\' booting up..." << std::endl;
	this->HitPoints = 10;
	this->EnergyPoints = 10;
	this->AttackDamage = 0;
}

ClapTrap::ClapTrap(ClapTrap const &src)
{
	std::cout << "Cloning process of ClapTrap codename \'" << src.Name << "\' started!" << std::endl;
	*this = src;
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "Shutting down..." << std::endl;
}

ClapTrap &ClapTrap::operator=(ClapTrap const &src)
{
	std::cout << "Cloning in progress..." << std::endl;
	this->Name = src.Name;
	this->HitPoints = src.HitPoints;
	this->EnergyPoints = src.EnergyPoints;
	this->AttackDamage = src.AttackDamage;
	return (*this);
}

ClapTrap::ClapTrap(std::string Name) : Name(Name)
{
	std::cout << "ClapTrap codename \'" << this->Name << "\' booting up..." << std::endl;
	this->HitPoints = 10;
	this->EnergyPoints = 10;
	this->AttackDamage = 0;
}

ClapTrap::ClapTrap(std::string Name, int HitPoints, unsigned int EnergyPoints, unsigned int AttackDamage) : Name(Name), HitPoints(HitPoints), EnergyPoints(EnergyPoints), AttackDamage(AttackDamage)
{
	std::cout << "ClapTrap codename \'" << this->Name << "\' booting up..." << std::endl;
}

void	ClapTrap::attack(const std::string& target)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "ClapTrap " << this->Name << " cannot attack! No more Energy Points left!" << std::endl;
		return ;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "ClapTrap " << this->Name << " cannot attack! He is K.O." << std::endl;
		return ;
	}
	else
	{
		this->EnergyPoints--;
		std::cout << "ClapTrap " << this->Name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage!" << std::endl;
	}
	if (this->AttackDamage <= 2)
		std::cout << "It's not very effective..." << std::endl;
	else if (this->AttackDamage >= 5)
		std::cout << "It's super effective!" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	this->HitPoints -= amount;
	std::cout << "ClapTrap " << this->Name << " took " << amount << " points of damage! Current HitPoints : " << HitPoints << std::endl;
	if (HitPoints <= 0)
		std::cout << "ClapTrap " << this->Name << " is K.O!" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "ClapTrap " << this->Name << " cannot repair himself! No more Energy Points left!" << std::endl;
		return ;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "ClapTrap " << this->Name << " cannot repair himself! He is K.O." << std::endl;
		return ;
	}
	else
	{
		this->EnergyPoints--;
		if (this->HitPoints += amount > MAX_HP)
			this->HitPoints = MAX_HP;
		else
			this->HitPoints += amount;
		std::cout << "ClapTrap " << this->Name << " repaired himself of " << amount << " HitPoints! Current HitPoints : " << HitPoints << std::endl;
	}
}

void	ClapTrap::boostAttack(unsigned int amount)
{
	std::cout << "Supercharging ClapTrap codename \'" << this->Name << "\' of " << amount << " AttackDamage points!" << std::endl;
	this->AttackDamage += amount;
	if (amount <= 2)
		std::cout << "[" << this->Name << "] : \"Like this is gonna help...\"" << std::endl;
	else if (amount <= 5)
		std::cout << "[" << this->Name << "] : \"Okay, this might help a little bit...\"" << std::endl;
	else
		std::cout << "[" << this->Name << "] : \"*cracks his robotic fingers* How about this?!\"" << std::endl;
}
