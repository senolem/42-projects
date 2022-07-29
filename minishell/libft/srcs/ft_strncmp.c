/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:13:31 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 21:01:34 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strncmp() function is similar to the strcmp() function, except
** that it only compares the first (at most) n bytes of s1 and s2.
** 
** Return Value: The ft_strncmp() function returns an integer less than,
** equal to, or greater than zero if the first n bytes of s1 are found,
** respectively, to be less than, to match, or be greater than s2. If at
** least one of the strings passed as parameters is NULL, the return
** value will be -3000.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-3000);
	i = 0;
	if (n <= 0)
		return (0);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && i < n - 1
		&& ((unsigned char *)s1)[i] != '\0' && ((unsigned char *)s2)[i] != '\0')
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
