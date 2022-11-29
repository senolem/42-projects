/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 05:02:37 by albaur            #+#    #+#             */
/*   Updated: 2022/04/19 05:03:46 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *keep, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!keep)
	{
		keep = (char *)malloc(1 * sizeof(char));
		keep[0] = '\0';
	}
	if (!keep || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(keep) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (keep)
		while (keep[++i] != '\0')
			str[i] = keep[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(keep) + ft_strlen(buff)] = '\0';
	free(keep);
	return (str);
}
