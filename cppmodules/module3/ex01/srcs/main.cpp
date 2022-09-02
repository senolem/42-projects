/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:35:18 by albaur            #+#    #+#             */
/*   Updated: 2022/09/02 14:23:21 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ScavTrap	Bot0;
	ScavTrap	Bot1("SC4V-0001");
	ScavTrap	Bot2("SC4V-0002");
	ScavTrap	Bot3("SC4V-0003");
	ScavTrap	Bot4 = Bot3;

	Bot0.boostAttack(0);
	Bot1.boostAttack(10);
	Bot2.boostAttack(1);
	Bot3.boostAttack(999999);
	Bot4.boostAttack(3);
	Bot0.attack("His shadow");
	Bot1.attack("Weak oldman");
	Bot2.attack("Teenager");
	Bot3.attack("Innocent woman");
	Bot4.attack("A random salesman passing by");
	Bot0.guardGate();
	Bot1.guardGate();
	Bot4.guardGate();
	Bot0.takeDamage(999999);
	Bot1.takeDamage(1);
	Bot2.takeDamage(9);
	Bot3.takeDamage(10);
	Bot4.takeDamage(100);
	Bot0.attack("His shadow");
	Bot1.attack("Weak oldman");
	Bot2.attack("Teenager");
	Bot3.attack("Innocent woman");
	Bot4.attack("A random salesman passing by");
	Bot0.beRepaired(999999);
	Bot1.beRepaired(1);
	Bot2.beRepaired(5);
	Bot3.beRepaired(10);
	Bot4.beRepaired(100);
	Bot0.takeDamage(999999);
	Bot1.takeDamage(1);
	Bot2.takeDamage(9);
	Bot3.takeDamage(10);
	Bot4.takeDamage(100);
	Bot0.guardGate();
	Bot1.guardGate();
	Bot4.guardGate();
	Bot0.takeDamage(999999);
	Bot1.takeDamage(1);
	Bot2.takeDamage(9);
	Bot3.takeDamage(10);
	Bot4.takeDamage(100);
}