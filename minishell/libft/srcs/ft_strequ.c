/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:35:25 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 17:48:27 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strequ() function compares lexicographically the two strings
** passed as parameters.
** 
** Return Value: The function returns 1 if the two strings are equal,
** otherwise it returns 0.
*/

#include "libft.h"

int	ft_strequ(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	if (s1[i] == '\0' || s2[i] == '\0')
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
