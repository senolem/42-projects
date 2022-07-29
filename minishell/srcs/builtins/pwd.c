/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:52:22 by albaur            #+#    #+#             */
/*   Updated: 2022/07/05 11:07:02 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **str)
{
	char	**env;

	(void)str;
	env = env_read(ENV_FILE);
	ft_putendl(env_get("PWD", env));
	ft_arr_freer(env);
	return (0);
}
