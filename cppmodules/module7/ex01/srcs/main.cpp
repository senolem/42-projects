/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:54:08 by albaur            #+#    #+#             */
/*   Updated: 2022/09/21 18:00:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Iter.hpp"

void	rockit(T const &)
{

}

int	main(void)
{
	template<typename T>
	void	rockit(T const &)
	{
		std::cout << T << std::endl;
	}
	
	int intTab[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	::iter(&intTab, 10, rockit);
}