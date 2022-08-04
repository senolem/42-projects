/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:51:49 by albaur            #+#    #+#             */
/*   Updated: 2022/08/04 12:25:31 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB
{
	private:
	std::string	name;
	Weapon		*weapon_;

	public:
	HumanB(std::string newname);

	void	setWeapon(Weapon &weapon);
	void	attack(void);
};

#endif