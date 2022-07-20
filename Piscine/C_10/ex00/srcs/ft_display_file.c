/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:30:00 by albaur            #+#    #+#             */
/*   Updated: 2021/11/30 11:01:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	ft_displayfile(char *argv)
{
	int		file;
	char	buffer[40000];
	int		bytepos;

	bytepos = 1;
	file = open(argv, O_RDONLY);
	if (file == -1)
		return (1);
	while (bytepos > 0)
	{
		bytepos = read(file, buffer, 40000);
		write(1, &buffer[0], bytepos);
	}
	close(file);
	return (0);
}

int	main(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (argc == 1)
	{
		write(2, "File name missing.", 18);
		return (1);
	}
	if (argc > 2)
	{
		write(2, "Too many arguments.", 19);
		return (1);
	}
	if (argc == 2)
	{
		ret = ft_displayfile(argv[1]);
		if (ret == 0)
			return (0);
		else if (ret == 1)
		{
			write(2, "Cannot read file.", 17);
			return (1);
		}
	}
}
