/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:38:25 by albaur            #+#    #+#             */
/*   Updated: 2022/07/13 16:58:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **str)
{
	char	**env;
	size_t	i;

	if (ft_arrlen(str) > 1)
	{
		ft_printf("env: too many arguments\n");
		return (1);
	}
	env = env_read(ENV_FILE);
	i = 0;
	while (env[i])
	{
		if (env[i][0] == '!' || env[i][0] == '?')
			;
		else
			ft_printf("%s\n", env[i]);
		++i;
	}
	ft_arr_freer(env);
	return (0);
}
