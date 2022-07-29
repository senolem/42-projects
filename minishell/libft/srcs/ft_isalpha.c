/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 21:36:26 by faventur          #+#    #+#             */
/*   Updated: 2022/02/26 18:58:20 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The isalpha() function checks whether c, which must have the value
** of an unsigned char or EOF, is an alphabetic character; in the
** standard "C" locale, it is equivalent to (isupper(c) || islower(c)).
** 
** Return Value: The values returned are nonzero if the character c
** falls into the tested class, and a zero value if not.
*/

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (2);
	else
		return (0);
}
