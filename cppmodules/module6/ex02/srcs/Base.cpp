/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:50:41 by albaur            #+#    #+#             */
/*   Updated: 2022/09/19 16:28:15 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base	*generate(void)
{
	Base							*ptr;
	default_random_engine			generator;
	uniform_int_distribution<int>	distribution(1, 3);
	int								RNG = distribution(generator);

	switch(RNG)
	{
		case 1:
			ptr = new A;
		case 2:
			ptr = new B;
		case 3:
			ptr = new C;
	}
	return (ptr);
}

void	identify(Base *p)
{

}
//void	identify(Base &p);