/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:20:06 by albaur            #+#    #+#             */
/*   Updated: 2022/07/20 10:43:06 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print(char **env)
{
	char	**tmp;
	size_t	i;

	i = 0;
	ft_sort_chartab(env);
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		if (!tmp)
			return ;
		if (env[i][0] == '?')
			;
		else if (env[i][0] == '!')
			ft_printf("declare -x %s\n", tmp[0] + 1);
		else
			ft_printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
		ft_arr_freer(tmp);
		++i;
	}
}

static int	export_min(char **str)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	if (ft_arrlen(str) == 1)
		return (-1);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_isalnum(str[i][j]) > 0)
				return (1);
			++j;
		}
		++i;
	}
	if (ft_strlen(str[1]) == 1 && str[1][0] == '_')
		return (1);
	return (-1);
}

static int	export_check(char **str)
{
	size_t	i;

	i = 0;
	if (!str[0])
		return (ret_err("minishell: bad assignment", NULL, -1));
	if (ft_isdigit(str[0][0]) != 0)
		return (ret_err("minishell: export: not a valid identifier :",
				str[0], -1));
	while (str[0][i])
	{
		if (ft_isalnum(str[0][i]) == 0 && str[0][i] != '_')
			return (ret_err("minishell: export: not valid in this context:",
					str[0], -1));
		++i;
	}
	if (ft_arrlen(str) == 1)
		return (-2);
	else
		return (1);
}

static int	export_exec(t_export *e, char **str)
{
	while (str[++e->i])
	{
		e->input = ft_split(str[e->i], '=');
		if (!e->input)
			return (ret_err("minishell: bad assignment", NULL, 1));
		e->j = export_check(e->input);
		e->tmp = ft_strjoin("!", e->input[0]);
		if (e->j == 1)
		{
			if (env_search(e->tmp, e->env) >= 0)
			{
				e->env = env_delete(e->tmp, &e->env);
				env_set(e->input[0], e->input[1], &e->env);
			}
			else
				env_set(e->input[0], e->input[1], &e->env);
		}
		else if (e->j == -2)
			env_set(e->tmp, "''", &e->env);
		free(e->tmp);
		ft_arr_freer(e->input);
	}
	if (e->j == -2)
		return (1);
	return (0);
}

int	builtin_export(char **str)
{
	t_export	e;

	e.i = 0;
	e.j = 0;
	e.env = env_read(ENV_FILE);
	if (!str || export_min(str) == -1)
	{
		export_print(e.env);
		ft_arr_freer(e.env);
		return (0);
	}
	e.j = export_exec(&e, str);
	env_write(ENV_FILE, e.env);
	ft_arr_freer(e.env);
	return (e.j);
}
