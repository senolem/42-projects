/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:33:58 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 15:20:26 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"

int	main(void)
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j;//should not create a leak
	delete i;

	std::cout << std::endl << "additonnal tests :" << std::endl;

	int	index = 0;
	Animal	*animals[10];

	while (index < 10)
	{
		if (index < 5)
			animals[index] = new Dog();
		else if (index >= 5)
			animals[index] = new Cat();
		++index;
	}

	index = 0;
	while (index < 10)
	{
		delete animals[index];
		++index;
	}

	std::cout << std::endl << "additonnal tests :" << std::endl;

	Brain	testbrain1;
	Brain	testbrain2;
	Cat		kitten;
	Dog		doggo;

	testbrain1.setIdea("testestest", 0);
	testbrain2.setIdea("BAOBAB", 99);
	testbrain1.displayIdea(0);
	testbrain2.displayIdea(0);
	testbrain1.displayIdea(99);
	testbrain2.displayIdea(99);
	kitten.setBrain(testbrain1);
	doggo.setBrain(testbrain2);
	kitten.displayBrain();
	doggo.displayBrain();
	return 0;
}
