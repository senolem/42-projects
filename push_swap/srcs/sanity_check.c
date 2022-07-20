/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanity_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:55:02 by albaur            #+#    #+#             */
/*   Updated: 2022/04/08 17:12:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

char	**shift_array(int argc, char **argv)
{
	int		i;
	char	**temp;

	i = 0;
	temp = malloc(sizeof(char *) * argc);
	while (argv[i])
	{
		temp[i] = ft_strdup(argv[i]);
		i++;
	}
	i = 0;
	while (i < argc - 1)
	{
		temp[i] = argv[i + 1];
		temp[i + 1] = argv[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

static int	duplicate_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < argc)
	{
		while (j < argc)
		{
			if (ft_atoi(argv[i]) == ft_atoi(argv[j]) && j != i)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

static int	integer_overlap_check(const char *str)
{
	if (!ft_strtololo(str))
		return (0);
	return (1);
}

static int	isdigit_check(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	if (str[0] == '-')
	{
		if (size > 1)
		{
			if (str[i + 1] < '0' || str[i + 1] > '9')
				return (0);
			else
				i++;
		}
		else
			return (0);
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	sanity_check(int argc, char **argv)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	if (argc >= 3)
		argv = shift_array(argc, argv);
	else if (argc < 3)
		argv = ft_split(argv[1], ' ');
	while (argv[c] != 0)
		c++;
	while (i < c)
	{
		if (!isdigit_check(argv[i]) || !integer_overlap_check(argv[i]))
			return (0);
		i++;
	}
	if (!duplicate_check(c, argv))
	{
		free(argv);
		return (0);
	}
	free(argv);
	return (1);
}
