/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_err_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:24:49 by albaur            #+#    #+#             */
/*   Updated: 2022/11/15 18:16:53 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	throw_err_ex(const char *str)
{
	if (str)
	{
		ft_putendl_fd(str, 2);
	}
	exit(1);
}
