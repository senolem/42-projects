/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:44:51 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 20:31:04 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_map_reader() function opens the .ber files and creates an array
** of strings made up of the lines composing the file.
*/

#include "_functions.h"

char	**ft_map_reader(char *filename)
{
	t_map_reader	var;

	var.fd = open(filename, O_RDONLY);
	if (var.fd < 0)
		return (NULL);
	var.i = 0;
	var.buffer = malloc(sizeof(char) * 1);
	if (!var.buffer)
		return (NULL);
	var.buffer[0] = '\0';
	var.temp = var.buffer;
	while (42)
	{
		var.temp = get_next_line(var.fd);
		if (var.temp == NULL)
			break ;
		var.buffer = ft_strjoin(var.buffer, var.temp);
		if (var.buffer == NULL)
			return (NULL);
		free(var.temp);
	}
	var.arr = ft_split(var.buffer, '\n');
	free(var.buffer);
	close(var.fd);
	return (var.arr);
}
