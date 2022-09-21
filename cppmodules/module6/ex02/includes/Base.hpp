/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:45:29 by albaur            #+#    #+#             */
/*   Updated: 2022/09/19 16:13:06 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

# include <random>
# include "A.hpp"
# include "B.hpp"
# include "C.hpp"

class Base
{
	public:
	virtual ~Base(void);
};

Base	*generate(void);
void	identify(Base *p);
void	identify(Base &p);

#endif