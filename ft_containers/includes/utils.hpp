/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:46:06 by albaur            #+#    #+#             */
/*   Updated: 2022/12/08 09:49:03 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP
# include <iostream>

namespace ft
{
	template <class InputIt>
	size_t	InputIt_get_len(InputIt first, InputIt last)
	{
		size_t	i = 0;

		for (; first != last; first++)
			++i;
		return (i);
	}
}

#endif