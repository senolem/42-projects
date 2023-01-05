/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:46:06 by albaur            #+#    #+#             */
/*   Updated: 2023/01/05 17:46:46 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP
# include <iostream>

namespace ft
{
	template <bool _bool, class _type = void>
	struct enable_if
	{

	};

	template <class _type>
	struct enable_if<true, _type>
	{
		typedef _type type;
	};

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