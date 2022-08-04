/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:56:25 by albaur            #+#    #+#             */
/*   Updated: 2022/08/04 12:25:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"

class HumanA
{
	private:
	std::string	name;
	Weapon		&weapon_;

	public:
	HumanA(std::string newname, Weapon &weapon);

	void	setWeapon(Weapon weapon);
	void	attack(void);
};

#endif