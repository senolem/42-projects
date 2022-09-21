/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:12:36 by albaur            #+#    #+#             */
/*   Updated: 2022/09/21 18:53:00 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap(DEFAULT_FRAG_CODENAME)
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

FragTrap::FragTrap(std::string Name) : ClapTrap(Name, 100, 100, 30)
{
	std::cout << "FragTrap codename \'" << this->Name << "\' online ┌(◉ ͜ʖ◉)つ" << std::endl;
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