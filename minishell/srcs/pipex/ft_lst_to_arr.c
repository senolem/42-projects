/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:50:10 by albaur            #+#    #+#             */
/*   Updated: 2022/07/19 16:58:08 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_counter(t_stack *stack)
{
	size_t	i;
	t_node	*current;

	if (!stack)
		return (-1);
	i = 0;
	current = stack->top;
	while (current)
	{
		if (!ft_tokcmp(current->content, greater_than_type)
			|| !ft_tokcmp(current->content, smaller_than_type)
			|| !ft_tokcmp(current->content, d_greater_than_type)
			|| !ft_tokcmp(current->content, d_smaller_than_type))
		{
			i++;
			current = current->next;
			if (current && i++)
				current = current->next;
		}
		else
			current = current->next;
	}
	return (i);
}

char	*ft_lst_to_arrdup(t_token *token)
{
	char	*tmp;

	if (token && token->str)
	{
		tmp = ft_strdup(token->str);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	return (NULL);
}

char	**ft_lst_to_arr(t_stack *stack)
{
	size_t	i;
	t_node	*tmp;
	char	**arr;

	if (!stack || !stack->top)
		return (NULL);
	i = 0;
	tmp = stack->top;
	arr = malloc(sizeof(char *) * (ft_stacksize(stack) + 1));
	if (!arr)
		return (NULL);
	arr[ft_stacksize(stack)] = 0;
	while (tmp && tmp->content)
	{
		arr[i] = ft_lst_to_arrdup(tmp->content);
		if (!arr[i])
		{
			ft_arr_freer_index(arr, &i);
			return (NULL);
		}
		tmp = tmp->next;
		++i;
	}
	return (arr);
}
/*
char	**ft_arr_cleaner(char **arr)
{
	size_t	arrlen;
	size_t	i;
	int		counter;

	if (!arr || !*arr)
		return (NULL);
	i = 0;
	arrlen = ft_arrlen;
	while (arr[i])
	{
		if (arr[i])
			counter++;
	}
	arr = malloc(sizeof(char *) * (ft_stacksize(stack) + 1));
	if (!arr)
		return (NULL);
	arr[ft_stacksize(stack)] = 0;
	while (tmp && tmp->content)
	{
		arr[i] = ft_lst_to_arrdup(tmp->content);
		if (!arr[i])
		{
			ft_arr_freer_index(arr, &i);
			return (NULL);
		}
		tmp = tmp->next;
		++i;
	}
	return (arr);
}
*/