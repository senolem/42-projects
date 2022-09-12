/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:34:42 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 15:49:52 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal
{
	protected:
	std::string	type;

	public:
	Animal(void);
	Animal(Animal const &src);
	virtual ~Animal(void);
	Animal &operator=(Animal const &src);
	Animal(std::string type);
	
	virtual void	makeSound(void) const = 0;
	std::string	getType(void) const;
};

#endif
