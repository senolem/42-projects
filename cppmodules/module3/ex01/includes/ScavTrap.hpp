/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:38:45 by albaur            #+#    #+#             */
/*   Updated: 2022/09/02 14:29:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include <iostream>

#define MAX_HP 10
#define DEFAULT_SCAV_CODENAME "SC4V-0000"
#define GUARD_GATE_DEFENSE 50
#define GUARD_GATE_COST 100

class ScavTrap
{
	private:
	std::string		Name;
	int	HitPoints;
	unsigned int	EnergyPoints;
	unsigned int	AttackDamage;
	bool			guardGateMode;

	public:
	ScavTrap(void);
	ScavTrap(ScavTrap const &src);
	~ScavTrap(void);
	ScavTrap &operator=(ScavTrap const &src);
	ScavTrap(std::string Name);

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
	void	boostAttack(unsigned int amount);
	void	guardGate(void);
};

#endif