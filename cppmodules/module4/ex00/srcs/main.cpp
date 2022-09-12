/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:33:58 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 13:19:13 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;
	
	std::cout << std::endl << "additonnal tests :" << std::endl;
	const WrongAnimal* tame = new WrongAnimal();
	const WrongAnimal* wouf = new WrongCat();
	std::cout << wouf->getType() << " " << std::endl;
	wouf->makeSound(); //will output the wrong cat sound!
	tame->makeSound();
	
	delete tame;
	delete wouf;

	return (0);
}
