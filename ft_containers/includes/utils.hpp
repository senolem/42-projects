/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:46:06 by albaur            #+#    #+#             */
/*   Updated: 2023/01/09 17:37:35 by albaur           ###   ########.fr       */
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

	template <class InputIt1, class InputIt2>
	bool	lexicographical_compare(InputIt1 lhs_begin, InputIt1 lhs_end, InputIt2 rhs_begin, InputIt2 rhs_end)
	{
		while (lhs_begin != lhs_end)
		{
			if (rhs_begin == rhs_end || *rhs_begin < *lhs_begin)
				return (false);
			else if (*lhs_begin < *rhs_begin)
				return (true);
			++lhs_begin;
			++rhs_begin;
		}
		return (rhs_begin != rhs_end);
	}

	template <class InputIt1, class InputIt2>
	bool equal (InputIt1 lhs_begin, InputIt1 lhs_end, InputIt2 rhs_begin)
	{
		while (lhs_begin != lhs_end)
		{
			if (*lhs_begin != *rhs_begin)
				return (false);
			++lhs_begin;
			++rhs_begin;
		}
		return (true);
	}

	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type				difference_type;
		typedef typename Iter::value_type					value_type;
		typedef typename Iter::pointer						pointer;
		typedef typename Iter::reference					reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template <class Iter>
	struct iterator_traits<Iter *>
	{
		typedef ptrdiff_t						difference_type;
		typedef Iter							value_type;
		typedef Iter*							pointer;
		typedef Iter&							reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class Iter>
	struct iterator_traits<const Iter *>
	{
		typedef ptrdiff_t						difference_type;
		typedef Iter							value_type;
		typedef const Iter*						pointer;
		typedef const Iter&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <bool use_const, typename const_false, typename const_true>
	struct enable_const {};

	template <typename const_false, typename const_true>
	struct enable_const<false, const_false, const_true>
	{
		typedef const_false	type;
	};

	template <typename const_false, typename const_true>
	struct enable_const<true, const_false, const_true>
	{
		typedef const_true	type;
	};
}

#endif