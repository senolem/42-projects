/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:33:31 by faventur          #+#    #+#             */
/*   Updated: 2022/07/12 12:15:10 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_tokstrlen(t_token *token)
{
	size_t	i;

	i = 0;
	if (!token || !token->str)
		return (0);
	while (token->str[i])
		i++;
	return (i);
}

void	ft_tokdel(t_token *tok)
{
	if (tok != NULL)
	{
		free(tok->str);
		tok->str = NULL;
		free(tok);
		tok = NULL;
	}
}

void	ft_tokdisplay(t_token *token)
{
	if (token && token->str)
		ft_printf("%s\ntype: %d\n", token->str, token->type);
}

int	ft_tokcmp(t_token *token, int type)
{
	if (token)
	{
		if (token->type == type)
			return (0);
		return (1);
	}
	return (-1);
}
