/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:24:49 by albaur            #+#    #+#             */
/*   Updated: 2022/07/20 22:06:42 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	throw_error(char *msg, int err)
{
	if (err != 0)
		errno = err;
	perror(msg);
	exit(EXIT_FAILURE);
}
