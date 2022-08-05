/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:33:48 by albaur            #+#    #+#             */
/*   Updated: 2022/08/05 16:39:26 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(int argc, char **argv)
{
	Harl	harltwopointoh;

	if (argc != 2)
	{
		std::cout << "Error: invalid arguments." << std::endl;
		std::cout << "usage: <filter> (DEBUG|INFO|WARNING|ERROR)" << std::endl;
		return (1);
	}
	harltwopointoh.complain(argv[1]);
}
