/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:38:57 by albaur            #+#    #+#             */
/*   Updated: 2022/09/21 18:52:49 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap(DEFAULT_SCAV_CODENAME)
{
	std::cout << "Deployed without a codename. Using default one: (" << DEFAULT_SCAV_CODENAME << ")." << std::endl;
	std::cout << "ScavTrap codename \'" << this->Name << "\' activated." << std::endl;
	this->HitPoints = 100;
	this->EnergyPoints = 50;
	this->AttackDamage = 20;
	this->guardGateMode = false;
}

ScavTrap::ScavTrap(ScavTrap const &src)
{
	std::cout << "I don't hate you, ScavTrap codename \'" << src.Name << "\'." << std::endl;
	*this = src;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "Good night..." << std::endl;
}

ScavTrap &ScavTrap::operator=(ScavTrap const &src)
{
	std::cout << "Hey." << std::endl;
	this->Name = src.Name;
	this->HitPoints = src.HitPoints;
	this->EnergyPoints = src.EnergyPoints;
	this->AttackDamage = src.AttackDamage;
	this->guardGateMode = src.guardGateMode;
	return (*this);
}

ScavTrap::ScavTrap(std::string Name) : ClapTrap(Name, 100, 50, 20)
{
	std::cout << "ScavTrap codename \'" << this->Name << "\' activated." << std::endl;
	this->guardGateMode = false;
}

void ScavTrap::attack(const std::string &target)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot attack, no more Energy Points left. Hibernating." << std::endl;
		return;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot attack, he is resting." << std::endl;
		return;
	}
	else
	{
		this->EnergyPoints--;
		std::cout << "ScavTrap " << this->Name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage." << std::endl;
	}
	if (this->AttackDamage <= 2)
		std::cout << "Something's wrong..." << std::endl;
	else if (this->AttackDamage >= 5)
		std::cout << "She probably deserved it." << std::endl;
}

void ScavTrap::guardGate(void)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot use guardGate, no more Energy Points left. Nap time." << std::endl;
		return;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot use guardGate, he is K.O. Goodnight." << std::endl;
		return;
	}
	else
	{
		if (this->EnergyPoints < GUARD_GATE_COST)
		{
			std::cout << "ScavTrap " << this->Name << " cannot use guardGate, not enough Energy Points left. Resting." << std::endl;
			return;
		}
		else
			this->EnergyPoints -= GUARD_GATE_COST;
		std::cout << "ScavTrap codename \'" << this->Name << "\' entered guardGate mode. Searching." << std::endl;
		this->guardGateMode = true;
	}
}
