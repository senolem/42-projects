/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:44:32 by albaur            #+#    #+#             */
/*   Updated: 2022/06/19 16:08:40 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>

# define ENV_FILE "/tmp/minishell_env"

// main struct

typedef struct s_data
{
	char		*input;
	int			exit;
	int			mode;
}		t_data;

// init
int			init_shell(t_data *data);
int			env_init(void);
void		env_write(char *path, char **env);
void		env_set(char *str, char *value, char ***env);
char		**env_add(char *str, char ***env);
char		*env_get(char *str, char **env);
int			env_search(char *str, char **env);
char		**env_read(char *path);


// parsing
int			parsing_input(t_data *data, char *input);

// env
char		*env_get(char *name, char **env);

// builtins

// signals
void		sig_ignore(t_data *data, int sig);

// utils
void		throw_error(t_data *data, char *msg, int err);

#endif