/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:09:24 by albaur            #+#    #+#             */
/*   Updated: 2022/03/16 13:42:03 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*magic_read(int fd, char *keep)
{
	int		pos;
	char	*str;

	pos = 0;
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (0);
	pos++;
	while (pos != 0 && !ft_strchr(keep, '\n'))
	{
		pos = read(fd, str, BUFFER_SIZE);
		if (pos == -1)
		{
			free(str);
			return (0);
		}
		str[pos] = '\0';
		keep = ft_strjoin(keep, str);
	}
	free(str);
	return (keep);
}

static char	*magic_line(char *keep)
{
	int		pos;
	char	*str;

	pos = 0;
	if (keep[pos] == '\0')
		return (0);
	while (keep[pos] != '\n' && keep[pos] != '\0')
		pos++;
	str = (char *)malloc(sizeof(char) * (pos + 2));
	if (!str)
		return (0);
	pos = 0;
	while (keep[pos] != '\n' && keep[pos] != '\0')
	{
		str[pos] = keep[pos];
		pos++;
	}
	if (keep[pos] == '\n')
	{
		str[pos] = keep[pos];
		pos++;
	}
	str[pos] = '\0';
	return (str);
}

static char	*magic_keep(char *keep)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (keep[i] != '\n' && keep[i] != '\0')
		i++;
	if (keep[i] == '\0')
	{
		free(keep);
		return (0);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(keep) - i + 1));
	if (!str)
		return (0);
	i++;
	while (keep[i] != '\0')
	{
		str[j++] = keep[i++];
	}
	str[j] = '\0';
	free(keep);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*keep;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	keep = magic_read(fd, keep);
	if (!keep)
		return (0);
	str = magic_line(keep);
	keep = magic_keep(keep);
	return (str);
}
