/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:38:44 by albaur            #+#    #+#             */
/*   Updated: 2022/09/02 13:54:10 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

#define MAX_HP 10
#define DEFAULT_CLAP_CODENAME "CL4P-0000"

class ClapTrap
{
	private:
	std::string		Name;
	int	HitPoints;
	unsigned int	EnergyPoints;
	unsigned int	AttackDamage;

	public:
	ClapTrap(void);
	ClapTrap(ClapTrap const &src);
	~ClapTrap(void);
	ClapTrap &operator=(ClapTrap const &src);
	ClapTrap(std::string Name);

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
	void	boostAttack(unsigned int amount);
};

#endif
