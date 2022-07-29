/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:25:59 by albaur            #+#    #+#             */
/*   Updated: 2022/07/22 22:56:39 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process_exit(int code)
{
	t_exit	e;

	e.str = ft_itoa(WEXITSTATUS(code));
	e.err = env_get_arg("?EXIT");
	e.ret = ft_atoi(e.err);
	if (e.ret != 0)
	{
		e.shlvl = env_get_shlvl();
		e.tmp = ft_itoa(e.shlvl - 1);
		env_set_arg("SHLVL", e.tmp);
		env_set_arg("?", e.str);
		env_set_arg("?EXIT", "0");
		if (e.shlvl == 1)
			unlink(ENV_FILE);
		free(e.str);
		free(e.err);
		free(e.tmp);
		exit(e.ret);
	}
	else
		env_set_arg("?", e.str);
	free(e.str);
	free(e.err);
}
