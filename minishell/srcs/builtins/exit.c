/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:43:28 by albaur            #+#    #+#             */
/*   Updated: 2022/07/25 12:50:15 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit_print(void)
{
	int	fd;

	fd = open("/dev/stdin", O_WRONLY, 0777);
	ft_putendl_fd("exit", fd);
	close(fd);
}

int	builtin_exit_num(char **s)
{
	size_t	i;

	i = 0;
	while (ft_arrlen(s) == 2 && s[1][i])
	{
		if (ft_isdigit(s[1][i]) == 0)
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", s[1]);
			return (255);
		}
		++i;
	}
	return (0);
}

int	builtin_exit(char **s)
{
	int		code;

	code = 0;
	if (ft_arrlen(s) == 1)
	{
		env_set_arg("?EXIT", "126");
		builtin_exit_print();
		exit(126);
	}
	else if (ft_arrlen(s) > 2)
		return (ret_err("minishell: exit: too many arguments", NULL, 1));
	code = builtin_exit_num(s);
	if (code == 0 && ft_arrlen(s) == 2 && s[1][0] == '\0')
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", s[1]);
		code = 255;
	}
	else if (ft_arrlen(s) == 2)
		code = ft_atoi(s[1]);
	builtin_exit_print();
	env_set_arg("?EXIT", ft_itoa(code));
	exit(code);
}
