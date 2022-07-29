/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:37:19 by faventur          #+#    #+#             */
/*   Updated: 2022/06/26 16:05:24 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_functions.h"

void	ft_printerror(char *program, char *pathname)
{
	ft_fprintf(2, "%s: %s: %s\n", program, pathname, strerror(errno));
	exit(1);
}
