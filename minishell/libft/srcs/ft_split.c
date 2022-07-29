/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:21:03 by faventur          #+#    #+#             */
/*   Updated: 2022/07/01 10:41:07 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strsplit() function allocates (with malloc(3)) and returns
** an array of "fresh" null-terminated strings (and the array will
** be null-terminated too) resulting from the splitting of the string
** passed as a parameter based on the character c. If the allocation
** fails, the function returns NULL.
*/

#include "libft.h"

static int	ft_check_charset(char c, char set)
{
	if (c == set || c == '\0')
		return (1);
	return (0);
}

static size_t	ft_word_counter(const char *s, char set)
{
	size_t	counter;
	size_t	i;

	if (!s)
		return (0);
	counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (!ft_check_charset(s[i], set) && ft_check_charset(s[i + 1], set))
			counter++;
		i++;
	}
	return (counter);
}

static size_t	let_count(char *str, char set, size_t *index)
{
	size_t	j;

	if (!str)
		return (0);
	j = 0;
	while (ft_check_charset(str[*index], set))
		(*index)++;
	while (str[*index] && !ft_check_charset(str[*index], set))
	{
		j++;
		(*index)++;
	}
	return (j);
}

static char	*ft_word_split(char	*newstr, char *str, char set, size_t *index)
{
	size_t	j;

	if (!newstr || !str)
		return (NULL);
	j = 0;
	while (ft_check_charset(str[*index], set))
		(*index)++;
	while (str[*index] && !ft_check_charset(str[*index], set))
		newstr[j++] = str[(*index)++];
	newstr[j] = '\0';
	return (newstr);
}

char	**ft_split(char const *s, char c)
{
	t_split	var;

	if (!s)
		return (NULL);
	if (ft_strlen(s) == 1 && s[0] == c)
		return (NULL);
	var.i = 0;
	var.j = 0;
	var.k = 0;
	var.tab_size = ft_word_counter(s, c);
	var.strtab = (char **)malloc(sizeof(char *) * (var.tab_size + 1));
	if (!var.strtab)
		return (NULL);
	while (var.k < ft_word_counter(s, c))
	{
		var.str_len = let_count((char *)s, c, &var.i);
		var.strtab[var.k] = malloc(sizeof(char) * (var.str_len + 1));
		if (!var.strtab[var.k])
			return (ft_arr_freer_index(var.strtab, &var.k));
		ft_word_split(var.strtab[var.k++], (char *)s, c, &var.j);
	}
	var.strtab[var.k] = NULL;
	return (var.strtab);
}
