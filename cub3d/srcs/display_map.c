/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:12:25 by faventur          #+#    #+#             */
/*   Updated: 2022/10/04 15:12:26 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

char	**ft_map_reader(char *filename)
{
	char	**arr;
	char	*buffer;
	char	*temp;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	i = 0;
	buffer = malloc(sizeof(char) * 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	temp = buffer;
	while (42)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		buffer = ft_strjoin(buffer, temp);
		free(temp);
	}
	arr = ft_split(buffer, '\n');
	free(buffer);
	close(fd);
	return (arr);
}
