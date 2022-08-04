/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:15:11 by albaur            #+#    #+#             */
/*   Updated: 2022/08/02 17:06:23 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <iostream>

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

class Zombie
{
	private:
	std::string	name;

	public:
	~Zombie(void);

	void	announce(void);
	void	applyName(std::string name);
};

Zombie*	zombieHorde(int N, std::string name);

#endif