/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:48:29 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 13:25:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include <string>
# include "Animal.hpp"

class Dog: public Animal
{
	public:
	Dog(void);
	Dog(Dog const &src);
	~Dog(void);
	Dog &operator=(Dog const &src);

	virtual void	makeSound(void) const;
};

#endif
