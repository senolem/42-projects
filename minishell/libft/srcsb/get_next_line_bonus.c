/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:36:09 by faventur          #+#    #+#             */
/*   Updated: 2022/03/12 16:32:35 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The get_next_line() function returns a line read from a file descriptor.
*/

#include "get_next_line_bonus.h"

static char	*ft_rest(char *reading_buf)
{
	int		i;
	int		j;
	char	*s;

	i = ft_strlen(reading_buf);
	j = 0;
	if (!reading_buf)
		return (NULL);
	while (reading_buf[j] && reading_buf[j] != '\n')
		j++;
	if (reading_buf[j] == '\0')
	{
		free(reading_buf);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (i - j));
	if (!s)
		return (NULL);
	i = 0;
	j++;
	while (reading_buf[j])
		s[i++] = reading_buf[j++];
	s[i] = '\0';
	free(reading_buf);
	return (s);
}

static char	*ft_last_line(char *reading_buf)
{
	char	*s;
	int		i;

	i = 0;
	if (!reading_buf)
		return (NULL);
	while (reading_buf[i] && reading_buf[i] != '\n')
		i++;
	if (reading_buf[0] == '\0')
		return (NULL);
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (reading_buf[i] != '\n' && reading_buf[i])
	{
		s[i] = reading_buf[i];
		i++;
	}
	if (reading_buf[i] == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

static char	*ft_reader(int fd, char *buffer, char *reading_buf, char *tmp)
{
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = reading_buf;
		if (!tmp)
		{
			tmp = (char *)malloc(sizeof(char) * 1);
			tmp[0] = '\0';
		}
		reading_buf = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(reading_buf, '\n') != NULL)
			break ;
	}
	free(buffer);
	return (reading_buf);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*reading_buf[257];
	char		*ret;
	char		*tmp;

	tmp = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > 256)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	reading_buf[fd] = ft_reader(fd, buffer, reading_buf[fd], tmp);
	if (!reading_buf[fd])
		return (NULL);
	ret = ft_last_line(reading_buf[fd]);
	reading_buf[fd] = ft_rest(reading_buf[fd]);
	return (ret);
}
