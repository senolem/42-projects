/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:45:37 by albaur            #+#    #+#             */
/*   Updated: 2022/06/14 10:37:18 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_input(t_data *data)
{
	if (data->mode && data->input[0] != '\0')
		add_history(data->input);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc > 1 && argv)
		throw_error(data, "Error", E2BIG);
	init_shell(data);
	while (!data->exit)
	{
		data->input = readline("~$ ");
		if (!data->input)
			break ;
		i = 0;
		while(ft_isspace(data->input[i]))
			++i;
		if (data->input)
			process_input(data);
		free(data->input);
	}
	return (0);
}
