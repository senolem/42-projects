/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:57:51 by faventur          #+#    #+#             */
/*   Updated: 2022/07/01 17:31:27 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_charset(char c)
{
	if (ft_isspace(c) || c == '\0')
		return (1);
	return (0);
}

static size_t	wordgroup_counter(char *s)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			counter += between_squotes(s, &i);
		else if (s[i] == '\"')
			counter += between_dquotes(s, &i);
		else if (ft_isoper(s[i]) && s[i] != s[i + 1])
			counter++;
		else if ((!ms_check_charset(s[i]) && !ft_isoper(s[i]))
			&& (ft_isoper(s[i + 1]) || ms_check_charset(s[i + 1])))
			counter++;
		i++;
	}
	return (counter);
}

size_t	ms_let_count(char *str, size_t *index)
{
	size_t	counter;
	int		p_switch;

	counter = 0;
	p_switch = 0;
	while (ms_check_charset(str[*index]))
		(*index)++;
	if (ft_isoper(str[*index]) && ++p_switch)
		counter += oper_len_index(str, index);
	while (str[*index] && !ms_check_charset(str[*index])
		&& !ft_isoper(str[*index]) && !p_switch)
	{
		if (str[*index] == '\'')
			counter += squote_len_index(str, index);
		else if (str[*index] == '\"')
			counter += dquote_len_index(str, index);
		else
		{
			(*index)++;
			counter++;
		}
	}
	return (counter);
}

static char	*wordgroup_split(char *newstr, char *str, size_t *index)
{
	size_t	j;
	int		p_switch;

	j = 0;
	p_switch = 0;
	while (ms_check_charset(str[*index]))
		(*index)++;
	if (ft_isoper(str[*index]) && ++p_switch)
		ft_oper_writer_index(newstr, str, index, &j);
	while (str[*index] && !ms_check_charset(str[*index])
		&& !ft_isoper(str[*index]) && !p_switch)
	{
		if (str[*index] == '\'')
			ft_squote_pruner_index(newstr, str, index, &j);
		else if (str[*index] == '\"')
			ft_dquote_pruner_index(newstr, str, index, &j);
		else
			newstr[j++] = str[(*index)++];
	}
	newstr[j] = '\0';
	return (newstr);
}

char	**ms_split(char *s)
{
	char	**strtab;
	size_t	size;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s)
		return (NULL);
	size = wordgroup_counter(s);
	strtab = malloc(sizeof(char *) * (size + 1));
	if (!strtab)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (k < size)
	{
		strtab[k] = malloc(sizeof(char) * (ms_let_count((char *)s, &i) + 1));
		if (!strtab[k])
			return (ft_arr_freer_index(strtab, &k));
		wordgroup_split(strtab[k++], (char *)s, &j);
	}
	strtab[k] = NULL;
	return (strtab);
}
