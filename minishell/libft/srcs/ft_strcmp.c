/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:02:26 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 20:09:15 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strcmp() function compares the two strings s1 and s2. It returns
** an integer less than, equal to, or greater than zero if s1 is found,
** respectively, to be less than, to match, or be greater than s2.
** 
** Return Value: The ft_strcmp() function returns an integer less than,
** equal to, or greater than zero if s1 is found, respectively, to be
** less than, to match, or be greater than s2. If at least one of the
** strings passed as parameters is NULL, it returns -3000.
*/

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-3000);
	i = 0;
	while (((unsigned char *)s1)[i] != '\0' && ((unsigned char *)s2)[i] != '\0')
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	if (((unsigned char *)s2)[i] == '\0')
		return (((unsigned char *)s1)[i]);
	if (((unsigned char *)s1)[i] == '\0')
		return (-((unsigned char *)s2)[i]);
	return (0);
}
