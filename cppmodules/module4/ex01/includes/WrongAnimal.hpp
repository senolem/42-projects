/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:43:44 by albaur            #+#    #+#             */
/*   Updated: 2022/09/23 14:57:18 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal
{
	protected:
	std::string	type;

	public:
	WrongAnimal(void);
	WrongAnimal(WrongAnimal const &src);
	virtual ~WrongAnimal(void);
	WrongAnimal &operator=(WrongAnimal const &src);
	WrongAnimal(std::string type);
	
	void	makeSound(void) const;
	std::string	getType(void) const;
};

#endif
