/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:51:49 by albaur            #+#    #+#             */
/*   Updated: 2022/08/02 17:05:33 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie*	zombieHorde(int N, std::string name)
{
	if (N < 1)
		return (NULL);
	Zombie	*horde = new Zombie[N];
	for (int i = 0; i < N; i++)
		horde[i].applyName(name);
	return (horde);
}