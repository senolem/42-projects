/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:04:44 by faventur          #+#    #+#             */
/*   Updated: 2022/06/27 15:41:35 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_striter() function applies the f function to every character of
** the string passed as a parameter. Every character is passed by address
** to the f function so that it may be modified if necessary.
*/

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] && s[i] != '\0')
	{
		f(&s[i]);
		i++;
	}
}
