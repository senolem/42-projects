/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_usd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:27:45 by albaur            #+#    #+#             */
/*   Updated: 2022/07/14 15:27:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_usd_quote_counter(char *str, size_t *i, size_t *counter, char quote)
{
	if (str[*i] == quote)
	{
		(*counter)++;
		(*i)++;
	}
	while (str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
	{
		(*counter)++;
		(*i)++;
	}
}

size_t	ft_usd_quote_len(char *str)
{
	size_t	counter;
	size_t	i;

	if (!str)
		return (0);
	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ft_usd_quote_counter(str, &i, &counter, '\'');
		else if (str[i] == '\"')
			ft_usd_quote_counter(str, &i, &counter, '\"');
		else
			i++;
	}
	return (counter);
}
