/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:27 by albaur            #+#    #+#             */
/*   Updated: 2022/09/15 18:33:46 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConversion.hpp"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string			input(argv[1]);
		ScalarConversion	Converter;
		
		Converter.analyseInput(input);
		Converter.printInput();
	}
	else
		std::cout << "Error : Invalid input. Only one argument is accepted." << std::endl;
}