/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:46:51 by albaur            #+#    #+#             */
/*   Updated: 2022/10/21 16:22:00 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

enum	{
	READ = 0,
	WRITE
};

void	putstr_fd(char *str, int fd)
{
	unsigned int	i = 0;

	while(str[i])
		++i;
	write(fd, str, i);
}

void	throw_error(void)
{
	putstr_fd("error: fatal\n", 2);
	exit(1);
}

void	exec_cmd(char **argv, char **env, int *fd, int *prev_fd)
{
	if (argv && argv[0] && env && fd && *prev_fd)
	{
		if (strcmp(argv[0], "cd") == 0)
		{
			if (argv[1] != NULL && argv[2] == NULL)
			{
				if (chdir(argv[1]) != 0)
				{
					putstr_fd("error: cd: cannot change directory to ", 2);
					putstr_fd(argv[1], 2);
					putstr_fd("\n", 2);
				}
			}
			else
				putstr_fd("error: cd: bad arguments\n", 2);
		}
		else
		{
			pid_t	pid = fork();
			if (pid == -1)
				throw_error();
			if (pid == 0)
			{
				close(fd[READ]);
				if (*prev_fd != -1)
					dup2(*prev_fd, STDIN_FILENO);
				if (fd[WRITE] != -1)
					dup2(fd[WRITE], STDOUT_FILENO);
				close(fd[WRITE]);
				if (execve(argv[0], argv, env) == -1)
				{
					putstr_fd("error: cannot execute ", 2);
					putstr_fd(argv[0], 2);
					putstr_fd("\n", 2);
				}
				exit(2);
			}
			else
			{
				waitpid(pid, NULL, 0);
				if (*prev_fd != -1)
				{
					close(*prev_fd);
					*prev_fd = -1;
				}
				if (fd[WRITE] != -1)
				{
					close(fd[WRITE]);
					fd[WRITE] = -1;
				}
				if (fd[READ] != -1)
				{
					*prev_fd = fd[READ];
					fd[READ] = -1;
				}
			}
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2] = {-1, -1};
	int	prev_fd = -1;
	int	start = 1;

	if (argc <= 1)
		return (0);		
	for(int i = 1; argv[i]; i++)
	{
		if (strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0)
		{
			if (strcmp(argv[i], "|") == 0)
			{
				if (pipe(fd) != 0)
					throw_error();
			}
			argv[i] = NULL;
			exec_cmd(&argv[start], env, fd, &prev_fd);
			start = i + 1;
		}
	}
	exec_cmd(&argv[start], env, fd, &prev_fd);
	return (0);
}