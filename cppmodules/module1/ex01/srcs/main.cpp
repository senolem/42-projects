/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:18:27 by albaur            #+#    #+#             */
/*   Updated: 2022/08/02 17:28:24 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iomanip>

int	main(void)
{
	Zombie	*braineater;

	braineater = zombieHorde(10, "braineaters");
	for (int i = 0; i < 10; i++)
	{
		braineater[i].announce();
	}
	braineater[0].applyName("Isaac");
	braineater[1].applyName("Magdalene");
	braineater[2].applyName("Keeper");
	braineater[3].applyName("Jacob");
	braineater[4].applyName("Esaeu");
	braineater[5].applyName("Lilith");
	braineater[6].applyName("The Lost");
	braineater[7].applyName("???");
	braineater[8].applyName("Samson");
	braineater[9].applyName("Bethany");
	for (int i = 0; i < 10; i++)
	{
		braineater[i].announce();
	}
	delete[] braineater;
}
