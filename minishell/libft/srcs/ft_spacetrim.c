/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spacetrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:31:36 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 21:36:26 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strtrim() function allocates (with malloc(3)) and returns a
** copy of the string passed as a parameter without the white spaces
** at the beginning and at the end of the string. Are considered as
** white spaces the characters ' ', '\n' and '\t'. If s doesn't
** contain any white space, the function returns a copy of s. If the
** allocation fails, the function returns NULL.
**
** Return Value: The function returns a trimmed copy of s or a
** "fresh" one.
*/

#include "libft.h"

static char	*ft_trim_and_copy(char *dest, char const *src)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!dest || !src)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(src) - 1;
	while (src[i] && ft_isspace(src[i]) && i <= len)
		i++;
	while (src[len] && ft_isspace(src[len]) && i <= len)
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

static size_t	ft_trim_and_count(char const *s)
{
	size_t	i;
	size_t	counter;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	counter = 0;
	len = ft_strlen(s) - 1;
	while (s[i] && ft_isspace(s[i]) && i <= len)
		i++;
	while (s[len] && ft_isspace(s[len]) && i <= len)
		len--;
	while (i <= len)
	{
		counter++;
		i++;
	}
	return (counter);
}

char	*ft_spacetrim(char const *s)
{
	char	*copy;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_trim_and_count(s);
	if (!len)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (NULL);
	ft_trim_and_copy(copy, s);
	if (!copy)
		return (NULL);
	return (copy);
}
