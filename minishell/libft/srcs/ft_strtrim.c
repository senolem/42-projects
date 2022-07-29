/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:31:36 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 21:33:44 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strtrim() function allocates (with malloc(3)) and returns a
** copy of the string s without the characters specified in set at the
** beginning and at the end of the string. If s doesn't contain anyone
** of the specified characters, the function returns a copy of s. If
** the allocation fails, the function returns NULL.
**
** Return Value: The function returns a trimmed copy of s or a "fresh"
** one.
*/

#include "libft.h"

static int	ft_check_charset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_trim_and_copy(char *dest, const char *src, const char *set)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(src) - 1;
	while (src[i] && ft_check_charset(src[i], set) && i <= len)
		i++;
	while (src[len] && ft_check_charset(src[len], set) && i <= len)
		len--;
	while (i <= len)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

static size_t	ft_trim_and_count(const char *s, const char *set)
{
	int	i;
	int	counter;
	int	len;

	i = 0;
	counter = 0;
	len = ft_strlen(s) - 1;
	while (s[i] && ft_check_charset(s[i], set) && i <= len)
		i++;
	while (s[len] && ft_check_charset(s[len], set) && i <= len)
		len--;
	while (i <= len)
	{
		counter++;
		i++;
	}
	return (counter);
}

char	*ft_strtrim(const char *s, const char *set)
{
	char	*copy;
	size_t	len;

	if (!s || !set)
		return (NULL);
	len = ft_trim_and_count(s, set);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (NULL);
	ft_trim_and_copy(copy, s, set);
	return (copy);
}
