/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:27:45 by albaur            #+#    #+#             */
/*   Updated: 2022/04/11 09:37:30 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	convert_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

char	**convert_argv(int argc, char **argv)
{
	if (argc >= 3)
		argv = shift_array(argc, argv);
	else if (argc < 3)
		argv = ft_split(argv[1], ' ');
	return (argv);
}

void	push_swap_error(t_struct *list)
{
	free(list);
	write(2, "Error\n", 6);
}

t_struct	*push_swap_struct(int argc, char **argv)
{
	t_struct	*list;
	int			i;

	i = 0;
	list = (t_struct *)malloc(sizeof(t_struct));
	if (!list)
		push_swap_error(list);
	ft_bzero(list, sizeof(t_struct));
	list->len_a = argc;
	list->len_b = 0;
	list->stack_a = (int *)malloc(sizeof(int) * argc);
	if (!list->stack_a)
		push_swap_error(list);
	list->stack_b = (int *)malloc(sizeof(int) * argc);
	if (!list->stack_b)
		push_swap_error(list);
	while (i < argc)
	{
		list->stack_a[i] = ft_atoi(argv[i]);
		i++;
	}
	list->max_length = list->len_a;
	return (list);
}

int	main(int argc, char **argv)
{
	t_struct	*list;

	if (argc < 2)
		return (0);
	if (!sanity_check(argc, argv))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	else
	{
		argv = convert_argv(argc, argv);
		argc = convert_argc(argv);
		list = push_swap_struct(argc, argv);
	}
	push_swap_algo(list);
	free(list);
	return (0);
}
