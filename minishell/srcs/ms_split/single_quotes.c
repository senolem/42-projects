/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:38:55 by faventur          #+#    #+#             */
/*   Updated: 2022/07/04 15:40:14 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	between_squotes(char *str, size_t *index)
{
	int	counter;

	counter = 0;
	if (str[*index] == '\'')
		(*index)++;
	while (str[*index])
	{
		if (str[*index] == '\'' && (ft_isoper(str[*index + 1])
				|| ms_check_charset(str[*index + 1])))
		{
			counter++;
			break ;
		}
		else if (str[*index] == '\'' && !ms_check_charset(str[*index + 1]))
			break ;
		(*index)++;
	}
	return (counter);
}

int	squote_len_index(char *str, size_t *index)
{
	int	counter;

	counter = 0;
	if (str[*index] == '\'')
		(*index)++;
	while (str[*index] && str[*index] != '\'')
	{
		counter++;
		(*index)++;
	}
	if (str[*index] == '\'' && str[*index + 1] != '\0')
		(*index)++;
	counter += 2;
	return (counter);
}

char	*ft_squote_pruner_index(char *quote, char *str, size_t *index,
			size_t *j)
{
	if (str[*index] == '\'')
	{
		quote[*j] = str[*index];
		(*index)++;
		(*j)++;
	}
	while (str[*index] && str[*index] != '\'')
	{
		quote[*j] = str[*index];
		(*j)++;
		(*index)++;
	}
	if (str[*index] == '\'' && str[*index + 1] != '\0')
	{
		quote[*j] = str[*index];
		(*index)++;
		(*j)++;
	}
	quote[*j] = '\0';
	return (quote);
}
