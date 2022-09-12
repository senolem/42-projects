/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:50:48 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 13:25:17 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include <iostream>
# include <string>
# include "Animal.hpp"

class Cat: public Animal
{
	public:
	Cat(void);
	Cat(Cat const &src);
	~Cat(void);
	Cat &operator=(Cat const &src);

	virtual void	makeSound(void) const;
};

#endif
