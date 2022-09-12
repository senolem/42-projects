/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:47:23 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 13:24:37 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WrongCat_HPP
# define WrongCat_HPP

# include <iostream>
# include <string>
# include "WrongAnimal.hpp"

class WrongCat: public WrongAnimal
{
	public:
	WrongCat(void);
	WrongCat(WrongCat const &src);
	~WrongCat(void);
	WrongCat &operator=(WrongCat const &src);

	virtual void	makeSound(void) const;
};

#endif
