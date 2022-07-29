/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 21:49:58 by faventur          #+#    #+#             */
/*   Updated: 2022/02/26 18:52:21 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The isdigit() function checks whether c, which must have the value
** of an unsigned char or EOF, is a digit (0 through 9).
** 
** Return Value: The values returned are nonzero if the character c
** falls into the tested class, and a zero value if not.
*/

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
