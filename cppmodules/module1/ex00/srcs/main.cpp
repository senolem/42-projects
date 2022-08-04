/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:18:27 by albaur            #+#    #+#             */
/*   Updated: 2022/08/02 16:50:01 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie	*braineater;

	randomChump("Isaac");
	braineater = newZombie("Magdalene");
	braineater->announce();
	delete braineater;
	randomChump("Keeper");
}
