/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:06:12 by albaur            #+#    #+#             */
/*   Updated: 2022/04/11 14:20:58 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_struct
{
	int		*stack_a;
	int		len_a;
	int		*stack_b;
	int		len_b;
	int		max_length;
}				t_struct;

// argv check and initialization
int			sanity_check(int argc, char **argv); // check if argv is valid
t_struct	*push_swap_struct(int argc, char **argv); // argv to structure
char		**shift_array(int argc, char **argv); // deletes first argument
int			push_swap_algo(t_struct *list); // main algo function
int			check_sort(t_struct *list); // check if stack_a is sorted
void		push_swap_error(t_struct *list); // free list if called

// operations
void		swap_a(t_struct *list);
void		swap_b(t_struct *list);
void		swap_ab(t_struct *list);
void		push_a(t_struct *list);
void		push_b(t_struct *list);
void		rotate_a(t_struct *list);
void		rotate_b(t_struct *list);
void		rotate_ab(t_struct *list);
void		rotate_reverse_a(t_struct *list);
void		rotate_reverse_b(t_struct *list);
void		rotate_reverse_ab(t_struct *list);

// get numbers
int			get_min(int *stack, int len); // get min nb index
int			get_next_min(int *stack, int len, int tmp); // next min nb index
int			get_max(int *stack, int len); // get max nb index

// sort algorithms
void		sort_3(t_struct *list); // sorts 3 numbers
void		sort_4(t_struct *list); // sorts 4 numbers
void		sort_5(t_struct *list); // sorts 5 numbers
void		stack_to_index(t_struct *list); // numbers to indexes (for >= 6 nbs)
void		radix_sort(t_struct *list); // sorts 6 numbers or more

#endif