/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 23:11:19 by faventur          #+#    #+#             */
/*   Updated: 2022/02/26 19:01:26 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The tolower() function converts the letter c to lower case, if
** possible.
** 
** If c is not an unsigned char value, or EOF, the behavior of this
** function is undefined.
** 
** Return Value: The value returned is that of the converted letter,
** or c if the conversion was not possible.
*/

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
		return (c);
	}
	else
		return (c);
}
