/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:48:29 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 15:12:41 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include <string>
# include "Animal.hpp"
# include "Brain.hpp"

class Dog: public Animal
{
	private:
	Brain *ideasbox;
	
	public:
	Dog(void);
	Dog(Dog const &src);
	~Dog(void);
	Dog &operator=(Dog const &src);

	virtual void	makeSound(void) const;
	void	setBrain(Brain const &src);
	Brain	&getBrain(void) const;
	void	displayBrain(void) const;
};

#endif
