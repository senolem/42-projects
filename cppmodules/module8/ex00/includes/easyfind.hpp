/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:47:51 by albaur            #+#    #+#             */
/*   Updated: 2022/10/03 10:16:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>
# include <string>
# include <array>
# include <vector>
# include <deque>
# include <forward_list>
# include <list>
# include <algorithm>
# include "Exception.hpp"

template<typename T>
int	easyfind(T container, int nb)
{
	typename	T::iterator	iter = std::find(container.begin(), container.end(), nb);
	try
	{
		if (iter == container.end())
			throw Exception("easyfind::NotFoundException");
		else
		{
			std::cout << "Value (" << *iter << ") has been found " << std::distance(container.begin(), iter) << " elements away from the beginning." << std::endl;
			return (0);
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (1);
}

#endif
