/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:45:37 by albaur            #+#    #+#             */
/*   Updated: 2022/07/18 15:06:07 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc > 1 && argv)
		throw_error(data, "Error", E2BIG);
	init_shell(data);
	while (!data->exit)
	{
		data->prompt = ft_concat(env_get_pwd(), " $ ");
		data->input = readline(data->prompt);
		if (data->input == NULL)
			break ;
		process_input(data);
		free(data->prompt);
	}
	data->shlvl = env_get_shlvl();
	data->tmp = ft_itoa(data->shlvl - 1);
	if (data->shlvl == 1)
		unlink(ENV_FILE);
	env_set_arg("SHLVL", data->tmp);
	free(data->tmp);
	free(data->prompt);
	free(data->input);
	free(data);
	return (0);
}
