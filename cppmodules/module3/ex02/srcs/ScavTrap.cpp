/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:38:57 by albaur            #+#    #+#             */
/*   Updated: 2022/09/02 14:47:15 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : Name(DEFAULT_SCAV_CODENAME)
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

ScavTrap::ScavTrap(std::string Name) : Name(Name)
{
	std::cout << "ScavTrap codename \'" << this->Name << "\' activated." << std::endl;
	this->HitPoints = 100;
	this->EnergyPoints = 50;
	this->AttackDamage = 20;
	this->guardGateMode = false;
}

void	ScavTrap::attack(const std::string& target)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot attack, no more Energy Points left. Hibernating." << std::endl;
		return ;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot attack, he is resting." << std::endl;
		return ;
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

void	ScavTrap::takeDamage(unsigned int amount)
{
	if (this->guardGateMode == true)
	{
		std::cout << "guardGate mode actived. Reducing next taken damages by -" << GUARD_GATE_DEFENSE << std::endl;
		if ((int)amount - GUARD_GATE_DEFENSE < 1)
			amount = 0;
		else
			amount -= GUARD_GATE_DEFENSE;
		this->guardGateMode = false;
	}
	this->HitPoints -= amount;
	std::cout << "ScavTrap " << this->Name << " took " << amount << " points of damage. Current HitPoints : " << HitPoints << std::endl;
	if (HitPoints <= 0)
		std::cout << "ScavTrap " << this->Name << " is K.O." << std::endl;
}

void	ScavTrap::beRepaired(unsigned int amount)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot repair himself, no more Energy Points left. Goodbye." << std::endl;
		return ;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot repair himself, he is K.O. Sleep mode activated." << std::endl;
		return ;
	}
	else
	{
		this->EnergyPoints--;
		if (this->HitPoints += amount > MAX_HP)
			this->HitPoints = MAX_HP;
		else
			this->HitPoints += amount;
		std::cout << "ScavTrap " << this->Name << " repaired himself of " << amount << " HitPoints. Current HitPoints : " << HitPoints << std::endl;
	}
}

void	ScavTrap::boostAttack(unsigned int amount)
{
	std::cout << "Supercharging ScavTrap codename \'" << this->Name << "\' of " << amount << " AttackDamage points. Whee." << std::endl;
	this->AttackDamage += amount;
	if (amount <= 2)
		std::cout << "[" << this->Name << "] : \"Come closer.\"" << std::endl;
	else if (amount <= 5)
		std::cout << "[" << this->Name << "] : \"Hold still.\"" << std::endl;
	else
		std::cout << "[" << this->Name << "] : \"Suppressing.\"" << std::endl;
}

void	ScavTrap::guardGate(void)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot use guardGate, no more Energy Points left. Nap time." << std::endl;
		return ;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "ScavTrap " << this->Name << " cannot use guardGate, he is K.O. Goodnight." << std::endl;
		return ;
	}
	else
	{
		if (this->EnergyPoints < GUARD_GATE_COST)
		{
			std::cout << "ScavTrap " << this->Name << " cannot use guardGate, not enough Energy Points left. Resting." << std::endl;
			return ;
		}	
		else
			this->EnergyPoints -= GUARD_GATE_COST;
		std::cout << "ScavTrap codename \'" << this->Name << "\' entered guardGate mode. Searching." << std::endl;
		this->guardGateMode = true;
	}
}
