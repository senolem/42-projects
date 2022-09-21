/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:38:45 by albaur            #+#    #+#             */
/*   Updated: 2022/09/21 18:45:26 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include <iostream>
# include "ClapTrap.hpp"

#define MAX_HP 10
#define DEFAULT_SCAV_CODENAME "SC4V-0000"
#define GUARD_GATE_DEFENSE 50
#define GUARD_GATE_COST 100

class ScavTrap : public ClapTrap
{
	private:
	bool			guardGateMode;

	public:
	ScavTrap(void);
	ScavTrap(ScavTrap const &src);
	~ScavTrap(void);
	ScavTrap &operator=(ScavTrap const &src);
	ScavTrap(std::string Name);

	void	attack(const std::string& target);
	void	guardGate(void);
};

#endif