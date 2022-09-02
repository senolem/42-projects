/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:12:22 by albaur            #+#    #+#             */
/*   Updated: 2022/09/02 15:43:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FragTrap_HPP
# define FragTrap_HPP

# include <iostream>

#define MAX_HP 10
#define DEFAULT_FRAG_CODENAME "FR4G-0000"
#define HIGH_FIVE_COST 2

class FragTrap
{
	private:
	std::string		Name;
	int				HitPoints;
	unsigned int	EnergyPoints;
	unsigned int	AttackDamage;

	public:
	FragTrap(void);
	FragTrap(FragTrap const &src);
	~FragTrap(void);
	FragTrap &operator=(FragTrap const &src);
	FragTrap(std::string Name);

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
	void	boostAttack(unsigned int amount);
	void	highFivesGuys(void);
};

#endif
