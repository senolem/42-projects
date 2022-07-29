/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:40:42 by faventur          #+#    #+#             */
/*   Updated: 2022/07/23 17:12:28 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The ms_dollar_manager() function parses each stack element and, in
** case there are environment variable names in the strings (strings
** without quotes or between double quotes), it calls the
** ms_dollar_parser() function to rewrite the string by replacing the
** variable names with their content.
*/

void	ms_dollar_manager(t_stack *stack)
{
	t_node	*current;
	ssize_t	index;

	index = 0;
	current = stack->top;
	while (current)
	{
		index = ms_dollar_checker(current->content);
		if (index >= 0 && (ms_usd_quote_checker(current->content, &index) == 2
				|| !ms_usd_quote_checker(current->content, &index)))
			ms_dollar_parser(current->content, &index);
		else
			current = current->next;
	}
}
