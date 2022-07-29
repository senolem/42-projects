/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:18:24 by faventur          #+#    #+#             */
/*   Updated: 2022/07/25 14:29:29 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_pipes(size_t len, t_var *var)
{
	size_t	i;

	i = 0;
	var->pipes = malloc(sizeof(int *) * (len + 1));
	while (i < len)
	{
		var->pipes[i] = malloc(sizeof(int) * 2);
		++i;
	}
	var->pipes[i] = 0;
}

int	pipex_open(t_stack **stack, size_t i, t_var *var)
{
	if (stack[i + 1])
	{
		if (pipe(var->pipes[i]) == -1)
		{
			perror("minishell: pipe");
			return (1);
		}
	}
	return (0);
}

int	pipex_close(t_stack **stack, size_t i, t_var *var)
{
	if (stack[i + 1])
		close(var->pipes[i][1]);
	if (i != 0 && stack[i - 1])
		close(var->pipes[i - 1][0]);
	if (var->fd[0] != 0 && !stack[i + 1])
		close(var->fd[0]);
	if (var->fd[1] != 1 && !stack[i + 1])
		close(var->fd[1]);
	return (0);
}

int	child_process(t_stack **stack, size_t i, t_var *var)
{
	int		code;
	pid_t	pid;
	char	**args;

	check_ms_launch(stack[i]);
	code = 0;
	pid = fork();
	if (pid)
		var->pid = pid;
	if (pid < 0)
		return (ret_err("minishell: fork: error", NULL, 1));
	else if (pid == 0)
	{
		sig_toggle(1);
		args = ft_lst_to_arr(stack[i]);
		pipex(stack, i, var);
		ft_exec(args, var);
		ft_arr_freer(args);
	}
	else if (pid > 0)
		waitpid(var->pid, &code, 0);
	sig_toggle(0);
	child_process_exit(code);
	return (0);
}

void	pipex(t_stack **stack, size_t i, t_var *var)
{
	dup2(var->fd[1], STDOUT_FILENO);
	dup2(var->fd[0], STDIN_FILENO);
	if (stack[i + 1])
	{
		close(var->pipes[i][0]);
		dup2(var->pipes[i][1], var->fd[1]);
		close(var->pipes[i][1]);
	}
	if (i != 0 && stack[i - 1])
	{
		dup2(var->pipes[i - 1][0], var->fd[0]);
		close(var->pipes[i - 1][0]);
	}
}
