/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:39:11 by albaur            #+#    #+#             */
/*   Updated: 2022/07/15 22:45:40 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_exec_args(char **cmd_args)
{
	size_t	i;
	char	**args;

	i = 0;
	args = malloc(sizeof(char *) * 4);
	if (!args)
		return (NULL);
	args[0] = ft_strdup("/bin/bash");
	args[1] = ft_strdup("-c");
	args[2] = 0;
	while (cmd_args[i])
	{
		args[2] = ft_concat(args[2], cmd_args[i]);
		if (i != ft_arrlen(cmd_args) - 1)
			args[2] = ft_concat(args[2], " ");
		++i;
	}
	args[3] = 0;
	return (args);
}
