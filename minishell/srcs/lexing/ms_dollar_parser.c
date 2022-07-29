/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:16:18 by faventur          #+#    #+#             */
/*   Updated: 2022/07/25 12:07:36 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ms_dollar_parser() function allocates (with malloc(3)) and
** returns a "fresh" null-terminated string with the name of the
** environment variable found in the string passed as a parameter.
** 
** The ms_dollar_replacer() function checks if the environment
** variable name passed as a parameter corresponds to an existant
** variable and, if it's the case, replaces it with its content
** in the new string.
** The idea is that what is written before the $ symbol is copied,
** then the content of the variable is written, followed by the
** rest of the string.
*/

#include "minishell.h"

static void	ms_dollar_eraser(t_dollar *dollar)
{
	dollar->i = 0;
	dollar->j = 0;
	dollar->line_len = ft_strlen(dollar->line);
	dollar->len = dollar->line_len - (dollar->varname_len + 1);
	dollar->str = malloc(sizeof(char) * (dollar->len + 1));
	if (!dollar->str)
		return ;
	while (dollar->line[dollar->i] && dollar->line[dollar->i] != '$')
		dollar->str[dollar->j++] = dollar->line[dollar->i++];
	if (dollar->line[dollar->i] == '$')
		dollar->str[dollar->j] = '\0';
	dollar->i += dollar->varname_len + 1;
	dollar->j = ft_strlen(dollar->str);
	while (dollar->line[dollar->i] && dollar->i < dollar->line_len)
		dollar->str[dollar->j++] = dollar->line[dollar->i++];
	dollar->str[dollar->j] = '\0';
}

static void	ms_dollar_measurer(t_dollar *dollar)
{
	dollar->line_len = ft_strlen(dollar->line);
	dollar->var_len = ft_strlen(dollar->var);
	dollar->len = dollar->line_len - (dollar->varname_len + 1)
		+ dollar->var_len;
}

static void	ms_dollar_tailor(t_dollar *dollar)
{
	dollar->i = 0;
	dollar->j = 0;
	ms_dollar_measurer(dollar);
	dollar->str = malloc(sizeof(char) * (dollar->len + 1));
	if (!dollar->str)
		return ;
	while (dollar->line[dollar->i] && dollar->line[dollar->i] != '$')
		dollar->str[dollar->j++] = dollar->line[dollar->i++];
	if (dollar->line[dollar->i] == '$')
		dollar->str[dollar->j] = '\0';
	ft_strcat(dollar->str, dollar->var);
	if (!dollar->str)
		return ;
	dollar->i += dollar->varname_len + 1;
	dollar->j = ft_strlen(dollar->str);
	while (dollar->line[dollar->i] && dollar->i < dollar->line_len)
		dollar->str[dollar->j++] = dollar->line[dollar->i++];
	dollar->str[dollar->j] = '\0';
}

char	*ms_dollar_replacer(t_dollar *dollar)
{
	dollar->var = ft_getenv(dollar->varname);
	if (dollar->var)
	{
		ms_dollar_tailor(dollar);
		ft_strdel(&dollar->line);
		dollar->line = dollar->str;
		ft_strdel(&dollar->var);
	}
	else
	{
		ms_dollar_eraser(dollar);
		ft_strdel(&dollar->line);
		dollar->line = dollar->str;
	}
	ft_strdel(&dollar->varname);
	return (dollar->line);
}

void	ms_dollar_parser(t_token *token, ssize_t *index)
{
	t_dollar	dollar;

	dollar.line = token->str;
	ms_dollar_counter(&dollar, index);
	dollar.i = 0;
	dollar.varname = malloc(sizeof(char) * (dollar.varname_len + 1));
	*index -= dollar.varname_len;
	while (dollar.line[*index] && ms_dollar_check_charset(dollar.line[*index]))
		dollar.varname[dollar.i++] = dollar.line[(*index)++];
	dollar.varname[dollar.i] = '\0';
	token->str = ms_dollar_replacer(&dollar);
}
