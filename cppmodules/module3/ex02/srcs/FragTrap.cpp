/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:12:36 by albaur            #+#    #+#             */
/*   Updated: 2022/09/02 15:49:10 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(void) : Name(DEFAULT_FRAG_CODENAME)
{
	std::cout << "I wasn't given a name! I will use the default one (◔_◔) (" << DEFAULT_FRAG_CODENAME << ")." << std::endl;
	std::cout << "FragTrap codename \'" << this->Name << "\' online ┌(◉ ͜ʖ◉)つ" << std::endl;
	this->HitPoints = 100;
	this->EnergyPoints = 100;
	this->AttackDamage = 30;
}

FragTrap::FragTrap(FragTrap const &src)
{
	std::cout << "Cloning myself \\(°^°)/ ! \'" << src.Name << "\'." << std::endl;
	*this = src;
}

FragTrap::~FragTrap(void)
{
	std::cout << "Goodbye !!! ╰( ͡° ͜ʖ ͡° )つ──☆*:・ﾟ" << std::endl;
}

FragTrap &FragTrap::operator=(FragTrap const &src)
{
	std::cout << "Here's a new FragTrap !! ヽ(•‿•)ノ" << std::endl;
	this->Name = src.Name;
	this->HitPoints = src.HitPoints;
	this->EnergyPoints = src.EnergyPoints;
	this->AttackDamage = src.AttackDamage;
	return (*this);
}

FragTrap::FragTrap(std::string Name) : Name(Name)
{
	std::cout << "FragTrap codename \'" << this->Name << "\' online ┌(◉ ͜ʖ◉)つ" << std::endl;
	this->HitPoints = 100;
	this->EnergyPoints = 100;
	this->AttackDamage = 30;
}

void	FragTrap::attack(const std::string& target)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "FragTrap " << this->Name << " cannot attack, no more Energy Points left (╯°□°）╯︵ ┻━┻" << std::endl;
		return ;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "FragTrap " << this->Name << " cannot attack, he is K.O ヽ(´ー｀)ノ" << std::endl;
		return ;
	}
	else
	{
		this->EnergyPoints--;
		std::cout << "FragTrap " << this->Name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage !!! ಠ‿ಠ" << std::endl;
	}
	if (this->AttackDamage <= 2)
		std::cout << "OMG YOURE SO BAD LMAO" << std::endl;
	else if (this->AttackDamage >= 5)
		std::cout << "GOOD AIM UWU" << std::endl;
}

void	FragTrap::takeDamage(unsigned int amount)
{
	this->HitPoints -= amount;
	std::cout << "FragTrap " << this->Name << " took " << amount << " points of damage ಥ﹏ಥ Current HitPoints : " << HitPoints << std::endl;
	if (HitPoints <= 0)
		std::cout << "FragTrap " << this->Name << " is K.O (⌣̩̩́_⌣̩̩̀)" << std::endl;
}

void	FragTrap::beRepaired(unsigned int amount)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "FragTrap " << this->Name << " cannot repair himself, no more Energy Points left (´Oƪ)" << std::endl;
		return ;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "FragTrap " << this->Name << " cannot repair himself, he is K.O (・_・;)" << std::endl;
		return ;
	}
	else
	{
		this->EnergyPoints--;
		if (this->HitPoints += amount > MAX_HP)
			this->HitPoints = MAX_HP;
		else
			this->HitPoints += amount;
		std::cout << "FragTrap " << this->Name << " repaired himself of " << amount << " HitPoints ( '́з'̀) Current HitPoints : " << HitPoints << std::endl;
	}
}

void	FragTrap::boostAttack(unsigned int amount)
{
	std::cout << "Supercharging FragTrap codename \'" << this->Name << "\' of " << amount << " AttackDamage points ლ(ಠ_ಠლ)" << std::endl;
	this->AttackDamage += amount;
	if (amount <= 2)
		std::cout << "[" << this->Name << "] : \"Uh oh... ಠ_ಠ\"" << std::endl;
	else if (amount <= 5)
		std::cout << "[" << this->Name << "] : \"You're gonna feel this one ( ͡° ͜ʖ ͡°)\"" << std::endl;
	else
		std::cout << "[" << this->Name << "] : \"HYAAAAAAAAAAAAAAAAAAAAAA!!! ୧༼ಠ益ಠ༽୨\"" << std::endl;
}

void	FragTrap::highFivesGuys(void)
{
	if (this->EnergyPoints == 0)
	{
		std::cout << "FragTrap " << this->Name << " cannot ask you for a high five, no more Energy Points left (๑•́ ₃ •̀๑)" << std::endl;
		return ;
	}
	else if (this->HitPoints <= 0)
	{
		std::cout << "FragTrap " << this->Name << " cannot ask you for a high five, he is K.O ಥ﹏ಥ" << std::endl;
		return ;
	}
	else
	{
		if (this->EnergyPoints < HIGH_FIVE_COST)
		{
			std::cout << "FragTrap " << this->Name << " cannot ask you for a high five, not enough Energy Points left (๑•́ ₃ •̀๑)" << std::endl;
			return ;
		}	
		else
			this->EnergyPoints -= HIGH_FIVE_COST;
		std::cout << "[" << this->Name << "] : \"How about a high five, huh?\"" << std::endl;
	}
}