/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrbool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:00:52 by faventur          #+#    #+#             */
/*   Updated: 2022/06/26 16:22:51 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strstrbool() function finds the first occurrence of the substring
** needle in the string haystack. The terminating null bytes are not
** compared.
** 
** Return Value: This function returns 0 if the substring is found, 1 if
** it's not found.
**
** Notice: I created the strstrbool() function for use with my
** ft_stack_remove_if() function, that's why it returns a 0 where it
** should return a 1 and vice versa.
*/

#include "_functions.h"

int	ft_strstrbool(const char *haystack, const char *needle)
{
	size_t	str_len;
	size_t	tofind_len;
	size_t	i;
	size_t	j;

	str_len = ft_strlen(haystack);
	tofind_len = ft_strlen(needle);
	i = 0;
	if (str_len < tofind_len)
		return (1);
	while (i <= str_len - tofind_len)
	{
		j = 0;
		while (j < tofind_len)
		{
			if (*(char *)(haystack + i + j) != *(char *)(needle + j))
				break ;
			j++;
		}
		if (j == tofind_len)
			return (0);
		i++;
	}
	return (1);
}
