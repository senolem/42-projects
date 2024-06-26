/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:12:22 by albaur            #+#    #+#             */
/*   Updated: 2022/09/21 18:50:24 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FragTrap_HPP
# define FragTrap_HPP

# include <iostream>
# include "ClapTrap.hpp"

#define MAX_HP 10
#define DEFAULT_FRAG_CODENAME "FR4G-0000"
#define HIGH_FIVE_COST 2

class FragTrap : public ClapTrap
{
	public:
	FragTrap(void);
	FragTrap(FragTrap const &src);
	~FragTrap(void);
	FragTrap &operator=(FragTrap const &src);
	FragTrap(std::string Name);

	void	highFivesGuys(void);
};

#endif
